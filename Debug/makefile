################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./source/F2837xD_Adc.obj" \
"./source/F2837xD_CodeStartBranch.obj" \
"./source/F2837xD_DefaultISR.obj" \
"./source/F2837xD_EPwm.obj" \
"./source/F2837xD_EQep.obj" \
"./source/F2837xD_GlobalVariableDefs.obj" \
"./source/F2837xD_Gpio.obj" \
"./source/F2837xD_Ipc.obj" \
"./source/F2837xD_Ipc_Driver_Util.obj" \
"./source/F2837xD_PieCtrl.obj" \
"./source/F2837xD_PieVect.obj" \
"./source/F2837xD_SysCtrl.obj" \
"./source/F2837xD_usDelay.obj" \
"./source/Kalman.obj" \
"./source/User_F2837xD_5742.obj" \
"./source/User_F2837xD_ADC.obj" \
"./source/User_F2837xD_DAC.obj" \
"./source/User_F2837xD_EPWM_EQEP.obj" \
"./source/User_F2837xD_SCI.obj" \
"./source/User_F2837xD_SPI.obj" \
"../cmd/2837xD_RAM_lnk_cpu1.cmd" \
"../cmd/F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/lib/rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include cmd/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include cmd/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
L_high_speed_PMSM.out \

EXE_OUTPUTS__QUOTED += \
"L_high_speed_PMSM.out" \

BIN_OUTPUTS += \
L_high_speed_PMSM.hex \

BIN_OUTPUTS__QUOTED += \
"L_high_speed_PMSM.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "L_high_speed_PMSM.out"

# Tool invocations
L_high_speed_PMSM.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=0 --fp_mode=relaxed --advice:performance=all --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"L_high_speed_PMSM.map" --stack_size=0x200 --warn_sections -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="L_high_speed_PMSM_linkInfo.xml" --rom_model -o "L_high_speed_PMSM.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

L_high_speed_PMSM.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/hex2000"  -o "L_high_speed_PMSM.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "source\F2837xD_Adc.obj" "source\F2837xD_CodeStartBranch.obj" "source\F2837xD_DefaultISR.obj" "source\F2837xD_EPwm.obj" "source\F2837xD_EQep.obj" "source\F2837xD_GlobalVariableDefs.obj" "source\F2837xD_Gpio.obj" "source\F2837xD_Ipc.obj" "source\F2837xD_Ipc_Driver_Util.obj" "source\F2837xD_PieCtrl.obj" "source\F2837xD_PieVect.obj" "source\F2837xD_SysCtrl.obj" "source\F2837xD_usDelay.obj" "source\Kalman.obj" "source\User_F2837xD_5742.obj" "source\User_F2837xD_ADC.obj" "source\User_F2837xD_DAC.obj" "source\User_F2837xD_EPWM_EQEP.obj" "source\User_F2837xD_SCI.obj" "source\User_F2837xD_SPI.obj" 
	-$(RM) "main.d" "source\F2837xD_Adc.d" "source\F2837xD_DefaultISR.d" "source\F2837xD_EPwm.d" "source\F2837xD_EQep.d" "source\F2837xD_GlobalVariableDefs.d" "source\F2837xD_Gpio.d" "source\F2837xD_Ipc.d" "source\F2837xD_Ipc_Driver_Util.d" "source\F2837xD_PieCtrl.d" "source\F2837xD_PieVect.d" "source\F2837xD_SysCtrl.d" "source\Kalman.d" "source\User_F2837xD_5742.d" "source\User_F2837xD_ADC.d" "source\User_F2837xD_DAC.d" "source\User_F2837xD_EPWM_EQEP.d" "source\User_F2837xD_SCI.d" "source\User_F2837xD_SPI.d" 
	-$(RM) "source\F2837xD_CodeStartBranch.d" "source\F2837xD_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

