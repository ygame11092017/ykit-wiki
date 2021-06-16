# 1. Web Integration

### 1. Description.
	- Partner will provide a api for get link for playing game in browser
	- YGame will call that api with below params, partner will verify and return a link, YGame will use this link embed to browser for user playing game
	
	| Name        | Description                        | Note        |
	| ----------- |------------------------------------|-------------|
	| accessToken | token for verify, encoded by base64|             |
	| sign        | Md5 (accessToken + appId + appSecret) |Used to verify the request. appId,appSecret are provided by YGame|
 
### 2 Verify acccessToken

    https://github.com/ygame11092017/ykit-wiki/blob/master/server/README.md#13-ykit-server-api

# 2. Character Logout Ingame

### 1. Description.
	- Partner will provide a api for logout character in game
	- YGame will call that api with below params, partner will verify and logout user
	_ Method API: GET
	
	| Name        | Description                        | Note        |
	| ----------- |------------------------------------|-------------|
	| accessToken | token for verify, encoded by base64|             |
	
	- Response: return the result in json format. For example: A user have three characters in the server S2. Their names are herror, warrior, king. The result will be returned as below
```
{
  "status":1,
  "msg":"",
}
```
 
### 2 Verify acccessToken

    https://github.com/ygame11092017/ykit-wiki/blob/master/server/README.md#13-ykit-server-api
