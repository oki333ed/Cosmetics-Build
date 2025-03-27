export interface Env {
	DB: D1Database;
	verify_password: string;
}

async function readRequestBody(request: Request) {
	return JSON.stringify(await request.json());
}

function buildErrorResponse(code: number, message: string): Response {
	let res: Response = Response.json(JSON.parse(`{"code": ${code}, "message": "${message}"}`), {status: code});
	return res;
}

function buildSuccessResponse(message: string): Response {
	let res: Response = Response.json(JSON.parse(`{"code": 200, "message": "${message}"}`), {status: 200});
	return res;
}

export default {
	async fetch(request, env): Promise<Response> {
		const {pathname} = new URL(request.url);
		switch(pathname) {
			case "/api/addCosmeticToUser": {
				if (request.method !== "POST") {
					return buildErrorResponse(400, "Wrong request type");
				}

				const reqBody = await readRequestBody(request);
				const parsedBody = JSON.parse(reqBody)

				const {results} = await env.DB.prepare(
					"SELECT * FROM AccountCosmetics WHERE accountID = ? AND cosmeticID = ?"
				)
				.bind(parsedBody["accountID"], parsedBody["cosmeticID"])
				.all();

				if (results.length !== 0) {
					return buildErrorResponse(401, "User already has this cosmetic");
				} else {
					await env.DB.prepare(
						"INSERT INTO AccountCosmetics (accountID, cosmeticID, isActive) VALUES (?, ?, ?)"
					)
					.bind(parsedBody["accountID"], parsedBody["cosmeticID"], parsedBody["isActive"])
					.run();

					return buildSuccessResponse(`Gave accountID ${parsedBody["accountID"]} cosmeticID ${parsedBody["cosmeticID"]}`);
				}
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
				if (request.method !== "POST") {
					return buildErrorResponse(400, "Wrong request type");
				}

				const reqBody = await readRequestBody(request);
				const {results} = await env.DB.prepare(
					"SELECT * FROM Accounts WHERE accountID = ?"
				)
				.bind(JSON.parse(reqBody)["accountID"])
				.all();

				if (results.length !== 0) {
					return buildErrorResponse(401, "Account already exists");
				} else {
					await env.DB.prepare(
						"INSERT INTO Accounts (accountID, creditsAmount) VALUES (?, 0)"
					)
					.bind(JSON.parse(reqBody)["accountID"])
					.run();

					return buildSuccessResponse("Successfully created user profile");
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
			`hello there :3`,
		);
	},
} satisfies ExportedHandler<Env>;