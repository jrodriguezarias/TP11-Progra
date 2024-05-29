################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Rules.c \
../board_graphics.c \
../main.c \
../uint_input.c 

C_DEPS += \
./Rules.d \
./board_graphics.d \
./main.d \
./uint_input.d 

OBJS += \
./Rules.o \
./board_graphics.o \
./main.o \
./uint_input.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Rules.d ./Rules.o ./board_graphics.d ./board_graphics.o ./main.d ./main.o ./uint_input.d ./uint_input.o

.PHONY: clean--2e-

