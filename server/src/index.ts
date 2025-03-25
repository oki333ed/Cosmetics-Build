export interface Env {
	DB: D1Database;
}

async function readRequestBody(request: Request) {
	return JSON.stringify(await request.json());
}

export default {
	async fetch(request, env): Promise<Response> {
		const {pathname} = new URL(request.url);
		switch(pathname) {
			case "/api/addCosmeticToUser": {
				const error = '{"error": 400}'
				if (request.method !== "POST") {
					return Response.json(JSON.parse(error))
				}

				const reqBody = await readRequestBody(request);
				const parsedBody = JSON.parse(reqBody)
				await env.DB.prepare(
					"INSERT INTO AccountCosmetics (accountID, cosmeticID, isActive) VALUES (?, ?, ?)"
				)
				.bind(parsedBody["accountID"], parsedBody["cosmeticID"], parsedBody["isActive"])
				.run();

				const code = '{"code": 200}'
				return Response.json(JSON.parse(code));
			}

			case "/api/cosmetics": {
				const {results} = await env.DB.prepare(
					"SELECT * FROM Cosmetics"
				)
				.all();
	
				return Response.json(results);
			}

			case "/api/cosmeticsForUser": {
				const {results} = await env.DB.prepare(
					"SELECT * FROM AccountCosmetics WHERE accountID = ?"
				)
				.bind(new URL(request.url).searchParams.get("accountID"))
				.all();

				return Response.json(results);
			}

			case "/api/createUser": {
				const error = '{"error": 400}'
				if (request.method !== "POST") {
					return Response.json(JSON.parse(error))
				}

				const reqBody = await readRequestBody(request);
				const {results} = await env.DB.prepare(
					"SELECT * FROM Accounts WHERE accountID = ?"
				)
				.bind(JSON.parse(reqBody)["accountID"])
				.all();

				if (results.length !== 0) {
					return Response.json(JSON.parse(error))
				} else {
					await env.DB.prepare(
						"INSERT INTO Accounts (accountID, creditsAmount) VALUES (?, 0)"
					)
					.bind(JSON.parse(reqBody)["accountID"])
					.run();

					const code = '{"code": 200}'
					return Response.json(JSON.parse(code));
				}
			}

			case "/api/getAccount": {
				const {results} = await env.DB.prepare(
					"SELECT * FROM Accounts WHERE accountID = ?"
				)
				.bind(new URL(request.url).searchParams.get("accountID"))
				.all();
	
				return Response.json(results);
			}
		}

		return new Response (
			"hello there :3",
		);
	},
} satisfies ExportedHandler<Env>;