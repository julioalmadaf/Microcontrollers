################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/idc/idc.c" \

C_SRCS += \
../Sources/idc/idc.c \

OBJS += \
./Sources/idc/idc_c.obj \

OBJS_QUOTED += \
"./Sources/idc/idc_c.obj" \

C_DEPS += \
./Sources/idc/idc_c.d \

C_DEPS_QUOTED += \
"./Sources/idc/idc_c.d" \

OBJS_OS_FORMAT += \
./Sources/idc/idc_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/idc/idc_c.obj: ../Sources/idc/idc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/idc/idc.args" -ObjN="Sources/idc/idc_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/idc/%.d: ../Sources/idc/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


