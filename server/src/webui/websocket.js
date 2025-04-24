const API_URL = "ws://127.0.0.1:8787/api/handlews"
const websocket = new WebSocket(API_URL)

function sendData(data) {
    if (websocket.OPEN) {
        websocket.send(data.serialize())
    }
}

websocket.addEventListener("message", (event) => {
    const parsedMSG = JSON.parse(event.data)
    switch (parsedMSG["packetID"]) {
        case 12004: {
            allCosmeticsPacket(parsedMSG)
            break
        }

        case 13002: {

        }

        case 14001: {
            doLoginPacket(parsedMSG)
            break
        }

        case 14003: {
            isAdminPacket(parsedMSG)
            break
        }
    }
})

function allCosmeticsPacket(parsedMSG) {
    const itemShopSelects = document.querySelectorAll("#item-select")
    parsedMSG["data"].forEach((cosmetic) => {
        itemShopSelects.forEach((select) => {
            const option = document.createElement("option")
            option.value = cosmetic["cosmeticID"]
            option.text = cosmetic["cosmeticName"]
            select.appendChild(option)
        })
    })
}

function doLoginPacket(parsedMSG) {
    if (parsedMSG["data"]["code"] === 403) {
        alert("Error: " + parsedMSG["data"]["message"])
    } else if (parsedMSG["data"]["code"] === 200) {
        const token = JSON.parse(parsedMSG["data"]["message"])["token"]
        document.cookie = `token=${token}`
        window.location.href = "dashboard.html"
    }
}

function isAdminPacket(parsedMSG) {
    let tokenCookie;
    document.cookie.split(";").forEach(cookie => {
        const parts = cookie.split('=')
        if (parts[0].trim() === "token") {
            const value = decodeURIComponent(parts.slice(1).join('='))
            tokenCookie = value
        }
    })

    if (parsedMSG["data"]["code"] === 403) {
        window.location.href = "index.html"
    } else if (parsedMSG["data"]["code"] === 200) {
        if (tokenCookie !== parsedMSG["data"]["message"]) {
            window.location.href = "index.html"
        } else {
            return
        }
    }
}