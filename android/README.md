# YKit for Android

Video Tutorials: [file](files/How%20to%20integrate%20YKit%20to%20android.mp4) or [youtube](https://youtu.be/BQYVgPVMoV4)

Demo Project: [https://github.com/ygame11092017/ykit-demo-android](https://github.com/ygame11092017/ykit-demo-android)

## Index
+ [A. Prerequisites](#a-prerequisites)
+ [B. Integrate SDK](#b-integrate-sdk)
    - [1. Add YKit library](#1-add-ykit-library)
    - [2. Config app](#2-config-app) 
    - [3. Implement code](#3-implement-code)
+ [C. Public function](#c-public-function)

## A. Prerequisites

+ [Android Studio 2.3.3](https://developer.android.com/studio/index.html)

+ Open Android Studio, click **File > Settings...**, choose **Appearance and Behavior > System Settings > Android SDK > SDK Tools**, install all packages in it
![](images/sdk_tools.png)

+ Open Android Studio, click **File > Project Structure**, set **JDK locations** and **Android SDK location**
![](images/project_structure.png)



## B. Integrate SDK

### 1. Add YKit library

+ Click **File > New > New Module**

    ![](images/new_module.png)

+ Click **Import .JAR/.AAR Package** then click **Next**

    ![](images/import_aar.png)

+ Enter the location of **ykit-release.aar** file then click **Finish**

    ![](images/finish_new_module.png)

+ Add `libraries.gradle` to root project folder

    ![](images/libraries.png)

+ Add this line end of file `settings.gradle` (Optional)

    ```
    org.gradle.jvmargs=-Xmx2048m
    ```

    ![](images/gradle_properties.png)
+ Check the file settings.gradle. Please insert line below if it is not exist in the file
    ```
    include ':ykit-release'
    ```

+ Update top-level `build.gradle` (`YKitDemo/proj.android-studio/build.gradle`)

```
    apply from: "./libraries.gradle"
    
    buildscript {
        repositories {
            jcenter()
            maven { url 'https://maven.fabric.io/public' }
            maven { url "https://plugins.gradle.org/m2/" }
        }
        dependencies {
            classpath 'com.android.tools.build:gradle:2.3.3'
            classpath 'me.tatarka:gradle-retrolambda:3.7.0'
            classpath 'com.google.gms:google-services:3.0.0'
            classpath 'io.fabric.tools:gradle:1.22.0'
            classpath 'com.jakewharton:butterknife-gradle-plugin:8.8.1'
            classpath 'com.jakewharton.hugo:hugo-plugin:1.2.1'
        }
    }
    
    allprojects {
        repositories {
            jcenter()
            maven { url "https://maven.google.com" }
            maven { url "https://www.jitpack.io" }
        }
    }
    
    task clean(type: Delete) {
        delete rootProject.buildDir
    }
```

![](images/diff_top_build_gradle.png)

+ Update module-level`build.gradle` (`YKitDemo/proj.android-studio/app/build.gradle`)

    ```
    [...]
    apply plugin: 'me.tatarka.retrolambda'
    apply plugin: 'io.fabric'
    
    android {
        compileSdkVersion rootProject.ext.compileSdkVersion
        buildToolsVersion rootProject.ext.buildToolsVersion
        
        defaultConfig {
            [...]
            minSdkVersion rootProject.ext.minSdkVersion
            targetSdkVersion rootProject.ext.targetSdkVersion
            multiDexEnabled true
        }
        
        compileOptions {
            sourceCompatibility rootProject.ext.sourceCompatibilityVersion
            targetCompatibility rootProject.ext.targetCompatibilityVersion
        }
        
        dexOptions {
            maxProcessCount 8
        }
    }
    
    repositories {
        mavenCentral()
        maven { url "https://jitpack.io" }
        maven { url 'https://maven.fabric.io/public' }
    }
    
    dependencies {
        [...]
        compile project(':ykit-release')
        
        compile deps.supportDesign
        compile deps.appcompatv7
        compile deps.recyclerviewv7
    
        compile deps.multidex
    
        compile deps.firebaseCore
        compile deps.firebaseMessaging
        compile deps.firebaseConfig
    
        compile deps.playServicesAuth
        
        compile deps.playServicesBase
        compile deps.installReferrer
    
        compile deps.billing
    
        compile(deps.crashlytics) { transitive = true; }
        compile(deps.answers) { transitive = true; }
    
        compile deps.butterknife
        annotationProcessor deps.butterknifeCompiler
    
        compile deps.dagger
        annotationProcessor deps.daggerCompiler
    
        compile deps.androidannotations
        annotationProcessor deps.androidannotationsCompiler
    
        compile deps.parceler
        annotationProcessor deps.parcelerCompiler
    
        compile deps.retrofit
        compile deps.retrofitConverterGson
        compile deps.retrofitAdapterRxjava
    
        compile deps.okhttp
        compile deps.okhttpInterceptor
    
        compile deps.gson
    
        compile deps.transitionseverywhere
        compile deps.calligraphy
    
        compile deps.glide
        annotationProcessor deps.glideCompiler
    
        compile deps.rxjava
        compile deps.rxandroid
        compile deps.rxlifecycle
        compile deps.rxlifecycleAndroid
        compile deps.rxlifecycleComponents
        compile deps.nybus
        compile deps.localeChanger
    
        compile deps.dbflow
        compile deps.dbflowCore
        compile deps.dbflowRx2
    
        compile deps.utilcode
    
        annotationProcessor deps.dbflowCompiler
        compile deps.timber
    
        compile deps.appsflyer
    
        compile deps.facebook
        compile deps.facebook_account_kit
    
        debugCompile deps.leakcanary
        releaseCompile deps.leakcanaryNoOp
        testCompile deps.leakcanaryNoOp
    
        compile deps.stetho
        compile deps.stethoOkhttp3
        compile deps.stethoUrlconnection
    
        compile deps.traceur
    
        compile deps.logger
    
        compile(deps.loggingInterceptor) {
            exclude group: 'org.json', module: 'json'
        }
    }
        
    apply plugin: 'com.google.gms.google-services'        
    ```
    
![](images/diff_module_build_gradle.png)

![](images/diff_module_build_gradle2.png)

![](images/diff_module_build_gradle3.png)

### 2. Config app 
+ Edit `AndroidManifest.xml`
+ First, insert two intent filters after main intent filter. Notice: replace xxxxx by the value which YGame will give it to you
```
            <intent-filter android:label="@string/app_name">
                <action android:name="android.intent.action.VIEW" />
                <category android:name="android.intent.category.DEFAULT" />
                <category android:name="android.intent.category.BROWSABLE" />
                <!-- Accepts URIs that begin with "http://test.ygame.vn/test” -->
                <data android:scheme="http"
                    android:host="xxxxxx"
                    android:pathPrefix="xxxxxx" />
                <!-- note that the leading "/" is required for pathPrefix-->
            </intent-filter>
            <intent-filter android:label="@string/app_name">
                <action android:name="android.intent.action.VIEW" />
                <category android:name="android.intent.category.DEFAULT" />
                <category android:name="android.intent.category.BROWSABLE" />
                <!-- Accepts URIs that begin with "example://gizmos” -->
                <data android:scheme="xxxxxx"
                    android:host="xxxxxx" />
            </intent-filter>
```
 
+ Second, add the following to `Application` tag
 
    ```    
    <activity
        android:name="com.facebook.accountkit.ui.AccountKitActivity"
        android:theme="@style/AppLoginTheme"
        tools:replace="android:theme" />

    <provider
        android:name="com.facebook.FacebookContentProvider"
        android:authorities="com.facebook.app.FacebookContentProviderXXXXXXXXXX"
        android:exported="true" />

    <meta-data
        android:name="com.facebook.sdk.ApplicationId"
        android:value="@string/facebook_app_id" />

    <meta-data
        android:name="com.facebook.accountkit.ApplicationName"
        android:value="@string/app_name" />

    <meta-data
        android:name="com.facebook.accountkit.ClientToken"
        android:value="@string/account_kit_client_token" />
    ```
  
 Replace `XXXXXXXXXX` string in `com.facebook.app.FacebookContentProviderXXXXXXXXXX` with your `facebook id` (you can get the `facebook id` in file `config.xml`)
           
 ![](images/manifest.png)      
   
 + Add `facebook_app_id`, `account_kit_client_token` to `app/res/values/strings.xml`
 
 ![](images/strings.png) 
   
 + Add `config.xml` to `app/res/xml/` and `google-services.json` to `app/` (create the `app/res/xml/` directory if it's not exist)
 
 ![](images/google-services.png)  
 
### 3. Implement code

  + In your main activity class, init the YKit by add the following to `AppActivity.java`
  
  ```  
    public class AppActivity extends Cocos2dxActivity {
    
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            [...]
    
            YKit.get().init(this, new YKitListener() {
                @Override
                public void onLogin(int userId, String accessToken) {
                    
                }
    
                @Override
                public void onLogout() {
                    
                }
    
                @Override
                public void onInAppPurchase(BillDto billDto) {
                }
    
                @Override
                public void onPause() {
                }
    
                @Override
                public void onResume() {
                }
            });
        }
    
        @Override
        protected void onResume() {
            super.onResume();
            YKit.get().onResume(this);
        }
    
        @Override
        protected void onPause() {
            super.onPause();
            YKit.get().onPause(this);
        }
    
        @Override
        protected void onDestroy() {
            super.onDestroy();
            YKit.get().onDestroy(this);
        }
    
        @Override
        protected void onActivityResult(int requestCode, int resultCode, Intent data) {
            YKit.get().onActivityResult(requestCode, resultCode, data, this);
        }
    }
  ```   
  
  In the previous code, we provide some callback functions: 
  + `onLogin`: notify when user login to YKit system successfully. Handle this function and call login with your server
  + `onLogout`: the event will be fired when user sign out of YKit system. In this case, you must kick the user out of your server as well
  + `onInAppPurchase`: notify purchase success
  + `onPause`: call when game pause
  + `onResume`: call when game resume

## C. Setup YCoin Support

We provide a buy function, which used to buy the item from your game.

Buy function has 4 parameters:

+ serverId: current server id

+ charId: current character id

+ paymentId: The package user want to buy

+ isConfirm: If this is true, there will be a confirm diablog before user can buy. If false, user will instantly buy the item.

+ serverName: current server name

+ charName: current character name

```
public void buy(String serverId, String charId, String paymentId, boolean isConfirm, String serverName, String charName)
```

Example usage
```
YKit.get().buy("myServerId", "myCharId", "myPaymentId",false, "Server Name", "Character Name");
```

## D. Public function

  + `YKit.get().openLogin()`: open login windows 
  + `YKit.get().openInApp()`: open inapp purchase windows 
  + `YKit.get().openAccount()`: open account info windows 
  + `YKit.get().openNotification()`: open notification windows 
  + `YKit.get().logout()`: logout of YKit 
  + `YKit.get().showLauncher()`: show floating widget 
  + `YKit.get().hideLauncher()`: hide floating widget
  + `YKit.get().setServerTest(boolean isTest);`: Use server test or not
  + `YKit.get().setRemindContent(String reminderText);`: Reminder text if user don't play game for a long time
