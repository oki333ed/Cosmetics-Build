class Packet {
    constructor(packetID, data) {
        this.packetID = packetID
        this.data = data
    }

    serialize() {
        const obj = {
            "packetID": this.packetID,
            "data": this.data
        }

        return JSON.stringify(obj)
    }
}