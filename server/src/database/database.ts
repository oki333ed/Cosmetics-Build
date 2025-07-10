import * as sqlite3 from "sqlite3";
import * as argon2 from "argon2"

import axios, {Axios} from "axios"
import {open, Database} from 'sqlite';

import { User } from "../types/user";
import { AccountCosmetics, accountCosmeticsGetAccountCosmetics, ActiveCosmetics, activeCosmeticsGetActiveCosmetics, Cosmetic, FullCosmetic } from "../types/cosmetics";
import { filterAllCosmetics, getActiveCosmetics } from "../utils";
import { PacketResponse } from "../types/response";

let db: Database<sqlite3.Database, sqlite3.Statement>;

export async function init() {
    const dbPath = process.env.DBPATH as string | "./database.db";
    db = await open({
        filename: dbPath,
        driver: sqlite3.Database
    })
}

export async function addCosmetic(accountID: number, cosmeticID: number, isActive: boolean) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    };

    const doesCosmeticExist = await db.get("SELECT * FROM AccountCosmetics WHERE accountID = ? AND cosmeticID = ?", accountID, cosmeticID);
    if (doesCosmeticExist !== undefined) {
        packetRes.code = 401;
        packetRes.message = "Cosmetic has already been added to this account!"
    } else {
        await db.run("INSERT INTO AccountCosmetics (accountID, cosmeticID, isActive) VALUES (?, ?, ?)", accountID, cosmeticID, (!isActive) ? 0 : 1)
        packetRes.code = 200
        packetRes.message = "Cosmetic added successfully"
    }

    return packetRes;
}

export async function createUser(accountID: number, token: string) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    };

    await axios.get(`https://argon.globed.dev/v1/validation/check?account_id=${accountID}&authtoken=${token}`).then(async (res) => {
        if (res.data["valid"] == true) {
            const doesAccExist = await db.get("SELECT * FROM Accounts WHERE accountID = ?", accountID)
            if (doesAccExist !== undefined) {
                packetRes.code = 401;
                packetRes.message = "Account already exists!"
            } else {
                await db.run("INSERT INTO Accounts (accountID, creditsAmount) VALUES (?, 0)", accountID)
                packetRes.code = 200;
                packetRes.message = "Account created successfully!"
            }
        }
    })

    console.log(`User ${accountID} has just logged in`)
    return packetRes;
}

export async function updateUser(accountID: number, creditsAmount: number, activeCosmetics: ActiveCosmetics, accountCosmetics: AccountCosmetics) {
    let newCreditsAmount: number;
    const oldCreditsAmount = await db.get("SELECT * FROM Accounts WHERE accountID = ?", accountID)
    if (oldCreditsAmount !== undefined) {
        newCreditsAmount = oldCreditsAmount["creditsAmount"] + creditsAmount
        const updatingUserAcc = await db.get("UPDATE Accounts SET creditsAmount = ? WHERE accountID = ?", newCreditsAmount, accountID);
        if (updatingUserAcc === undefined) {

        } else {
            let cosmetics = activeCosmeticsGetActiveCosmetics(activeCosmetics);
            await Promise.all(cosmetics.map(async (cosmetic: Cosmetic) => {
                setCosmeticActive(accountID, cosmetic.cosmeticID)
            }))
            
            let userCosmetics = (await getUserInfo(accountID)).allCosmetics

            // this sucks but whatever
            if (userCosmetics.hats.length <= accountCosmetics.hats.length) {
                let newCosmetics = accountCosmetics.hats.filter(element => !userCosmetics.hats.includes(element))
                await Promise.all(newCosmetics.map((cosmetic: Cosmetic) => {
                    addCosmetic(accountID, cosmetic.cosmeticID, (cosmetic.isActive === 0))
                }))
            }

            if (userCosmetics.masks.length <= accountCosmetics.masks.length) {
                let newCosmetics = accountCosmetics.masks.filter(element => !userCosmetics.masks.includes(element))
                await Promise.all(newCosmetics.map((cosmetic: Cosmetic) => {
                    addCosmetic(accountID, cosmetic.cosmeticID, (cosmetic.isActive === 0))
                }))
            }

            if (userCosmetics.objects.length <= accountCosmetics.objects.length) {
                let newCosmetics = accountCosmetics.objects.filter(element => !userCosmetics.objects.includes(element))
                await Promise.all(newCosmetics.map((cosmetic: Cosmetic) => {
                    addCosmetic(accountID, cosmetic.cosmeticID, (cosmetic.isActive === 0))
                }))
            }

            if (userCosmetics.particles.length <= accountCosmetics.particles.length) {
                let newCosmetics = accountCosmetics.particles.filter(element => !userCosmetics.particles.includes(element))
                await Promise.all(newCosmetics.map((cosmetic: Cosmetic) => {
                    addCosmetic(accountID, cosmetic.cosmeticID, (cosmetic.isActive === 0))
                }))
            }
        }
    }

    return getUserInfo(accountID);
}

export async function getAllCosmetics() {
    const cosmetics = await db.all("SELECT * FROM Cosmetics")

    let allCosmetics: Cosmetic[] = []
    await Promise.all(cosmetics.map(async (cosmetic: any) => {
        let newCos: FullCosmetic = {
            cosmeticID: cosmetic["cosmeticID"],
            cosmeticName: cosmetic["cosmeticName"],
            cosmeticDescription: cosmetic["cosmeticDescription"],
            cosmeticAmount: cosmetic["cosmeticAmount"],
            cosmeticRarity: cosmetic["cosmeticRarity"],
            isActive: 0
        }
        allCosmetics.push(newCos)
    }));

    return allCosmetics
}

