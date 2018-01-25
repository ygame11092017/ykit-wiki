# How to create the signature from request parameters

## 1. Web Payment
### 1.1. API get list server game
Method: HTTP GET
Params:
app_id: The id of your application is issued by YGame, use this parameter to classify android and ios
user_id: id of YKit account  
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_server?app_id=ea2d5a18ebbd43871103b502f804db79&user_id=333&sign=ae5403d7469d07a11089593b5c4cc082
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&user_id=333

- Step 1: sort the name of parameters by A → Z

		app_id > user_id

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
### 1.2. API get list characters
Method: HTTP GET
Params:
app_id: The id of your application is issued by YGame, use this parameter to classify android and ios
user_id: id of YKit account  
server_id: id of server game. Get from the previous step  
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_character?app_id=ea2d5a18ebbd43871103b502f804db79&user_id=888&server_id=4&sign=db53b60570662098176fc6e955af4af0
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&user_id=888&server_id=4

- Step 1: sort the name of parameters by A → Z

		app_id > server_id > user_id

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

### 1.3. API get list payment
Method: HTTP GET
Params:
app_id: The id of your application, use this parameter to classify android and ios
user_id: id of YKit account
char_id: id of character in game. Get from the previous step
server_id: id of server game
sign: Used to verify the request.

- For example, we have the request URL below:
```
https://yourdomain.com/get_list_payment?app_id=ea2d5a18ebbd43871103b502f804db79&user_id=888&server_id=4&char_id=777&sign=c16372fb2336553338416671a008e13a
```
- Have a look at the parameters. We will compute the sign by follow some steps below

		app_id=ea2d5a18ebbd43871103b502f804db79&user_id=888&server_id=4&char_id=777

- Step 1: sort the name of parameters by A → Z

		app_id > char_id > server_id > user_id

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
### 1.4. API Payment callback
Method: HTTP GET
Params:
amount:	Value of the purchase
app_id:	The id of your application, use this parameter to classify android and ios     
response_time: Purchase time
transaction_id:	id of the transaction
transaction_type: Type of purchase: COIN
user_id: id of user, who make the request
char_id: id of character - get from API get list server game
server_id: id of server game - get from API get list server game
payment_id: id of payment package - get from API get list payment
order_id: order id
sign: Used to verify the request

- For example, we have the request URL below:
```
https://yourdomain.com/web_callback_payment?amount=1000&app_id=01570b2b4730a1e60d257ebd80db7027&response_time=1516441388&transaction_id=1516441388394co&transaction_type=COIN&user_id=113&char_id=2260001&server_id=1&payment_id=Bonus1500&order_id=87681734197&sign=1072316ca7e6e1c0cc2bea9ce8570c0a

```
- Have a look at the parameters. We will compute the sign by follow some steps below

		amount=1000&app_id=01570b2b4730a1e60d257ebd80db7027&response_time=1516441388&transaction_id=1516441388394co&transaction_type=COIN&user_id=113&char_id=2260001&server_id=1&payment_id=Bonus1500&order_id=87681734197

- Step 1: sort the name of parameters by A → Z

		amount > app_id > char_id > order_id > payment_id > response_time > server_id > transaction_id > transaction_type > user_id

- Step 2: get the values from ordered parameters. We have the final String

		values = 100001570b2b4730a1e60d257ebd80db7027226000187681734197Bonus1500151644138811516441388394coCOIN113

- Step 3: create the signature

```
sign = md5( values + appSecret )
* appSecret: the secret key of your application

For example:
var appSecret = "34bf3d41b69094a395bfbf7491ca4814"
sign = md5 ( values + appSecret ) = 1072316ca7e6e1c0cc2bea9ce8570c0a
```


