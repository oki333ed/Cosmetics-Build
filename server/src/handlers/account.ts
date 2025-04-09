import { ExtendedWebSocket } from "websocket-express";
import { buildPacket } from "./packets";
import { createUser, getUserInfo } from "../database/database";

export function handleAccountPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    switch (parsedMsg["packetID"]) {
        case 1001: {
            createUserPacket(parsedMsg, ws);
            break;
        }

        case 1003: {
            requestUserPacket(parsedMsg, ws);
            break;
        }
    }
}

function createUserPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    createUser(parsedMsg["data"]["accountID"]).then((message) => {
        ws.send(buildPacket(10001, message))
    })
}

function requestUserPacket(parsedMsg: any, ws: ExtendedWebSocket) {
    getUserInfo(parsedMsg["data"]["accountID"]).then((userInfo) => {
        ws.send(buildPacket(10002, userInfo))
    })
}