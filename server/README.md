## Prerequisites
* A [Cloudflare Account](https://dash.cloudflare.com/sign-up/workers-and-pages)
* [Node.js](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm)

## Build Instructions
1. Create the prod-cosmetics DB `npx wrangler d1 create prod-cosmetics`
2. Install all packages `npm install`
3. Initialize schema `npx wrangler d1 execute prod-cosmetics --local --file=./schemas/schema.sql`
4. Run `npm run dev`

To deploy this worker to the web
1. Bootstrap DB with schema file `npx wrangler d1 execute prod-cosmetics --remote --file=./schemas/schema.sql`
2. Deploy `npx wrangler deploy`

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
* `/api/createUser` POST Request
  * Body Params
    * accountID - int
  * Returns
    * 200 - Successfully added
    * 400 - Wrong request type
* `/api/getAccount` GET Request
  * URL Params
    * accountID - int
  * Returns
    * JSON Object with accountID and creditsAmount