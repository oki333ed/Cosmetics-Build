## Prerequisites
* [Node.js](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm)
* [SQLite3](https://sqlite.org/cli.html)

## Build Instructions
1. Create the database file `sqlite3 filename.db < schemas/schema.sql`
2. Install all the packages `npm install`
3. Run the server
    * If running locally, do either `npm start` or `npm run watch`
    * If building for production, run `npm run build` then `npm run serve`

# Endpoints
All the endpoints for the server  
(disclaimer - SQLite doesnt have many types so im simplifying them next to their true type)

## Cosmetics Endpoints
* `/api/addCosmeticToUser` Websocket Request
  * Body Params
    * accountID - int
    * cosmeticID - int
    * isActive - int (bool)
  * Returns
    * 200 - Successfully added
* `/api/cosmetics` GET Request
  * Returns
    * JSON Object with all the cosmetics
* `/api/cosmeticsForUser` GET Request
  * URL Params
    * accountID - int
  * Returns
    * JSON Object with all the cosmetics for a specific accountID
* `/api/setCosmeticActive` Websocket Request
  * Body Params
    * accountID - int
    * cosmeticID - int
  * Returns
    * 200 - Successfully set

## Account Endpoints
* `/api/createUser` Websocket Request
  * Body Params
    * accountID - int
  * Returns
    * 200 - Successfully added
    * 401 - Account already exists
* `/api/getAccount` GET Request
  * URL Params
    * accountID - int
  * Returns
    * JSON Object with accountID and creditsAmount