.text            
.global print
print:
    push {r0}

    ldr r0, =message
    swi #0xFCFCFC

    pop {r0}

.data
message:
    .asciz "hello world\n\0"
