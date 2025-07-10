import 'dotenv/config'

import { WebSocketExpress } from 'websocket-express';

import * as database from './database/database';
import { apiRouter } from './routes/api';

const app = new WebSocketExpress();
const port = parseInt(process.env.PORT as string) | 8787

app.use("/api", apiRouter);

app.get("/", (req, res) => {
    res.send("hi there silly :3")
})

database.init()

app.listen(port, () => {
    console.log(`Server running at http://localhost:${process.env.PORT}`);
});