import { Request, Response } from "express";

import {Router} from "websocket-express";

export const apiRouter = new Router();

apiRouter.get("/", (req: Request, res: Response) => {
    res.send("hi there cutie :3");
});

apiRouter.ws("/wstest", async (req, res) => {
	const ws = await res.accept();
	ws.on('message', (msg) => {
		console.log(`message: ${msg}`);
	});
});