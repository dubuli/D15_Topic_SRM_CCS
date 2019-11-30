################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
F:/kuaipan/ALsrm/CCS/sLED2/rts2800_ml.lib 

C_SRCS += \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_DefaultIsr.c \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_GlobalVariableDefs.c \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_MemCopy.c \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieCtrl.c \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieVect.c \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_SysCtrl.c \
F:/kuaipan/ALsrm/CCS/sLED2/main.c 

ASM_SRCS += \
F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_CodeStartBranch.asm 

CMD_SRCS += \
F:/kuaipan/ALsrm/CCS/sLED2/RAM_Link.cmd 

ASM_DEPS += \
./DSP281x_CodeStartBranch.pp 

OBJS += \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_CodeStartBranch.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_DefaultIsr.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_GlobalVariableDefs.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_MemCopy.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_PieCtrl.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_PieVect.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_SysCtrl.obj \
F:/kuaipan/ALsrm/CCS/sLED2/Debug/main.obj 

C_DEPS += \
./DSP281x_DefaultIsr.pp \
./DSP281x_GlobalVariableDefs.pp \
./DSP281x_MemCopy.pp \
./DSP281x_PieCtrl.pp \
./DSP281x_PieVect.pp \
./DSP281x_SysCtrl.pp \
./main.pp 

OBJS__QTD += \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_CodeStartBranch.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_DefaultIsr.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_GlobalVariableDefs.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_MemCopy.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_PieCtrl.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_PieVect.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\DSP281x_SysCtrl.obj" \
"F:\kuaipan\ALsrm\CCS\sLED2\Debug\main.obj" 

ASM_DEPS__QTD += \
".\DSP281x_CodeStartBranch.pp" 

C_DEPS__QTD += \
".\DSP281x_DefaultIsr.pp" \
".\DSP281x_GlobalVariableDefs.pp" \
".\DSP281x_MemCopy.pp" \
".\DSP281x_PieCtrl.pp" \
".\DSP281x_PieVect.pp" \
".\DSP281x_SysCtrl.pp" \
".\main.pp" 

ASM_SRCS_QUOTED += \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_CodeStartBranch.asm" 

C_SRCS_QUOTED += \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_DefaultIsr.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_GlobalVariableDefs.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_MemCopy.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieCtrl.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieVect.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_SysCtrl.c" \
"F:/kuaipan/ALsrm/CCS/sLED2/main.c" 


# Each subdirectory must supply rules for building sources it contributes
F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_CodeStartBranch.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_DefaultIsr.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_DefaultIsr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_DefaultIsr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_GlobalVariableDefs.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_MemCopy.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_MemCopy.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_MemCopy.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_PieCtrl.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_PieCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_PieVect.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_PieVect.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_PieVect.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/DSP281x_SysCtrl.obj: F:/kuaipan/ALsrm/CCS/sLED2/DSP281x_SysCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="DSP281x_SysCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

F:/kuaipan/ALsrm/CCS/sLED2/Debug/main.obj: F:/kuaipan/ALsrm/CCS/sLED2/main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="D:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files (x86)/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/LED" --diag_warning=225 --issue_remarks --large_memory_model --unified_memory --obj_directory="F:/kuaipan/ALsrm/CCS/sLED2/Debug" --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


