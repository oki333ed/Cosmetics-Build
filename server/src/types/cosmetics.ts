export type Cosmetic = {
    cosmeticID: number
    isActive: number
}

export type ActiveCosmetics = {
    hat: Cosmetic
    mask: Cosmetic
    object: Cosmetic
    particle: Cosmetic
}

export type AccountCosmetics = {
    hats: Cosmetic[]
    masks: Cosmetic[]
    objects: Cosmetic[]
    particles: Cosmetic[]
}