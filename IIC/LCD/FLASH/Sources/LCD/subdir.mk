################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LCD/lcd.c" \

C_SRCS += \
../Sources/LCD/lcd.c \

OBJS += \
./Sources/LCD/lcd_c.obj \

OBJS_QUOTED += \
"./Sources/LCD/lcd_c.obj" \

C_DEPS += \
./Sources/LCD/lcd_c.d \

C_DEPS_QUOTED += \
"./Sources/LCD/lcd_c.d" \

OBJS_OS_FORMAT += \
./Sources/LCD/lcd_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/LCD/lcd_c.obj: ../Sources/LCD/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/LCD/lcd.args" -ObjN="Sources/LCD/lcd_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/LCD/%.d: ../Sources/LCD/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


