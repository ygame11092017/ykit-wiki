# Server Integration

## 1. Get User Information

### 1.1 Flow
	
![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/get_user_info.png)
	
	
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

## 2. Web Payment
This is the YGame Payment System on Web. User can purchase the game content by using the YGame Web Payment
### 2.1. Flow
![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/web_flow.jpg)

- 1: User login to YGame System
- 2: API get list server game. This is the HTTP GET provided by Server Game to return the list of server game 
- 3: API get list character. This is the HTTP GET provided by Server Game to return the list of characters base on the selected server game 
- 4: API get list payment. This is the HTTP GET provided by Server Game to return all purchase packages which offer in the game
- 5: Pay with YGame System via Card, Banking ...
- 6: API payment success. Called when user make the payment successfully

### 2.2. API get list server game
This is your own API to return the list of your server game.
- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of YKit account
  + sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#21-api-get-list-server-game)
  
- Response: return the result in json format. For example: your game has four server games. The response will be returned as below
```
{
  "status":1,
  "msg":"",
  "data":[
    {"server_name":"S1","server_id":1},
    {"server_name":"S2","server_id":2},
    {"server_name":"S3","server_id":3},
    {"server_name":"S4","server_id":4}
  ]
}
```

### 2.3 API get list charaters
This is your own API to return the list of characters in game
- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of YKit account
  + server_id: id of server game. Get from the previous step
  + sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#22-api-get-list-characters)
  
- Response: return the result in json format. For example: A user have three characters in the server S2. Their names are herror, warrior, king. The result will be returned as below
```
{
  "status":1,
  "msg":"",
  "data":[
    {"char_name":"hero","char_id":"123", "char_level":8},
    {"char_name":"warrior","char_id":"456", "char_level":20},
    {"char_name":"king","char_id":"999", "char_level":35}
  ]
}
```

### 2.4. API get list payment
This is your own API to return the list payment packages of your game
![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/payment_packages.png)

- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of YKit account
  + char_id: id of character in game. Get from the previous step
  + server_id: id of server game
  + sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#23-api-get-list-payment)
  
- Response: return the result in json format. For example: the response is corresponding to the screenshot above
```
{
  "status":1,
  "msg":"",
  "data":[
    {"name":"80 Nguyen Bao","id":"80_nb", "type":"normal"},
    {"name":"200 Nguyen Bao","id":"200_nb", "type":"normal"},
    {"name":"400 Nguyen Bao","id":"400_nb", "type":"normal"},
    {"name":"2000 Nguyen Bao","id":"2000_nb", "type":"normal"},
    {"name":"4000 Nguyen Bao","id":"4000_nb", "type":"normal"},
    {"name":"6000 Nguyen Bao","id":"6000_nb", "type":"normal"},
    {"name":"20000 Nguyen Bao","id":"20000_nb", "type":"normal"},
    {"name":"350kc /ngay","id":"350kc", "type":"special"},
    {"name":"450kc /ngay","id":"450kc", "type":"special"}
  ]
}
```
- Type:
  + normal: normal package, for example, purchare for gold, coin
  + special: some special packages, for example: weekly, daily



## 3. Payment
### 3.1 Flow
	
![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/payment_flow.png)

### 3.2 Description
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
### 3.3 Server Game Callback URL
- This is your own API to received the payment success request from YKit Server. Please build your API in GET method. When users finish the payment transaction in YKit system, YKit server will send the notification to your application server-side via your callback url with the following parameters.

| Name        | Description           |
| ------------- |:-------------:|
| amount      | Value of the purchase |
| app_id      | The id of your application is issued by YGame, use this parameter to classify android and ios       |
| response_time | Purchase time|
| transaction_id | id of the transaction|
| transaction_type | Type of purchase: COIN|
| user_id | id of user, who make the request|
| char_id | id of character - get from function setPaymentInfo in YKit client|
| server_id | id of server game - get from function setPaymentInfo in YKit client|
| payment_id | id of payment package - get from function setPaymentInfo in YKit client|
| order_id | order id|
| sign | Used to verify the request.

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


