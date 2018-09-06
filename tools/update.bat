@echo off

adb root
adb wait-for-device
ping -n 2 127.0.1>nul
adb devices
adb root
adb disable-verity

echo "============> reboot now and disable verity"
adb reboot
ping -n 10 127.0.1>nul
adb wait-for-device
ping -n 10 127.0.1>nul
adb root
adb wait-for-device
ping -n 5 127.0.1>nul

echo "============> device connected and update library"
adb devices
adb root
adb remount
adb install -r -t camera2yuvtest-debug_Sub_2864x2148.apk
adb push camera.qcom.so /vendor/lib/hw/
adb push com.qti.sensormodule.ofilm_imx576.bin /vendor/lib/camera/

echo "============> reboot again"
adb reboot

echo "============> finished."

::adb shell am start -n com.zui.camera.yuvtest/com.zui.camera.yuvtest.CameraActivity
pause
