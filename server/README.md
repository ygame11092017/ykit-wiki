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

| Name        |                             Description                                        |                        Note                                   |
| ----------- | :----------------------------------------------------------------------------: | :-----------------------------------------------------------: |
| accessToken |                              Get from YKit system                              |                                                               |
| appId       | The id of your application, use this parameter to classify android and ios     |                                                               |
| sign        |                       Md5 (accessToken + appId + appKey)                       | appKey: the secret key of your application is issued by YGame |

A successful response will contain your user information in JSON format:

```json
{
  "status": 1,
  "msg": "",
  "data": {
    "userId": 123,
    "username": "username123",
    "...": "..."
  }
}
```

\*\*\*\* Note: userId is unique, other informations can change

If your request is incorrect, you will be received the failure response

```json
{
  "status": 0,
  "msg": "error description"
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
  - app_id: The id of your application, use this parameter to classify android and ios
  - user_id: id of YKit account
  - sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#11-api-get-list-server-game)
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

- Note:
  - server_name : string
  - server_id : integer

### 2.3 API get list charaters

This is your own API to return the list of characters in game

- Method: HTTP GET
- Params:
  - app_id: The id of your application, use this parameter to classify android and ios
  - user_id: id of YKit account
  - server_id: id of server game. Get from the previous step
  - sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#12-api-get-list-characters)
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

- Note:
  - char_id : string
  - char_name : string
  - char_level : integer

### 2.4. API get list payment

This is your own API to return the list payment packages of your game
![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/payment_packages.png)

- Method: HTTP GET
- Params:
  - app_id: The id of your application, use this parameter to classify android and ios
  - user_id: id of YKit account
  - char_id: id of character in game. Get from the previous step
  - server_id: id of server game
  - sign: Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#13-api-get-list-payment)
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

- Note:

  - name : string
  - id : string ( ~ payment_id in payment file (excel) from YGame )
  - type : string

- Type:
  - normal: normal package, for example, purchare for gold, coin
  - special: some special packages, for example: weekly, daily

## 3. Payment Callback URL

- This is your own API to received the payment success request from YKit Server. Please build your API in GET method. When users finish the payment transaction in YKit system, YKit server will send the notification to your application server-side via your callback url with the following parameters.

| Name             |                                                                                    Description                                                                                              |
| ---------------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| amount           |                                                                                    Value of the purchase                                                                                    |
| app_id           |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| response_time    |                                                                                        Purchase time                                                                                        |
| transaction_id   |                                                                                    id of the transaction                                                                                    |
| transaction_type |                                                                                   Type of purchase: COIN                                                                                    |
| user_id          |                                                                              id of user, who make the request                                                                               |
| char_id          |                                                                                       id of character                                                                                       |
| server_id        |                                                                                      id of server game                                                                                      |
| payment_id       |                                                                                    id of payment package                                                                                    |
| order_id         |                                                                                          order id                                                                                           |
| sign             | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

- Your API must be response the result in the JSON format as description in the table below

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

| Error code       |   Reason             |
| ---------------- | :------------------: |
| -1               |     system error     |
| -2               | invalid character id |
| -3               |  invalid server id   |
| -4               |  invalid payment id  |
| -5               |     unknow error     |

## 4. Push notification

- When you want to push notification to user. Use the API below

URL: https://api.ygame.vn/v1/user/push_notify

Params:

| Name        |                                       Description                                                  |
| ----------- | :------------------------------------------------------------------------------------------------: |
| appId       | The id of your application is issued by YGame, use this parameter to classify android and ios      |
| accessToken |                                        Get from YKit system                                        |
| msgid       |                                        equals to payment_id                                        |
| sign        |         Used to verify the request. sign = (md5(accessToken + appId + msgid + secretKey))          |

- Flow
  ![alt text](https://github.com/ygame11092017/ykit-wiki/blob/master/server/guide_push.jpg)

## 5. Event integration

### 5.1. API cashback coin to user

- This is your own API to received the request from YKit Server. Please build your API in GET method. When users by the special package, if this package has the "cashback" attribute. YKit Server will cashback the coin to user and send the request to your service to notify this event.

| Name       |                                       Description                                                  |
| ---------- | :------------------------------------------------------------------------------------------------: |
| appId      |   The id of your application is issued by YGame, use this parameter to classify android and ios    |
| char_id    |                                          id of character                                           |
| server_id  |                                         id of server game                                          |
| ycoin      |                                           cashback value                                           |
| reason     |                                    reason cashback. use to log                                     |
| sign       | Used to verify the request. sign = (md5(appId + char_id + reason + server_id + ycoin + secretKey)) |

- Your API must be response the result in the JSON format as description in the table below

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

### 5.2. API bonus gold in game

- This is your own API to received the request from YKit Server. Please build your API in GET method. When users by the special package, if this package has the "bonus" attribute. YKit Server will send the request to your service in order to add the bonus gold in game to user.

| Name           | Type           |                                       Description                                                 |
| -------------- | :------------: | :-----------------------------------------------------------------------------------------------: |
| appId          |     String     |   The id of your application is issued by YGame, use this parameter to classify android and ios   |
| char_id        |     String     |                                          id of character                                          |
| server_id      |    Integer     |                                         id of server game                                         |
| gold           |    Integer     |                                         extra bonus value                                         |
| reason         |   String       |                                     reason bonus. use to log                                      |
| sign           |     String     | Used to verify the request. sign = (md5(appId + char_id + gold + reason + server_id + secretKey)) |

- Your API must be response the result in the JSON format as description in the table below

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

## 6. Tracking NRU (New Register User)

When users created their characters successfully, please send the request to YKit Server in order to log NRU (New Register User)

URL: https://api.ygame.vn/v1/user/create_character

Params:

| Name             |                                                     Description                                                                |
| ---------------- | :----------------------------------------------------------------------------------------------------------------------------: | ------------------- |
| appId            |               The id of your application is issued by YGame, use this parameter to classify android and ios                    |
| accessToken      |                                                      Get from YKit system                                                      |
| char_id          |                                                             String                                                             | id of character     |
| char_name        |                                                             String                                                             | name of character   |
| server_id        |                                                            Integer                                                             | id of server game   |
| server_name      |                                                             String                                                             | name of server game |
| ip               |                                                         The ip of user                                                         |
| sign             | Used to verify the request. sign = (md5(accessToken + appId + char_id + char_name + server_id + server_name + ip + secretKey)) |

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

## 7. Using giftcode

- This is your own API to use gift code into game

- Method: GET

Params:

| Name           |                                                                                    Description                                                                                              |
| -------------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | ----------------- |
| app_id         |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| user_id        |                                                                                         id of user                                                                                          |
| char_id        |                                                                                           String                                                                                            | id of character   |
| server_id      |                                                                                           Integer                                                                                           | id of server game |
| gift_code      |                                                                                      giftcode of user                                                                                       |
| sign           | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| Success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

| Error Code       | JSON Format            |
| ---------------- | :--------------------: |
| -1               |      system error      |
| -2               |  invalid character id  |
| -3               |    invalid sever id    |
| -4               |      invalid code      |
| -5               | giftcode has been used |
| -6               |      unknow error      |

## 8. Tracking DAU integration

When user select server and character, then playing game successfully, please send the request to YKit Server in order to log DAU (daily active User)

URL: https://tracking.ygame.vn

Params:

| Name             |                                                                                    Description                                                                                              |
| ---------------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| app_id           |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| user_id          |                                                                                       The id of user                                                                                        |
| char_id          |                                                                                     The id of character                                                                                     |
| char_name        |                                                                                    The name of character                                                                                    |
| server_id        |                                                                               Integer. The id of server game                                                                                |
| server_name      |                                                                                   The name of server game                                                                                   |
| ip               |                                                                                       The ip of user                                                                                        |
| sign             | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| Success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

## 9. Get server and character of user is online in game

- This is your own API to get server and character which user is playing (online) in game, if user is offline in game, please response to fail

- Method: GET

Params:

| Name        |                                                                                    Description                                                                                              |
| ----------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| app_id      |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| user_id     |                                                                                       The id of user                                                                                        |
| sign        | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

| Response              |                                          JSON Format                                                    |
| --------------------- | :-----------------------------------------------------------------------------------------------------: |
| Success response      | {"status":1,"msg":"","data":{"server_id":"...","server_name":"...", "char_id":"...","char_name":"..."}} |
| Failure response      |                                {"status": "0", "msg":"reason","data":{}}                                |

## 10. Add items for user

- This is your own API to add items for user in game

- Method: GET

Params:

| Name              |                                                                                    Description                                                                                              |
| ----------------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| app_id            |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| user_id           |                                                                                       The id of user                                                                                        |
| char_id           |                                                                                     The id of character                                                                                     |
| server_id         |                                                                                    The id of server game                                                                                    |
| mail_title        |                                                                                      The title of mail                                                                                      |
| mail_content      |                                                                                     The content of mail                                                                                     |
| items             |                  List of id and number of item used to add for user in game. Example: [{"id":"ID001","type":"type1","number":1},{"id":"ID002",,"type":"type2""number":2}]                   |
| sign              | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

| Response              |          JSON Format                     |
| --------------------- | :--------------------------------------: |
| Success response      |        {"status": "1", "msg":""}         |
| Failure response      | {"status": "error_code", "msg":"reason"} |

## 10. Get top level and power in game

- This is your own API to get list top level and power of all server in game

- Method: GET

Params:

| Name        |                                                                                    Description                                                                                              |
| ----------- | :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| app_id      |                                             The id of your application is issued by YGame, use this parameter to classify android and ios                                                   |
| number      |                                                                                        Number of top                                                                                        |
| sign        | Used to verify the request. [Click here to know how to verify the signature](https://github.com/ygame11092017/ykit-wiki/blob/master/server/HowToCreateSignature.md#14-api-payment-callback) |

Response:

- Response: return the result in json format. For example: the response is corresponding to the screenshot above

```
  {
  "status": 1,
  "msg": "",
  "data": {
    "top_level": [
      {
        "char_id": "char_id1",
        "char_name": "char_name1",
        "sever_id": "server_id1",
        "server_name": "server_name1",
        "level": 100,
        "power": 1
      },
      {
        "char_id": "char_id2",
        "char_name": "char_name2",
        "sever_id": "server_id2",
        "server_name": "server_name2",
        "level": 99,
        "power": 1
      }
      ,
      {
        "char_id": "char_id3",
        "char_name": "char_name3",
        "sever_id": "server_id3",
        "server_name": "server_name3",
        "level": 98,
        "power": 1
      }
    ],
    "top_power": [
      {
        "char_id": "char_id1",
        "char_name": "char_name1",
        "sever_id": "server_id1",
        "server_name": "server_name1",
        "power": 1000,
        "level": 1
      },
      {
        "char_id": "char_id2",
        "char_name": "char_name2",
        "sever_id": "server_id2",
        "server_name": "server_name2",
        "power": 999,
        "level": 1
      }
      ,
      {
        "char_id": "char_id3",
        "char_name": "char_name3",
        "sever_id": "server_id3",
        "server_name": "server_name3",
        "power": 998,
        "level": 1
      }
    ]
  }
}
```
