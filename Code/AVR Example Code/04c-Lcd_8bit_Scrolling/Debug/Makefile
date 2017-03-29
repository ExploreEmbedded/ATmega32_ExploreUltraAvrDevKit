################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../../00-libfiles/gpio.c \
../../00-libfiles/lcd.c \
../delay.c \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
gpio.o \
lcd.o \
delay.o \
main.o

OBJS_AS_ARGS +=  \
gpio.o \
lcd.o \
delay.o \
main.o

C_DEPS +=  \
gpio.d \
lcd.d \
delay.d \
main.d

C_DEPS_AS_ARGS +=  \
gpio.d \
lcd.d \
delay.d \
main.d

OUTPUT_FILE_PATH +=04c-Lcd_8bit_Scrolling.elf

OUTPUT_FILE_PATH_AS_ARGS +=04c-Lcd_8bit_Scrolling.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler









./%.o: ../../00-libfiles/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000UL  -I"C:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include" -I"../../00-libfiles"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32 -B "C:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega32" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000UL  -I"C:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\include" -I"../../00-libfiles"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32 -B "C:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega32" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="04c-Lcd_8bit_Scrolling.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32 -B "C:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.0.90\gcc\dev\atmega32"  
	@echo Finished building target: $@
	"C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "04c-Lcd_8bit_Scrolling.elf" "04c-Lcd_8bit_Scrolling.hex"
	"C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "04c-Lcd_8bit_Scrolling.elf" "04c-Lcd_8bit_Scrolling.eep" || exit 0
	"C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "04c-Lcd_8bit_Scrolling.elf" > "04c-Lcd_8bit_Scrolling.lss"
	"C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "04c-Lcd_8bit_Scrolling.elf" "04c-Lcd_8bit_Scrolling.srec"
	"C:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "04c-Lcd_8bit_Scrolling.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "04c-Lcd_8bit_Scrolling.elf" "04c-Lcd_8bit_Scrolling.a" "04c-Lcd_8bit_Scrolling.hex" "04c-Lcd_8bit_Scrolling.lss" "04c-Lcd_8bit_Scrolling.eep" "04c-Lcd_8bit_Scrolling.map" "04c-Lcd_8bit_Scrolling.srec" "04c-Lcd_8bit_Scrolling.usersignatures"
	