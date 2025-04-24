import { ExtendedWebSocket } from "websocket-express";
import { addAdmin, checkAdmin, tryDashboardLogin } from "../database/database";
import { buildPacket } from "./packets";

export function handleDashboardPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    switch (parsedMSG["packetID"]) {
        case 4001: {
            tryLoginPacket(parsedMSG, ws);
            break;
        }

        case 4002: {
            addAdminPacket(parsedMSG, ws);
            break;
        }

        case 4003: {
            checkAdminPacket(parsedMSG, ws);
            break;
        }
    }
}

function tryLoginPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    tryDashboardLogin(parsedMSG["data"]["accountID"], parsedMSG["data"]["password"]).then((res) => {
        ws.send(buildPacket(14001, res));
    })
}

function addAdminPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    addAdmin(parsedMSG["data"]["accountID"], parsedMSG["data"]["password"]).then((res) => {
        ws.send(buildPacket(14002, res))
    })
}

function checkAdminPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    checkAdmin(parsedMSG["data"]["hash"]).then((res) => {
        ws.send(buildPacket(14003, res))
    })
}