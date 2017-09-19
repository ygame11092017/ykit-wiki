# How To Use Xlauncher Payment System Flexible 

## 1. What's the problem
XCTCorp is one of the famous publisher in Vietnam. We already have published many games such as action game, role playing game, card battle ... We used to be facing in different payment scenarios when connect and publish these games. A payment scenarios means the action when user purchase the digital goods in game. 

For example, In somes game, users can use their money to buy coins - a digital money in game - or to buy some special items. 
How to adapt the payment process in this payment scenarios? How to know when user want to buy coins or buy special items?

This document will be help you to resolve this problem

## 2. My Solution
Let me reuse the example above. A game provide two payment packages for user, let's name it a "package_coin" and "package_item"

- package_coin: purchase 0.99$ and get 100 coin
- package_item: purchase 0.99$ and get a valuable item, for example, a cup of tea

Let me remind you the payment process
- Step 1: user choice the payment package in your game
- Step 2: your game create "the payment extra data (PED)" and call the function showPaymentScreen in SDK
- Step 3: user confirm the payment
- Step 4: Xlaucher client send the payment receipt with your PED to Xlauncher server
- Step 5: Xlaucher server process payment and "callback the result" to your server game

That's all

Let's focus two important steps, "create the payment extra data" and "callback the result".

First, We will discuss more detail in step 2.

PED is your customized data, you can build PED whatever you want.I will demo how to use the PED to classify the package_coin and package_item by using the example above.

We need some additional information to demo. An user who make the purchase in game is named "Peter".

My PED will be contructed by formatting below
```
PED = base64( username + | + package_type + | + time ) - just example :)
```
When Peter buy the package "package_coin" or "package_item", The PED will be constructed as below

```
PED = base64 (peter|coin|21022017114155) = xxxxxxxxxxx  //in case buy package_coin
PED = base64 (peter|item|21022017114155) = yyyyyyyyyyy  //in case buy package_item
```
That's enough for step 2. Let's move to the step 5 - "callback the result"

When the Xlauncher server process the payment successfully. Xlauncher server will call to your server game to notify the payment success. The important parameters which sent to your server game is

- amount: Value of the purchase. In this example is 0.99
- game_order: the PED

[Read here for full parameters](https://github.com/xctcorporation/ServerIntegration#2-payment)

When your server game received the request parameter from Xlauncher server. Just do some simple steps below to classify what package user want to buy

- Step 1: decode the PED, separate the information
```
  origin = decode_base64 (xxxxxxxxxx) = peter|coin|21022017114155 //in case buy package_coin
  origin = decode_base64 (yyyyyyyyyy) = peter|item|21022017114155 //in case buy package_item
  
  => user: peter
  => type of package: coin or item
  => time purchase: 21/02/2017 11:41:55
  
```

- Step 2: check the package type and amount
```
if(type.equals(coin)){
    //add coin for user
    
}else if(type.equals(item)){
    /*
        check the value of purchase with the price of item (0.99$). If the amount parameter greater than 0.99$, add the item and some coins. If amount less than 0.99$, add some coins
        
        */
    if(amount < 0.99){
        //add coin for user
        
    }else if(amount == 0.99){
        //add the cup of tea
        
    }else{
        //add coin and the cup of tea
        
    }
}
```

That's all, thanks :)
