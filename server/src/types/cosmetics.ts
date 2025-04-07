export type Cosmetic = {
    cosmeticID: number
    cosmeticName: string
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