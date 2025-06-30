CREATE TABLE IF NOT EXISTS Cosmetics (
    cosmeticID INTEGER PRIMARY KEY,
    cosmeticName TEXT,
    cosmeticDescription TEXT,
    cosmeticAmount INTEGER,
    cosmeticRarity INTEGER
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
    accountID INTEGER PRIMARY KEY,
    password TEXT
);

INSERT INTO Cosmetics (cosmeticID, cosmeticName, cosmeticDescription, cosmeticAmount, cosmeticRarity) VALUES 
    (1001, 'Teto Hair', 'Every Miku needs their own Teto', 1000, 0),
    (1002, 'Leaf', 'Who doesnt wanna turn beautiful in Autumn?', 1000, 0),
    (1003, 'Halo', 'A fallen angel... now beating Stereo Madness!', 1000, 0),
    (1004, 'Little Boat', 'Georgie used to have one of these, now you do!', 1000, 0),
    (2001, 'Freddy Fazbear', 'The animatronics here get a little quirky at night...', 1000, 0),
    (2002, 'Hearts', 'Valentines Day came early!', 5000, 1),
    (3001, 'Test Object', 'test object', 1000, 0),
    (4001, 'Test Particle Effect', 'test particles', 1000, 0);