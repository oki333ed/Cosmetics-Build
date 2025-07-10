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
    accountID INTEGER PRIMARY KEY,
    password TEXT
);

<<<<<<< Updated upstream
CREATE TABLE IF NOT EXISTS ItemShop (
    rowID INTEGER PRIMARY KEY,
    cosmeticID INTEGER
);

INSERT INTO Cosmetics (cosmeticID, cosmeticName, cosmeticAmount) VALUES 
    (1001, 'Test Hat', 1000), 
    (2001, 'Test Mask', 1000), 
    (3001, 'Test Object', 1000),
    (4001, 'Test Particle Effect', 1000);
=======
INSERT INTO Cosmetics (cosmeticID, cosmeticName, cosmeticDescription, cosmeticAmount, cosmeticRarity) VALUES 
    (1001, 'Teto Hair', 'Every Miku needs their own Teto', 1000, 0),
    (1002, 'Toxic Pin', 'Slimy business', 1000, 0),
    (1003, 'Bocchi', 'Bocchi the Rock!', 1000, 0),
    (1004, 'Bow Tie', 'You gotta have a little class while playing', 5000, 1),
    (1005, 'Stolas Hat', 'This bird got style!', 10000, 2),
    (1006, 'Cat Ears Hat', 'mrrow mrrp mrrp meow', 5000, 1),
    (1007, 'Copper Golem', 'Sorting your mind', 1000, 0),
    (1008, 'Crown', 'You think youre the king? Im the king!', 1000, 0),
    (1009, 'Egg', 'Sunny side, over easy, doesnt matter!', 1000, 0),
    (1010, 'Flower Crown', 'The only crown you will ever need!', 5000, 1),
    (1011, 'Horns', 'For the demon inside', 1000, 0),
    (1012, 'Nikos Hat', 'Im NOT a cat!!', 10000, 2),
    (1013, 'Paws', '(New Pawdest)', 5000, 1),
    (1014, 'Plumbob', 'ji mebofiwe tukiwe sijimosi!', 5000, 1),
    (1015, 'Soul', 'Deltarune Soon TM', 5000, 1),
    (2001, 'Freddy Fazbear', 'The animatronics here get a little quirky at night...', 5000, 1),
    (2002, 'Hearts', 'Valentines Day came early!', 5000, 1),
    (2003, 'Ice Shards', 'BAKA!!', 10000, 2),
    (2004, 'Dragon Wings', 'Here be dragons', 25000, 3),
    (2005, 'Preleak swords', 'This cosmetic has been canceled', 25000, 3),
    (2006, 'Flowey', 'Kill or be Killed.', 10000, 2),
    (2007, 'Knife', 'Its like Friday the 13th all over again!', 1000, 0),
    (3001, 'Test Object', 'test object', 1000, 0),
    (4001, 'Test Particle Effect', 'test particles', 1000, 0);
>>>>>>> Stashed changes
