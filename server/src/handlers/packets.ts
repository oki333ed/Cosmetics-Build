export function buildPacket(packetID: number, data: object): string {
    const obj = `{
        "packetID": ${packetID},
        "data": ${JSON.stringify(data)}
    }`

    return obj;
}