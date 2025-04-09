import { ExtendedWebSocket } from "websocket-express";
import { addCosmetic, getUserCosmetics, setCosmeticActive } from "../database/database";
import { buildPacket } from "./packets";

export function handleCosmeticPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    switch (parsedMSG["packetID"]) {
        case 2001: {
            addCosmeticPacket(parsedMSG, ws)
            break;
        }

        case 2002: {
            setCosmeticActivePacket(parsedMSG, ws)
            break;
        }

        case 2003: {
            requestUserCosmeticsPacket(parsedMSG, ws)
            break;
        }
    }
}

function addCosmeticPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    addCosmetic(parsedMSG["data"]["accountID"], parsedMSG["data"]["cosmeticID"], (parsedMSG["data"]["isActive"] === 0) ? false : true).then((res) => {
        ws.send(buildPacket(12001, res))
    })
}

function setCosmeticActivePacket(parsedMSG: any, ws: ExtendedWebSocket) {
    setCosmeticActive(parsedMSG["data"]["accountID"], parsedMSG["data"]["cosmeticID"]).then((res) => {
        ws.send(buildPacket(12002, res))
    })
}

function requestUserCosmeticsPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    getUserCosmetics(parsedMSG["data"]["accountID"]).then((cosmetics) => {
        ws.send(buildPacket(12003, cosmetics))
    })
}