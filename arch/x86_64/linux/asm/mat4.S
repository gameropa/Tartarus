.global mult_m4
.type mult_m4, @function

mult_m4:
    vmovups         (%rsi), %ymm0
    vmovups         32(%rsi), %ymm2
    vperm2f128      $17, %ymm0, %ymm0, %ymm3
    vperm2f128      $0, %ymm0, %ymm0, %ymm1

    vmovups         (%rdx), %ymm0

    vperm2f128      $0, %ymm2, %ymm2, %ymm4
    vperm2f128      $17, %ymm2, %ymm2, %ymm2

    vpermilps       $255, %ymm0, %ymm5
    vpermilps       $170, %ymm0, %ymm6
    vpermilps       $0, %ymm0, %ymm7
    vpermilps       $85, %ymm0, %ymm0

    vmulps          %ymm3, %ymm0, %ymm0

    vfmadd231ps     %ymm1, %ymm7, %ymm0
    vfmadd231ps     %ymm4, %ymm6, %ymm0
    vfmadd231ps     %ymm2, %ymm5, %ymm0

    vmovups         %ymm0, (%rdi)
    vmovups         32(%rdx), %ymm0

    vpermilps       $255, %ymm0, %ymm5
    vpermilps       $170, %ymm0, %ymm6
    vpermilps       $0, %ymm0, %ymm7
    vpermilps       $85, %ymm0, %ymm0

    vmulps          %ymm3, %ymm0, %ymm0

    vfmadd132ps     %ymm7, %ymm0, %ymm1
    vfmadd132ps     %ymm6, %ymm1, %ymm4

    vmovaps         %ymm4, %ymm0
    vfmadd231ps     %ymm2, %ymm5, %ymm0
    vmovups         %ymm0, 32(%rdi)
    vzeroupper
    ret
