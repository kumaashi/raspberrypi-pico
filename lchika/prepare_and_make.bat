git clone https://github.com/raspberrypi/pico-sdk.git
curl "https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-win32.zip?revision=ffcaa06c-940d-4319-8d7e-d3070092d392&la=en&hash=130196DDF95B0D9817E1FDE08A725C7EBFBFB5B8" -L -o gcc-arm-none-eabi-10-2020-q4-major-win32.zip
unzip gcc-arm-none-eabi-10-2020-q4-major-win32.zip
patch -p1 < patch_elf2uf2.diff
cl pico-sdk\tools\elf2uf2\main.cpp /Ipico-sdk\src\common\boot_uf2\include\ /Feelf2uf2 /nologo /Ox /GS- /EHsc
start make.bat
