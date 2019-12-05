################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Retardos/retardos.c" \

C_SRCS += \
../Sources/Retardos/retardos.c \

OBJS += \
./Sources/Retardos/retardos_c.obj \

OBJS_QUOTED += \
"./Sources/Retardos/retardos_c.obj" \

C_DEPS += \
./Sources/Retardos/retardos_c.d \

C_DEPS_QUOTED += \
"./Sources/Retardos/retardos_c.d" \

OBJS_OS_FORMAT += \
./Sources/Retardos/retardos_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Retardos/retardos_c.obj: ../Sources/Retardos/retardos.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Retardos/retardos.args" -ObjN="Sources/Retardos/retardos_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Retardos/%.d: ../Sources/Retardos/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


