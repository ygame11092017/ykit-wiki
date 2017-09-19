# XlauncherIOS For Unity
## Get Started

Xlauncher SDK for iOS is the most simple way to intergrate user and payment to XCT system.Xlauncher SDK provide solution for payment such as: SMS, card, internet banking và Apple Payment.

## Steps to integrate SDK

    1. Convert Unity to IOS game/application.

    2. Setup Xlauncher SDK

    3. Config SDK - Payment function

    4. Xlauncher SDK flow


### 1. Convert Unity to IOS game/application

   Import WrapperIOS class and Xlauncher Framework into plugin/IOS in Unity Project
   
   Follow the video guide below
    
   [![How To Convert Unity to IOS game/application](http://img.youtube.com/vi/dZV1wjXS7QU/0.jpg)](http://www.youtube.com/watch?v=dZV1wjXS7QU "How To Convert Unity to IOS game/application")

### 2. Setup Xlauncher SDK

#### 2.1. Embedded Xlauncher.framework into project

   - Embedded Binaries with SDK

   ![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/addEmbled.png)

#### 2.2. Add url schemes

- Add the following url schemes for Facebook(“fb” + facebook app id) and Google sign in (Reverse client id) from XlauncherConfig.plist file
    
![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/addFbSchemes.png)

- Add facebook app id, facebook display name and application queries scheme as below. Please replace app id and display name with the value in the XlauncherConfig.plist file
    
![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/addFbId.png)

- Add file XlauncherConfig.plist to your root project

#### 2.3. Coding
- Import SDK: import XLauncher/XLauncher.h into UnityAppController.m

- Add these lines of code in Application StartUnity function in UnityAppController class, after window setup and before return line. You can get Google Signin client ID in the XlauncherConfig.plist. Handle callback : There are two callback functions you can handle including: login success and logout success. You may use these data to call login or logout to your server
```
- (void)startUnity:(UIApplication*)application{
    
            // Project configure
        
            XLauncher *launcher = [XLauncher getInstance];
	[launcher setupWithWindow:window usingFacebookSDK:YES]; // YES is using facebook 
	//
	// if using facebook API, you need to implement 
	// [launcher setPermissionFacebook:@"public_profile"]; // string is the permission you want to 
	//
	// Handle login callback
	[launcher handleLoginWithCompletion:^(NSDictionary *data) { 
	
		NSString *userID = data[kParamUserID];
		NSString *userName = data[kParamUserName];
		NSString *accessToken = data[kParamAccessToken]; 
	
	}]; 

	// Handle logout callback
	[launcher handleLogoutWithCompletion:^{ 
		//do something
	}];

	[launcher handlePaymentWithCompletion:^(NSDictionary *data){
        //NSLog(@"Payment success! %@", data);
    	}];	
	    
    
            [launcher setDomainDebug:NO]; // if you want to build in the TEST mode, pass it to TRUE

            
 }
```

- If you want to send back a value to unity game method, you can use function :

GameObjectName1 : GameObject which will receive in Unity

MethodName1 : method to get data.

Param : value to transfer 	


	UnitySendMessage("GameObjectName1", "MethodName1", [param UTF8String]);
		

[Read here for more detail about how to setup the TEST enviroment] (https://github.com/xctcorporation/ServerIntegration/blob/master/SetupTheEnviroment.md)

- In the previous code, we provide two callback functions. There are handleLoginWithCompletion and handleLogoutWithCompletion. You may use these functions to call login or logout with your server

- Add function handle Facebook schemes 

```
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *) sourceApplication annotation:(id)annotation { 

	NSDictionary *dict = @{kParamApplication: ATNonNilObject(application), kParamUrl: ATNonNilObject(url), kParamSourceApplication: ATNonNilObject(sourceApplication), kParamAnnotation: ATNonNilObject(annotation)}; 

	ATDispatchEvent(Event_AppOpenUrl, dict); 

	return YES; 
}
```

- This example code is apply for landscape mode. Base on your game orientation, if your game support both portrait and landscape then you must replace UIInterfaceOrientationMaskLandscape with UIInterfaceOrientationMaskAll, if you game is only support portrait mode, then you don’t need to add this function
```
- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window { 

	if ([[XLauncher getInstance] isScreenRotateToPortrait]) {
		return UIInterfaceOrientationMaskPortrait; 
	} else{ 	
		return UIInterfaceOrientationMaskLandscape;
	}
}
```

#### 2.4. Public functions
- Here is the list of public functions you can call to customize the Xlauncher in your game: 

* setLauncherStickySide: You can specific the side that launcher can stick to via the or bitwise. 
Ex: ATButtonStickySideTop | ATButtonStickySideBottom 

* silentLogin: When open the app, maybe user is already logged in. Call this function to check if user is logged in or not, if not, you must call showLoginScreen function to show the login screen. 

```
if([[Xlauncher getInstance] silentLogin])
	// Move direct to game
else {
	// Show login screen
	[[Xlauncher getInstance] showLoginScreen];
}
```
        
* showButtonLauncherWithAnimation 
* hideButtonLauncherWithAnimation
* showLoginScreen: Show the login screen, if user not logged in yet
* showPaymentScreen: You may want to show payment screen from your game
* handleShowSDKCompletion: You can get the event show SDK here
* handleCloseSDKCompletion: You can get the event show SDK here

### 3. Implement payment extra data

Payment extra data (PED) is the data you send to game server when user make payment success. 
For example: if your game have multiple servers or multiple characters, you may want to send this data to game server, so its will know which character get the gold. The format is defined on your demand. 
    
Note*: 
* It must be unique string
* Maximum is 50 characters
* There's no special character in string

    
To set PED, you can call function

	void setGameOrder(char *gameOrder) {
	}

### 4. Flow

#### 4.1. Login flow: 
![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/loginFlow.png)

#### 4.2. Payment flow:
![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/PaymentFlow.png)

### 5. Video Guide

   [![Video Guide](http://img.youtube.com/vi/PfrMZtJtEsw/0.jpg)](http://www.youtube.com/watch?v=PfrMZtJtEsw "Video Guide")
