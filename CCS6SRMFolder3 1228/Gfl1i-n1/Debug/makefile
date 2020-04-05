################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti2/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./DSP281x_Adc.obj" \
"./DSP281x_CodeStartBranch.obj" \
"./DSP281x_CpuTimers.obj" \
"./DSP281x_DefaultIsr.obj" \
"./DSP281x_Ev.obj" \
"./DSP281x_GlobalVariableDefs.obj" \
"./DSP281x_Gpio.obj" \
"./DSP281x_MemCopy.obj" \
"./DSP281x_PieCtrl.obj" \
"./DSP281x_PieVect.obj" \
"./DSP281x_Sci.obj" \
"./DSP281x_SysCtrl.obj" \
"./Ifl1.obj" \
"../Flash_Link.cmd" \
"../rts2800_ml.lib" \
-l"C:/ti2/ccsv6/tools/compiler/c2000_6.2.7/lib/rts2800_ml.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Jfl1PiTwoPhaseStart5.out \

EXE_OUTPUTS__QUOTED += \
"Jfl1PiTwoPhaseStart5.out" \

BIN_OUTPUTS += \
Jfl1PiTwoPhaseStart5.hex \

BIN_OUTPUTS__QUOTED += \
"Jfl1PiTwoPhaseStart5.hex" \


# All Target
all: Jfl1PiTwoPhaseStart5.out

# Tool invocations
Jfl1PiTwoPhaseStart5.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti2/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"Jfl1PiTwoPhaseStart5.map" --stack_size=1000 --warn_sections -i"C:/ti2/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"C:/ti2/ccsv6/tools/compiler/c2000_6.2.7/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="Jfl1PiTwoPhaseStart5_linkInfo.xml" --rom_model -o "Jfl1PiTwoPhaseStart5.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Jfl1PiTwoPhaseStart5.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti2/ccsv6/tools/compiler/c2000_6.2.7/bin/hex2000"  -o "Jfl1PiTwoPhaseStart5.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "DSP281x_Adc.pp" "DSP281x_CpuTimers.pp" "DSP281x_DefaultIsr.pp" "DSP281x_Ev.pp" "DSP281x_GlobalVariableDefs.pp" "DSP281x_Gpio.pp" "DSP281x_MemCopy.pp" "DSP281x_PieCtrl.pp" "DSP281x_PieVect.pp" "DSP281x_Sci.pp" "DSP281x_SysCtrl.pp" "Ifl1.pp" 
	-$(RM) "DSP281x_Adc.obj" "DSP281x_CodeStartBranch.obj" "DSP281x_CpuTimers.obj" "DSP281x_DefaultIsr.obj" "DSP281x_Ev.obj" "DSP281x_GlobalVariableDefs.obj" "DSP281x_Gpio.obj" "DSP281x_MemCopy.obj" "DSP281x_PieCtrl.obj" "DSP281x_PieVect.obj" "DSP281x_Sci.obj" "DSP281x_SysCtrl.obj" "Ifl1.obj" 
	-$(RM) "DSP281x_CodeStartBranch.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

