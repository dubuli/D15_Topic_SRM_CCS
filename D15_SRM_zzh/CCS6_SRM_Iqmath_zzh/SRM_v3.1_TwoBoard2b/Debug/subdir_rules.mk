################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SRM_double_EV.obj: ../SRM_double_EV.C $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/CCS6_SRM_zzh/SRM_v3.1_TwoBoard2b" -g --define="_DEBUG" --define="LARGE_MODEL" --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="SRM_double_EV.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

START.obj: ../START.C $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/CCS6_SRM_zzh/SRM_v3.1_TwoBoard2b" -g --define="_DEBUG" --define="LARGE_MODEL" --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="START.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


