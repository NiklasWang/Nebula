@echo off
::setlocal enabledelayedexpansion
:: %1 device
:: %2 number of pictures
:: %3 destDir


adb -s %1 root
adb -s %1 remount

:: start app
adb -s %1 shell am start -n com.zui.camera.yuvtest/com.zui.camera.yuvtest.CameraActivity

:: 
set /a time=0
:waitFile
	set /a n=0
	for /f %%i in ('adb -s %1 shell ls /storage/emulated/0/DCIM/yuv/') do (set /a n+=1)
		if %n%==%2 goto pullFile
	goto waitFile
	
:exit
	echo "fail"

:pullFile
	if not exist %3 md %3

	adb -s %1 pull /sdcard/DCIM/yuv %3
	move %3\yuv\*.* %3\
	rmdir /s /q %3\yuv\
	adb -s %1 shell rm -rf /sdcard/DCIM/yuv

	adb -s %1 pull /data/misc/camera/ %3\
	move %3\camera\calib* %3\
	rmdir /s /q %3\camera\

	echo succeed
	
