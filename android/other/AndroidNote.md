# Android FAQ

## 1. How to build release with keystore in Android Studio

[![How to build release with keystore in Android Studio](http://img.youtube.com/vi/G0GUc9mABLY/0.jpg)](http://www.youtube.com/watch?v=G0GUc9mABLY "How to build release with keystore in Android Studio")

## 2. Why we can't login by facebook and google plus
Please make sure the android build is release with XCT's keystore. For more detail how to build release with keystore, move to question 1

## 3. How to update the existing Xlauncher framework
- Step 1: drag and drop the new xlauncher framework to xlauncher-release folder in your project
![alt tag](https://github.com/xctcorporation/XlauncherAndroid/blob/master/update_sdk.png)
- Step 2: click on "ok"
- Step 3: click on "override"
- Step 4: very important, "clean" and "rebuild" the apk

