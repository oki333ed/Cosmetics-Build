import { apiRouter } from './routes/api';
import { WebSocketExpress, Router } from 'websocket-express';

const app = new WebSocketExpress();
const port = 8787;

app.use("/api", apiRouter);

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});