export async function getCosmetic(cosmeticID: number) {
    const cosmetic = await db.get("SELECT * FROM Cosmetics WHERE cosmeticID = ?", cosmeticID);

    const cosmeticType: Cosmetic = {
        cosmeticID: cosmetic["cosmeticID"],
        cosmeticName: cosmetic["cosmeticName"],
        isActive: cosmetic["isActive"]
    }

    return cosmeticType;
}

export async function getUserInfo(accountID: number): Promise<User> {
    const accRes = await db.get("SELECT * FROM Accounts WHERE accountID = ?", accountID)
    const cosRes = await db.all("SELECT * FROM AccountCosmetics WHERE accountID = ?", accountID)

    const allCosmetics: Cosmetic[] = [];
    await Promise.all(cosRes.map(async (cosmetic: any) => {
        let cos = await getCosmetic(cosmetic["cosmeticID"])
        cos.isActive = cosmetic["isActive"];
        allCosmetics.push(cos);
    }));

    const user: User = {
        accountID: accountID,
        creditsAmount: accRes["creditsAmount"],
        activeCosmetics: getActiveCosmetics(allCosmetics),
        allCosmetics: filterAllCosmetics(allCosmetics),
    };

    return user
}

export async function getUserCosmetics(accountID: number) {
    const cosRes = await db.all("SELECT * FROM AccountCosmetics WHERE accountID = ?", accountID)

    let allCosmetics: Cosmetic[] = [];
    await Promise.all(cosRes.map(async (cosmetic: any) => {
        let cos = await getCosmetic(cosmetic["cosmeticID"])
        cos.isActive = cosmetic["isActive"]
        allCosmetics.push(cos);
    }));

    return getActiveCosmetics(allCosmetics);
}

export async function setCosmeticActive(accountID: number, cosmeticID: number) {
    const cosCheck = await db.get("SELECT * FROM AccountCosmetics WHERE accountID = ? AND cosmeticID = ?", accountID, cosmeticID)
    if (cosCheck === undefined) {
        let res: PacketResponse = {
            code: 401,
            message: "You do not own this cosmetic!"
        }
        
        return res;
    }

    if (cosmeticID > 1000 && cosmeticID < 2000) {
        await db.run("UPDATE AccountCosmetics SET isActive = 0 WHERE accountID = ? AND cosmeticID BETWEEN 1000 AND 2000", accountID)
    } else if (cosmeticID > 2000 && cosmeticID < 3000) {
        await db.run("UPDATE AccountCosmetics SET isActive = 0 WHERE accountID = ? AND cosmeticID BETWEEN 2000 AND 3000", accountID)
    } else if (cosmeticID > 3000 && cosmeticID < 4000) {
        await db.run("UPDATE AccountCosmetics SET isActive = 0 WHERE accountID = ? AND cosmeticID BETWEEN 3000 AND 4000", accountID)
    } else if (cosmeticID > 4000 && cosmeticID < 5000) {
        await db.run("UPDATE AccountCosmetics SET isActive = 0 WHERE accountID = ? AND cosmeticID BETWEEN 4000 AND 5000", accountID)
    }
    
    await db.run("UPDATE AccountCosmetics SET isActive = 1 WHERE accountID = ? AND cosmeticID = ?", accountID, cosmeticID)

    let res: PacketResponse = {
        code: 200,
        message: "Cosmetic successfully set!"
    }

    return res
}

export async function updateItemShop(items: number[]) {
    for (let i = 0; i < items.length; i++) {
        await db.run("UPDATE ItemShop SET cosmeticID = ? WHERE rowID = ?", items[i], i + 1)
    }
}

export async function addAdmin(accountID: number, password: string) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    }

    const hash = await argon2.hash(password)
    const isAdmin = await db.get("SELECT * FROM Admins WHERE accountID = ?")
    if (isAdmin !== undefined) {
        packetRes.code = 400
        packetRes.message = "User is already admin!"
    } else {
        await db.run("INSERT INTO Admins (accountID, password) VALUES (?, ?)", accountID, hash)
        packetRes.code = 200
        packetRes.message = "User successfully added!"
    }

    return packetRes
}

export async function checkAdmin(hash: string) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    }

    const isAdmin = await db.get("SELECT * FROM Admins WHERE password = ?", hash)
    if (isAdmin !== undefined) {
        packetRes.code = 200
        packetRes.message = isAdmin["password"]
    } else {
        packetRes.code = 403
        packetRes.message = ""
    }

    return packetRes
}

export async function tryDashboardLogin(accountID: number, password: string) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    };

    const isAdmin = await db.get("SELECT * FROM Admins WHERE accountID = ?", accountID);
    if (isAdmin !== undefined) {
        if (await argon2.verify(isAdmin["password"], password)) {
            packetRes.code = 200
            
            let obj = {
                "token": isAdmin["password"]
            }
            packetRes.message = JSON.stringify(obj)

        } else {
            packetRes.code = 403
            packetRes.message = "Invalid username or password."
        }
    } else {
        packetRes.code = 403
        packetRes.message = "Invalid username or password."
    }

    return packetRes
}