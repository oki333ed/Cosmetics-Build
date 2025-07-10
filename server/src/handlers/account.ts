import { ExtendedWebSocket } from "websocket-express";
import { buildPacket } from "./packets";
import { createUser, getUserInfo, updateUser } from "../database/database";
import { AccountCosmetics, ActiveCosmetics } from "../types/cosmetics";

export function handleAccountPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    switch (parsedMsg["packetID"]) {
        case 1001: {
            createUserPacket(parsedMsg, ws);
            break;
        }

        case 1002: {
            updateUserPacket(parsedMsg, ws);
            break;
        }

        case 1003: {
            requestUserPacket(parsedMsg, ws);
            break;
        }
    }
}

function createUserPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    createUser(parsedMsg["data"]["accountID"], parsedMsg["data"]["token"]).then((message) => {
        ws.send(buildPacket(10001, message))
    })
}

function updateUserPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    let activeCosmetics: ActiveCosmetics = parsedMsg["data"]["activeCosmetics"];
    let accountCosmetics: AccountCosmetics = parsedMsg["data"]["accountCosmetics"];
    updateUser(parsedMsg["data"]["accountID"], parsedMsg["data"]["creditsAmount"], activeCosmetics, accountCosmetics).then((userInfo) => {
        ws.send(buildPacket(10002, userInfo))
    })
}

function requestUserPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    getUserInfo(parsedMsg["data"]["accountID"]).then((userInfo) => {
        ws.send(buildPacket(10002, userInfo))
    })
}