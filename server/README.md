## Prerequisites
* [Node.js](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm)
* [SQLite3](https://sqlite.org/cli.html)

## Build Instructions
1. Create the database file `sqlite3 <filename>.db < schemas/schema.sql`
2. Install all the packages `npm install`
3. Run the server
    * If running locally, do either `npm start` or `npm run watch`
    * If building for production, run `npm run build` then `npm run serve`