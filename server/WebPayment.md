# Web Payment
This is the YGame Payment System on Web. User can purchase the game content by using the YGame Web Payment
## 1. Flow
![alt text](https://github.com/xctcorporation/ServerIntegration/blob/master/webpayment_flow.jpg)

- 1: User login to YGame System
- 2: API get list server game. This is the HTTP GET provided by Server Game to return the list of server game 
- 3: API get list character. This is the HTTP GET provided by Server Game to return the list of characters base on the selected server game 
- 4: API get list payment. This is the HTTP GET provided by Server Game to return all purchase packages which offer in the game
- 5: Pay with YGame System via Card, Banking ...
- 6: API payment success. Called when user make the payment successfully

## 1. API get list server game
This is your own API to return the list of your server game.
- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of xct account
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

## 2. API get list charaters
This is your own API to return the list of characters in game
- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of xct account
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

## 3. API get list payment
This is your own API to return the list payment packages of your game
![alt text](https://github.com/xctcorporation/ServerIntegration/blob/master/payment_packages.png)

- Method: HTTP GET
- Params: 
  + app_id: The id of your application, use this parameter to classify android and ios
  + user_id: id of xct account
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

