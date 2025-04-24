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

## Item Shop Packets
* 3001 - GetItemShopPacket
* 3002 - UpdateItemShopPacket

## Dashboard Packets
* 4001 - TryLoginPacket
* 4002 - AddAdminPacket
* 4003 - CheckAdminPacket

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

## Item Shop Packets
* 13001 - ReturnItemShopPacket
* 13002 - UpdatedItemShopPacket

## Dashboard Packets
* 14001 - DoLoginPacket
* 14002 - AddedAdminPacket
* 14003 - IsAdminPacket