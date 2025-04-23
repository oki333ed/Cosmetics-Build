import path from 'node:path';

import { WebSocketExpress } from 'websocket-express';
import * as express from "express"

import * as database from './database/database';
import { apiRouter } from './routes/api';

const app = new WebSocketExpress();
const port = 8787;

app.use("/api", apiRouter);

app.use("/dashboard", express.static(path.join(__dirname, "webui")))

database.init()

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});