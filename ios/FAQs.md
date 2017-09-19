# iOS FAQs

## 1. How to replace the existing Xlauncher Framework
- Drag and drop Xlauncher.framework into your project. (choose replace)
- Embedded Binaries with SDK
- Remove the old one, then link again with new 
![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/addEmbled.png)

## 2. How to export adhoc
1. Open the Archives organizer (choose Organizer from the Window menu), and select the archive. Then Click the Export button

![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/1_select_ipa.png)

2. Select export option:
- To distribute your app to users with designated devices, select “Save for Ad Hoc Deployment.” The app will be code signed with the distribution certificate.
- To distribute your app for internal testing, select “Save for Development Deployment.” The app will be code signed with your development certificate.

![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/2_select_adhoc.png)

3. Select export one app for all compatible devices

![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/3_select_export.png)

4. check “Include manifest for over-the-air installation.”

![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/4_include_manifest.png)

5. Enter the following information:
- Name: The name of the app displayed during download and installation.
- App URL: just fill something for example. We will edit it later.
- Display Image URL (image with size 57 x 57): just fill something for example. We will edit it later.
- Full Size Image URL (image with size 512 x 512): just fill something for example. We will edit it later.

![alt tag](https://github.com/xctcorporation/XlauncherIOS/blob/master/Images/5_fill_info.png)

6. Give me the ipa file and plist file
