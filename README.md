# How to run
* open with Unity 2022.3.18f1 (extensions: ios)
* switch platform to ios
* Build and Run
* In Xcode 'Signing and Capabilities',
  * Set Provisioning profile 
  * Remove 'Push Notification' and 'Sign in with Apple' in Configuration of 'Unity-iPhone' Target, 
![image](https://github.com/nakwonchoi-5minlab/gamepot-linkage-static-sample/assets/106501566/69423263-25d2-42bf-9317-1bc4299e4d31)

# Expect
* `$(inherited)` exist to process frameworks in 'Framework Search Paths' in 'UnityFramework' target.
![image](https://github.com/nakwonchoi-5minlab/gamepot-linkage-static-sample/assets/106501566/3faee238-d7be-4d82-8bc9-7dab1ac31adb)

# Actual
* Overwrite by third-party plugin

