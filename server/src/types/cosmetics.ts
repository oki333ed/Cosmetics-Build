export type Cosmetic = {
    cosmeticID: number
    cosmeticName: string
    isActive: number
}

export enum CosmeticRarity {
    COMMON = 0,
    EPIC,
    LEGENDARY,
    MYTHIC
}

export type FullCosmetic = {
    cosmeticID: number
    cosmeticName: string
    cosmeticDescription: string
    cosmeticAmount: number
    cosmeticRarity: CosmeticRarity
    isActive: number
}

export type ActiveCosmetics = {
    hat: Cosmetic
    mask: Cosmetic
    object: Cosmetic
    particle: Cosmetic
}

export function activeCosmeticsGetActiveCosmetics(activeCosmetics: ActiveCosmetics): Cosmetic[] {
    let cosmetics: Cosmetic[] = [activeCosmetics.hat, activeCosmetics.mask, activeCosmetics.object, activeCosmetics.particle];

    return cosmetics;
}

export type AccountCosmetics = {
    hats: Cosmetic[]
    masks: Cosmetic[]
    objects: Cosmetic[]
    particles: Cosmetic[]
}

export function accountCosmeticsGetAccountCosmetics(accountCosmetics: AccountCosmetics): Cosmetic[][] {
    let cosmetics = [accountCosmetics.hats, accountCosmetics.masks, accountCosmetics.objects, accountCosmetics.particles]

    return cosmetics;
}