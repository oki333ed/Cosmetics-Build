## build instructions
1. Install all packages `npm install`
2. Initialize schema `npx wrangler d1 execute prod-cosmetics --local --file=./schemas/schema.sql`
3. Run `npm run dev`

# Endpoints
All the endpoints for the server  
(disclaimer - sqlite doesnt have many types so im simplifying them next to their true type)

## Cosmetics Endpoints
* `/api/addCosmeticToUser` POST Request
  * Body Params
    * accountID - int
    * cosmeticID - int
    * isActive - int (bool)
  * Returns
    * 200 - Successfully added
    * 400 - Wrong request type
* `/api/cosmetics` GET Request
  * Returns
    * JSON Object with all the cosmetics
* `/api/cosmeticsForUser` GET Request
  * URL Params
    * accountID - int
  * Returns
    * JSON Object with all the cosmetics for a specific accountID

## Account Endpoints
* `api/getAccount` GET Request
  * URL Params
    * accountID - int
  * Returns
    * JSON Object with accountID and creditsAmount