# Server Integration

## 1. Get User Information

### 1.1 Flow
	
![alt text](https://github.com/xctcorporation/ServerIntegration/raw/master/get_user_info.png)
	
	
### 1.2. Description 

		1. Game Client calls a YKit function, then SDK show up the Login UI.
		2. YKit Client sends a login request to YKit server to validate the user info.
		3. YKit Client  receives the user info and accessToken from YKit server.
		4. YKit Client transfer the accessToken and user info to Game Client in order to notify there is a user login to game.
		5. Game Client create a login request with the accessToken and send it to Game Server.
		6. Game Server get the user information by sending the request to YKit server API with the accessToken as a parameter.
		7. Game Server receives User information from the YKit Server.
		8. Game Client receives Login Response and let the user join game.

### 1.3 YKit server API
- When users login or register to YKit system successfully, The access token will be passed from YKit system to your client. Access token is used to get the user information from your server-side.  
- To send a message, your Game Server issues a POST request.

		URL: https://api.ygame.vn/v1/user/user_info
		
	
| Name        | Description           | Note           |
| ------------- |:-------------:|:-------------:|
| accessToken      | Get from YKit system ||
| appId      | The id of your application is issued by YGame      ||
| sign | Md5 (accessToken + appId + appKey) |appKey: the secret key of your application is issued by YGame|

A successful response will contain your user information in JSON format:
```json
{
"status":1,
"msg":"",
"data":{
"userId":123
"username":"mario",
"dateCreate":"2017-09-20 14:59:28",
"dateUpdate":"2017-09-21 14:59:28",
"accessToken":"a0a6e4e4caebb1d799b7b49ed45ff71c",
"accessExpires":1474444768875,
    
}
}
```

If your request is not valid, you will be received the failure response
```json
{
"status":0,
"msg":"error description",
} 
```

## 2. Payment
### 2.1 Flow
	
![alt text](https://github.com/xctcorporation/ServerIntegration/blob/master/payment_flow.png)

### 2.2 Description
```
1. Game Client calls a YKit function setPaymentInfo to pass three paramerter: char_id, server_id, payment_id. These params will be post back to Server Game
2. YKit Client sends a payment request to YKit server.
3.  After processing the payment, YKit Server will send the notification to your Game Server via your callback url. Game Server will transfer game coin to user. 
4. Game Server return the payment response to YKit Server.
4.1. If game is based on socket technology, Game Server may notify the payment result to user at this time. 
5. YKit Client  receives the payment info from YKit server.
6. YKit Client calls Game Client function to notify there is a payment. 
6.1. Game Client  send a request to Game Server to check there is this payment or not.
6.2. If there is a successful payment, Game Client will notify the result to user.
NOTE: Step 6.1 and 6.2 just use for the game can’t send a message from server to client (like game using HTTP POST/GET to connect to server).  
```
### 2.3 Server Game Callback URL
- This is your own API to received the payment success request from YKit Server. Please build your API in GET method. When users finish the payment transaction in YKit system, YKit server will send the notification to your application server-side via your callback url with the following parameters.

| Name        | Description           |
| ------------- |:-------------:|
| amount      | Value of the purchase |
| app_id      | The id of your application is issued by YGame, use this parameter to classify android and ios       |
| response_time | Purchase time|
| transaction_id | id of the transaction|
| transaction_type | Type of purchase: CARD, BANK|
| currency | VN or USD |
| user_id | id of user, who make the request|
| char_id | id of character - get from function setPaymentInfo in YKit client|
| server_id | id of server game - get from function setPaymentInfo in YKit client|
| payment_id | id of payment package - get from function setPaymentInfo in YKit client|
| order_id | order id|
| card_code | * if transaction_type = CARD, card_code = code|
| card_serial | * if transaction_type = CARD, card_serial = serial|
| card_vendor | * if transaction_type = CARD, card_vendor = name|
| sign | Used to verify the request.

- Your API must be response the result in the JSON format as description in the table below

| Response        |JSON Format            |
| ------------- |:-------------:|
| success response      | {"status": "1", "msg":""} |
| Failure response      | {"status": "0", "msg":"reason"} |
