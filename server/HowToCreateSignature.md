# How to create the signature from request parameters

## 1. SDK Payment callback
- For example, we have the request URL below:
```
https://yourdomain.com/sdk_callback_payment?amount=0.99&app_id=ea2d5a18ebbd43871103b502f804db79&response_time=2017-01-10 17:11:33&transaction_id=43093285&transaction_type=CARD&currency=VND&game_order=1147277470600214&user_id=217&order_id=ffc9447c6c45b1d1a6ecbdfbd3a1aa21&card_code=xxxxxxxx&card_serial=yyyyyyy&card_vendor=viettel&sign=16f97f19fe1ded03bb3e175b19a0709e
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		amount=0.99&app_id=ea2d5a18ebbd43871103b502f804db79&response_time=2017-01-10 17:11:33&transaction_id=43093285&transaction_type=CARD&currency=VND&game_order=1147277470600214&user_id=217&order_id=ffc9447c6c45b1d1a6ecbdfbd3a1aa21&card_code=xxxxxxxx&card_serial=yyyyyyy&card_vendor=viettel

- Step 1: sort the name of parameters by A → Z

		amount > app_id > card_code > card_serial > card_vendor > currency > game_order > order_id > response_time > transaction_id > transaction_type > user_id

- Step 2: get the values from ordered parameters. We have the final String

		values = 0.99ea2d5a18ebbd43871103b502f804db79xxxxxxxxyyyyyyyviettelVND1147277470600214ffc9447c6c45b1d1a6ecbdfbd3a1aa212017-01-10 17:11:3343093285CARD217

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application is issued by YGame

For example:
var appSecret = "ff9af584ad6c9328930f3925f2c973f0"
sign = md5 ( values + appSecret ) = 16f97f19fe1ded03bb3e175b19a0709e
```
## 2. Web Payment
### 2.1. API get list server game
Method: HTTP GET
Params:
app_id: The id of your application is issued by YGame, use this parameter to classify android and ios
xct_id: id of xct account  
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_server?app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=333&sign=ae5403d7469d07a11089593b5c4cc082
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=333

- Step 1: sort the name of parameters by A → Z

		app_id > xct_id

- Step 2: get the values from ordered parameters. We have the final String

		values = ea2d5a18ebbd43871103b502f804db79333

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application

For example:
var appSecret = "ff9af584ad6c9328930f3925f2c973f0"
sign = md5 ( values + appSecret ) = ae5403d7469d07a11089593b5c4cc082
```
### 2.2. API get list characters
Method: HTTP GET
Params:
app_id: The id of your application is issued by YGame, use this parameter to classify android and ios
xct_id: id of xct account  
server_id: id of server game. Get from the previous step  
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_character?app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=888&server_id=4&sign=db53b60570662098176fc6e955af4af0
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=888&server_id=4

- Step 1: sort the name of parameters by A → Z

		app_id > server_id > xct_id

- Step 2: get the values from ordered parameters. We have the final String

		values = ea2d5a18ebbd43871103b502f804db794888

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application

For example:
var appSecret = "ff9af584ad6c9328930f3925f2c973f0"
sign = md5 ( values + appSecret ) = db53b60570662098176fc6e955af4af0
```

### 2.3. API get list payment
Method: HTTP GET
Params:
app_id: The id of your application, use this parameter to classify android and ios
xct_id: id of xct account
char_id: id of character in game. Get from the previous step
server_id: id of server game
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_payment?app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=888&server_id=4&char_id=777&sign=c16372fb2336553338416671a008e13a
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&xct_id=888&server_id=4&char_id=777

- Step 1: sort the name of parameters by A → Z

		app_id > char_id > server_id > xct_id

- Step 2: get the values from ordered parameters. We have the final String

		values = ea2d5a18ebbd43871103b502f804db797774888

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application

For example:
var appSecret = "ff9af584ad6c9328930f3925f2c973f0"
sign = md5 ( values + appSecret ) = c16372fb2336553338416671a008e13a
```
### 2.4. API WEB Payment callback
Method: HTTP GET
Params:
amount:	Value of the purchase
app_id:	The id of your application, use this parameter to classify android and ios     
response_time: Purchase time
transaction_id:	id of the transaction
transaction_type: Type of purchase: CARD, BANK
currency: VN or USD
user_id: id of user, who make the request
char_id: id of character - get from API get list server game
server_id: id of server game - get from API get list server game
payment_id: id of payment package - get from API get list payment
order_id: order id
card_code: * if transaction_type = CARD, card_code = code
card_serial: * if transaction_type = CARD, card_serial = serial
card_vendor: * if transaction_type = CARD, card_vendor = name
sign: Used to verify the request

- For example, we have the request URL below:
```
https://yourdomain.com/web_callback_payment?amount=0.99&app_id=ea2d5a18ebbd43871103b502f804db79&response_time=2017-01-10 17:11:33&transaction_id=43093285&transaction_type=CARD&currency=VND&user_id=888&char_id=777&server_id=3&payment_id=22&order_id=ffc9447c6c45b1d1a6ecbdfbd3a1aa21&card_code=xxxxxxxx&card_serial=yyyyyyy&card_vendor=viettel&sign=e7e0fd0927dc659ccbffd53e116a92fd

```
- Have a look at the parameters. We will compute the sign by follow some steps below

		amount=0.99&app_id=ea2d5a18ebbd43871103b502f804db79&response_time=2017-01-10 17:11:33&transaction_id=43093285&transaction_type=CARD&currency=VND&user_id=888&char_id=777&server_id=3&payment_id=22&order_id=ffc9447c6c45b1d1a6ecbdfbd3a1aa21&card_code=xxxxxxxx&card_serial=yyyyyyy&card_vendor=viettel

- Step 1: sort the name of parameters by A → Z

		amount > app_id > card_code > card_serial > card_vendor > char_id > currency > order_id > payment_id > response_time > server_id > transaction_id > transaction_type > user_id

- Step 2: get the values from ordered parameters. We have the final String

		values = 0.99ea2d5a18ebbd43871103b502f804db79xxxxxxxxyyyyyyyviettel777VNDffc9447c6c45b1d1a6ecbdfbd3a1aa21222017-01-10 17:11:33343093285CARD217

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application

For example:
var appSecret = "ff9af584ad6c9328930f3925f2c973f0"
sign = md5 ( values + appSecret ) = e7e0fd0927dc659ccbffd53e116a92fd
```


