target remote :12345
display /x *0x200BFF8
display /x *0x2004000
display /x $sip
display /x $mip
display /x $mcause
display /x $medeleg
display /i $pc

b _start
b riscv_mtvec_mti
b riscv_mtvec_exception