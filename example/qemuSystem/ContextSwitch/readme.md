/opt/riscv32/bin/riscv32-unknown-elf-gdb -x example/qemuSystem/ContextSwitch/help.gdb build/qemuSystem/ContextSwitch/context

riscv64-unknown-elf-gdb -x example/qemuSystem/ContextSwitch/help.gdb build/qemuSystem/ContextSwitch/context

qemu-system-riscv32 -S -gdb tcp::12345 -nographic -serial mon:stdio -machine virt -bios build/qemuSystem/ContextSwitch/context


riscv64-unknown-elf-gdb -x example/qemuSystem/ContextSwitch/help.gdb build/qemuSystem/ContextSwitch/context


docker run --network=host -it --rm -v $PWD:/workspace riscv-toolchain-multilib:v0.2