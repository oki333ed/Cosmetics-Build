FROM node:24-alpine

WORKDIR /app

RUN apk add --no-cache sqlite sqlite-dev bash

COPY package*.json ./
RUN npm install

COPY . .

RUN sqlite3 database.db < schemas/schema.sql

EXPOSE 8787

CMD ["sh", "-c", "npm run build && npm run serve"]
