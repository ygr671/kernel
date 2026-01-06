CC        = clang
LD        = ld.lld

TARGET  = -target i386-pc-none-elf
CCOPTS  = $(TARGET) -march=i386 -m32 -std=c99 -ffreestanding -O2 -Wall -Wextra
LDOPTS  = -m elf_i386 -T linker.ld

BUILD   = build/

C_SOURCES = $(wildcard src/*.c)
C_OBJECTS = $(patsubst src/%.c, $(BUILD)%.o, $(C_SOURCES))

ASM_OBJECTS = $(BUILD)boot.o

.PHONY: b r c

b: $(BUILD) $(ASM_OBJECTS) $(C_OBJECTS)
	@echo "LINKING..."
	$(LD) $(LDOPTS) -o $(BUILD)kernel.bin $(ASM_OBJECTS) $(C_OBJECTS)

$(BUILD)boot.o: boot.asm
	@echo "BUILDING ASM..."
	nasm -f elf32 -o $@ $<

$(BUILD)%.o: %.c
	@echo "BUILDING $<..."
	$(CC) $(CCOPTS) -c src$< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

r: b
	@echo "RUNNING..."
	qemu-system-i386 -kernel $(BUILD)kernel.bin

c:
	@echo "CLEANING..."
	rm -rf $(BUILD)
