.global socket
.type socket, @function

socket:
    movq    $41, %rax
    syscall
    ret
