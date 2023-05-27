
CC = /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
OBJCOPY = /opt/devkitpro/devkitARM/bin/arm-none-eabi-objcopy
GBAFIX = /opt/devkitpro/tools/bin/gbafix

INC = -I../include -I/opt/devkitpro/libgba/include -L/opt/devkitpro/libgba/lib -L../cmake-build-devkitpro-arm
LNK = -lTinyGL -lgba -lmm -lm 

all: clean gears_gba

clean:
	$(RM) *.o *.elf *.gba *.sav

gears_gba: gears_gba.c
	$(CC) -mthumb -mthumb-interwork $(INC) -c gears_gba.c
	$(CC) $(INC) -specs=gba.specs -mthumb -mthumb-interwork gears_gba.o $(LNK) -o gears_gba.elf
	$(OBJCOPY) -O binary gears_gba.elf gears_gba.gba
	$(GBAFIX) gears_gba.gba
