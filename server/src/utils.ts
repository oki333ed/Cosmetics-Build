import { AccountCosmetics, ActiveCosmetics, Cosmetic } from "./types/cosmetics";

export function filterAllCosmetics(cosmetics: Cosmetic[]): AccountCosmetics {
    let allCosmetics: AccountCosmetics = {
        hats: [],
        masks: [],
        objects: [],
        particles: []
    }

    cosmetics.forEach((cosmetic: Cosmetic) => {
        if (cosmetic.cosmeticID > 1000 && cosmetic.cosmeticID < 2000) {
            allCosmetics.hats.push(cosmetic)
        } else if (cosmetic.cosmeticID > 2000 && cosmetic.cosmeticID < 3000) {
            allCosmetics.masks.push(cosmetic)
        } else if (cosmetic.cosmeticID > 3000 && cosmetic.cosmeticID < 4000) {
            allCosmetics.objects.push(cosmetic)
        } else if (cosmetic.cosmeticID > 4000 && cosmetic.cosmeticID < 5000) {
            allCosmetics.particles.push(cosmetic)
        }
    })

    return allCosmetics;
}

export function getActiveCosmetics(cosmetics: Cosmetic[]): ActiveCosmetics {
    const accountCosmetics = filterAllCosmetics(cosmetics);

    let hat: any = accountCosmetics.hats.find((hat) => hat.isActive === 1);
    let mask: any = accountCosmetics.masks.find((mask) => mask.isActive === 1);
    let object: any = accountCosmetics.objects.find((object) => object.isActive === 1);
    let particle: any = accountCosmetics.particles.find((particle) => particle.isActive === 1);

    if (hat === undefined) hat = null
    if (mask === undefined) mask = null
    if (object === undefined) object = null
    if (particle === undefined) particle = null

    let activeCosmetics: ActiveCosmetics = {
        hat: hat,
        mask: mask,
        object: object,
        particle: particle
    }

    return activeCosmetics;
}