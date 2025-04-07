import * as sqlite3 from "sqlite3";
import {open, Database} from 'sqlite';
import { User } from "../types/user";
import { Cosmetic } from "../types/cosmetics";
import { filterAllCosmetics, getActiveCosmetics } from "../utils";
import { PacketResponse } from "../types/response";

let db: Database<sqlite3.Database, sqlite3.Statement>;
let dbPath = "./database.db"

export async function init() {
    db = await open({
        filename: dbPath,
        driver: sqlite3.Database
    })
}

export async function createUser(accountID: number) {
    let packetRes: PacketResponse = {
        code: 0,
        message: ''
    };

    const doesAccExist = await db.get("SELECT * FROM Accounts WHERE accountID = ?", accountID)
    if (doesAccExist !== undefined) {
        packetRes.code = 401;
        packetRes.message = "Account already exists!"
    } else {
        await db.run("INSERT INTO Accounts (accountID, creditsAmount) VALUES (?, 0)", accountID)
        packetRes.code = 200;
        packetRes.message = "Account created successfully!"
    }

    return packetRes;
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
    cosRes.forEach((cosmetic: any) => {
        getCosmetic(cosmetic["cosmeticID"]).then((cos) => {
            cos["isActive"] = cosmetic["isActive"];
            allCosmetics.push(cos);
        })
    });

    const user: User = {
        accountID: accountID,
        creditsAmount: accRes["creditsAmount"],
        activeCosmetics: getActiveCosmetics(allCosmetics),
        allCosmetics: filterAllCosmetics(allCosmetics),
    };

    return user
}