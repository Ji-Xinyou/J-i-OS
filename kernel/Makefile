# Set the C compiler and debugger
CC = clang
GDB = gdb 

LD = ld.lld
ASM = nasm

INC = -Iinc/
SRC = $(shell find . -type f -name "*.c")
ASM_SRC = $(shell find . -type f -name "*.S")

# CRITICAL: assembly must be linked first
OBJ = ${ASM_SRC:.S=.o} ${SRC:.c=.o} 

CCFLAGS = -ggdb -c -ffreestanding -target x86_64-none-elf
# LDFLAGS = -Ttext 0x8200
LDFLAGS = -Tkernel.ld
LDFLAGS_BIN = ${LDFLAGS} --oformat binary
ASFLAGS = -f elf64

all: kernel kernel.elf

kernel: ${OBJ}
	${LD} -o $@ ${LDFLAGS_BIN} $^

kernel.elf: ${OBJ}
	${LD} -o $@ ${LDFLAGS} $^

%.o: %.c
	${CC} ${CCFLAGS} ${INC} -o $@ $^

%.o: %.S
	${ASM} $< ${ASFLAGS} -o $@

clean:
	rm -f kernel kernel.elf *.o **/*.o
