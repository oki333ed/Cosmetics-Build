import { AccountCosmetics, ActiveCosmetics } from "./cosmetics";

export interface User {
    accountID: number,
    creditsAmount: number,
    activeCosmetics: ActiveCosmetics,
    allCosmetics: AccountCosmetics,
}