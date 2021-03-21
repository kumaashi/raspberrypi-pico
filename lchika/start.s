.cpu cortex-m0plus
.thumb
    ldr r0, =0x20001000
    mov sp, r0
    bl main
    b .
