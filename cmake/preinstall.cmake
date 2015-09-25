
MESSAGE(STATUS "Running preinstall script")

# run install script
EXECUTE_PROCESS(
	COMMAND bash "preinstall.sh"
	RESULT_VARIABLE PREINSTALL_RESULT
)

IF(NOT "${PREINSTALL_RESULT}" STREQUAL "0")
	MESSAGE(FATAL_ERROR "ERROR: Preinstallscript failed: Maybe you need administrative privileges?")
ENDIF(NOT "${PREINSTALL_RESULT}" STREQUAL "0")

MESSAGE(STATUS "Done")

###############################################################################
