import { ExtendedWebSocket } from "websocket-express";
import { updateItemShop } from "../database/database";
import { buildPacket } from "./packets";

export function handleItemShopPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    switch (parsedMSG["packetID"]) {
        case 3001: {
            getItemShopPacket(parsedMSG, ws)
            break
        }

        case 3002: {
            updateItemShopPacket(parsedMSG, ws)
            break
        }
    }
}

function getItemShopPacket(parsedMSG: any, ws: ExtendedWebSocket) {

}

function updateItemShopPacket(parsedMSG: any, ws: ExtendedWebSocket) {
    updateItemShop(parsedMSG["data"]["items"]).then(() => {
        ws.send(buildPacket(13002, {
            "message": "Updated successfully!"
        }))
    })
}