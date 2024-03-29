B=boot
K=kernel
U=user

CC=gcc

QEMU=qemu-system-x86_64

QEMUARGS = -drive format=raw,file=os.img \
		   -m 256M \
		   -device isa-debug-exit,iobase=0xf4,iosize=0x04 \
		   -serial stdio

QEMUTESTARGS = $(QEMUARGS) -display none

.PHONY: qemu sz lldb clean

qemu: img
	-@$(QEMU) $(QEMUARGS)

test: img
	$(QEMU) $(QEMUTESTARGS)

# dd if=/dev/zero of=os.img bs=512 count=8192
# dd if=boot/boot of=os.img bs=512 conv=notrunc
# dd if=kernel/kernel of=os.img bs=512 seek=3 conv=notrunc
# @cp $B/boot ./os.img && cat $K/kernel >> os.img
img:
	@make clean
	@make -C $B && make -C $K
	dd if=/dev/zero of=os.img bs=512 count=10000
	dd if=boot/boot of=os.img bs=512 conv=notrunc
	dd if=kernel/kernel of=os.img bs=512 seek=3 conv=notrunc

format:
	find . -name "*.c" 2>/dev/null | xargs clang-format -i
	find . -name "*.h" 2>/dev/null | xargs clang-format -i

BYTESZ=$(shell wc -c < os.img)
sz: img
	@echo "Byte=$(BYTESZ)"

lldb:
	$(QEMU) $(QEMUARGS) -s -S & \
    lldb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

clean:
	@find . -name "*.o"  | xargs rm -f
	@find . -name "*.elf"  | xargs rm -f
	@rm -rf $K/kernel $B/boot ./*.img

