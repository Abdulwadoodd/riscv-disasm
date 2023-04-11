TOOLCHAIN_PREFIX=riscv64-unknown-elf-

%.elf: %.S
	$(TOOLCHAIN_PREFIX)gcc -nostartfiles -nostdlib -march=rv32i -mabi=ilp32 -o$@ $<
%.bin: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< $@
%.hex: %.bin
	python3 makehex.py $< > $@

clean:
	rm -f *.elf *.bin *.hex
