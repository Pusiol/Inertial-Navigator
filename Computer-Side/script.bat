set path="C:\Users\1\Desktop\Android\android-ndk-r16b-windows-x86_64\android-ndk-r16b\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin"


arm-linux-androideabi-as -o %1.o %1.s

arm-linux-androideabi-ld -o %1 %1.o

set path=C:\Users\1\Desktop\Android\platform-tools

adb push hello /data/local/tmp/%1

adb shell chmod 777 /data/local/tmp/%1

adb shell /data/local/tmp/%1

adb shell /data/local/tmp/%1>>archive

::adb ls /data/local/tmp/