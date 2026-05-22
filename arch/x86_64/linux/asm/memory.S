.global sys_mmap
.type sys_mmap, @function

sys_mmap:
    movq    $9, %rax
    movq    %rcx, %r10
    syscall
    ret

.global sys_munmap
.type sys_munmap, @function

sys_munmap:
    movq    $11, %rax
    syscall
    ret

.global sys_mremap
.type sys_mremap, @function

sys_mremap:
    movq    $25, %rax
    movq    %rcx, %r10
    syscall
    ret
