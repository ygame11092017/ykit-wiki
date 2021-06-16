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
	_ Method API: POST
	
	| Name        | Description                        | Note                               |
	| ----------- |------------------------------------|------------------------------------|
	| accessToken | token for verify, encoded by base64|This is YGame User Token            |
	
- Response: return the result in json format.
```
{
  "status":1,
  "msg":"",
}
```
- Your API must be response the result in the JSON format as description in the table below

| Response        |JSON Format            |
| ------------- |:-------------:|
| success response      | {"status": "1", "msg":""} |
| Failure response      | {"status": "error_code", "msg":"reason"} |

| Error code        |Reason            |
| ------------- |:-------------:|
| -1      | system error |
| -2      | invalid character id|
| -3      | invalid server id|
| -4      | invalid payment id |
| -5      | unknow error |
### 2 Verify acccessToken

    https://github.com/ygame11092017/ykit-wiki/blob/master/server/README.md#13-ykit-server-api
