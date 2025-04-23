CREATE TABLE IF NOT EXISTS Cosmetics (
    cosmeticID INTEGER PRIMARY KEY,
    cosmeticName TEXT,
    cosmeticAmount INTEGER
);

CREATE TABLE IF NOT EXISTS Accounts (
    accountID INTEGER PRIMARY KEY, 
    creditsAmount INTEGER
);

CREATE TABLE IF NOT EXISTS AccountCosmetics (
    accountID INTEGER,
    cosmeticID INTEGER,
    isActive INTEGER
);

CREATE TABLE IF NOT EXISTS Admins (
    accountID INTEGER PRIMARY KEY
);

INSERT INTO Cosmetics (cosmeticID, cosmeticName, cosmeticAmount) VALUES 
    (1001, 'Test Hat', 1000), 
    (2001, 'Test Mask', 1000), 
    (3001, 'Test Object', 1000),
    (4001, 'Test Particle Effect', 1000);