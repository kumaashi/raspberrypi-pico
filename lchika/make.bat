set EABIBINPATH=gcc-arm-none-eabi-10-2020-q4-major\bin
set MCPUOPTION=-mcpu=cortex-m0plus
set GCCOPTION=-O1 -fno-builtin -nostartfiles -nostdlib -mthumb -ffreestanding -c
%EABIBINPATH%\arm-none-eabi-as.exe %MCPUOPTION% start.s -o start.o
%EABIBINPATH%\arm-none-eabi-gcc %MCPUOPTION% test.c %GCCOPTION%
%EABIBINPATH%\arm-none-eabi-ld -T memorymap.ld start.o test.o
elf2uf2 a.out a.uf2

REM %EABIBINPATH%\arm-none-eabi-readelf -a a.out
REM %EABIBINPATH%\arm-none-eabi-objdump -S start.o
REM %EABIBINPATH%\arm-none-eabi-objdump -S test.o
REM 
del *.out *.o
