# Web Integration

### 1. Description.

	1. When user login successful in YKit system, user will be redirected to your game link to play game 
	with 2 params
	
	| Name        | Description                        | Note        |
	| ----------- |------------------------------------|-------------|
	| accessToken | token for verify, encoded by base64|             |
	| sign        | Md5 (accessToken + appId + appKey) |Used to verify the request. appId,appKey are provided
														by YGame|
   
   	Example : https://example.com/index.html?accessToken=...&sign=...

    2. After verify request successful, your server will decode accessToken and verify this accessToken
     with YKit system

### 2 Verify acccessToken.

    https://github.com/ygame11092017/ykit-wiki/blob/master/server/README.md#13-ykit-server-api

