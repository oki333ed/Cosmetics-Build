# Protocol

A little documentation on all the packets

# Client
All the client packets

## Account Packets
* 1001 - CreateUserPacket
* 1002 - UpdateUserPacket
* 1003 - RequestUserPacket
* 1004 - RequestAuthPacket

## Cosmetics Packets
* 2001 - AddCosmeticPacket
* 2002 - SetCosmeticActivePacket
* 2003 - RequestUserCosmeticsPacket
* 2004 - RequestAllCosmeticsPacket

# Server
All the server packets

## Account Packets
* 10001 - UserCreatedPacket
* 10002 - UserDataPacket
* 10003 - UserAuthPacket

## Cosmetics Packets
* 12001 - CosmeticAddedPacket
* 12002 - CosmeticSetActivePacket
* 12003 - UserCosmeticsPacket
* 12004 - AllCosmeticsPacket