[Read here for basic setup about how to setup the enviroment with Native](https://github.com/xctcorporation/XlauncherIOS/blob/master/README.md)

[Read here for basic setup about how to setup the enviroment with Unity](https://github.com/xctcorporation/XlauncherIOS/blob/master/README-Unity.md)

- To use SDK with Facebook API, you have to set
          
         [launcher setupWithWindow:window usingFacebookSDK:YES];

- You also need to set permission to to get details user information of facebook's users :

          - (void)setPermissionFacebook:(NSString *)permission;
          // Example : [launcher setPermissionFacebook:@"public_profile"];
[For more permission you can read here](https://developers.facebook.com/docs/facebook-login/permissions)

- Check if user is facebook user, open dialog if user is not login through facebook. Return a dictionary included user's infomation:

          - (NSDictionary *)checkFacebookAccessToken;
          
- Check if user is facebook user, return nil if not login facebook, return a dictionary included user's infomation :

          - (NSDictionary *)getFacebookInfo;
