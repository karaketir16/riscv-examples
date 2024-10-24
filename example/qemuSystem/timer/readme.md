/opt/riscv32/bin/riscv32-unknown-elf-gdb -x example/qemuSystem/timer/help.gdb build/qemuSystem/timer/timer 

qemu-system-riscv32 -S -gdb tcp::12345 -nographic -serial mon:stdio -machine virt -bios build/qemuSystem/timer/timer