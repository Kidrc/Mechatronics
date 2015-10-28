#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=drivers/hodor_mech.c drivers/hodor_motors.c drivers/hodor_sensors.c drivers/hodor_battery.c drivers/hodor_gyro.c library/src/AD.c library/src/BOARD.c library/src/ES_Framework.c library/src/IO_Ports.c library/src/pwm.c library/src/roach.c library/src/serial.c library/src/RC_Servo.c library/src/LED.c library/src/i2c_master.c statemachines/FindRuling/FindRuling_2ndLevel.c statemachines/FindRuling/SearchCastleSE_3rdLevel.c statemachines/FindRuling/SearchCastleSW_3rdLevel.c statemachines/FindRuling/SearchCastleNW_3rdLevel.c statemachines/AlignReverse.c statemachines/ReturnCenter.c statemachines/SearchCastle.c statemachines/Rotate.c statemachines/LeaveHome/LeaveHome_2ndLevel.c statemachines/LeaveHome/StartPoint_3rdLevel.c statemachines/toplevel.c EventCheckers.c statemachines/RetrieveCrown_2ndLevel.c statemachines/ReturnHome_2ndLevel.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/drivers/hodor_mech.o ${OBJECTDIR}/drivers/hodor_motors.o ${OBJECTDIR}/drivers/hodor_sensors.o ${OBJECTDIR}/drivers/hodor_battery.o ${OBJECTDIR}/drivers/hodor_gyro.o ${OBJECTDIR}/library/src/AD.o ${OBJECTDIR}/library/src/BOARD.o ${OBJECTDIR}/library/src/ES_Framework.o ${OBJECTDIR}/library/src/IO_Ports.o ${OBJECTDIR}/library/src/pwm.o ${OBJECTDIR}/library/src/roach.o ${OBJECTDIR}/library/src/serial.o ${OBJECTDIR}/library/src/RC_Servo.o ${OBJECTDIR}/library/src/LED.o ${OBJECTDIR}/library/src/i2c_master.o ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o ${OBJECTDIR}/statemachines/AlignReverse.o ${OBJECTDIR}/statemachines/ReturnCenter.o ${OBJECTDIR}/statemachines/SearchCastle.o ${OBJECTDIR}/statemachines/Rotate.o ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o ${OBJECTDIR}/statemachines/toplevel.o ${OBJECTDIR}/EventCheckers.o ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/drivers/hodor_mech.o.d ${OBJECTDIR}/drivers/hodor_motors.o.d ${OBJECTDIR}/drivers/hodor_sensors.o.d ${OBJECTDIR}/drivers/hodor_battery.o.d ${OBJECTDIR}/drivers/hodor_gyro.o.d ${OBJECTDIR}/library/src/AD.o.d ${OBJECTDIR}/library/src/BOARD.o.d ${OBJECTDIR}/library/src/ES_Framework.o.d ${OBJECTDIR}/library/src/IO_Ports.o.d ${OBJECTDIR}/library/src/pwm.o.d ${OBJECTDIR}/library/src/roach.o.d ${OBJECTDIR}/library/src/serial.o.d ${OBJECTDIR}/library/src/RC_Servo.o.d ${OBJECTDIR}/library/src/LED.o.d ${OBJECTDIR}/library/src/i2c_master.o.d ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d ${OBJECTDIR}/statemachines/AlignReverse.o.d ${OBJECTDIR}/statemachines/ReturnCenter.o.d ${OBJECTDIR}/statemachines/SearchCastle.o.d ${OBJECTDIR}/statemachines/Rotate.o.d ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d ${OBJECTDIR}/statemachines/toplevel.o.d ${OBJECTDIR}/EventCheckers.o.d ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/drivers/hodor_mech.o ${OBJECTDIR}/drivers/hodor_motors.o ${OBJECTDIR}/drivers/hodor_sensors.o ${OBJECTDIR}/drivers/hodor_battery.o ${OBJECTDIR}/drivers/hodor_gyro.o ${OBJECTDIR}/library/src/AD.o ${OBJECTDIR}/library/src/BOARD.o ${OBJECTDIR}/library/src/ES_Framework.o ${OBJECTDIR}/library/src/IO_Ports.o ${OBJECTDIR}/library/src/pwm.o ${OBJECTDIR}/library/src/roach.o ${OBJECTDIR}/library/src/serial.o ${OBJECTDIR}/library/src/RC_Servo.o ${OBJECTDIR}/library/src/LED.o ${OBJECTDIR}/library/src/i2c_master.o ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o ${OBJECTDIR}/statemachines/AlignReverse.o ${OBJECTDIR}/statemachines/ReturnCenter.o ${OBJECTDIR}/statemachines/SearchCastle.o ${OBJECTDIR}/statemachines/Rotate.o ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o ${OBJECTDIR}/statemachines/toplevel.o ${OBJECTDIR}/EventCheckers.o ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=drivers/hodor_mech.c drivers/hodor_motors.c drivers/hodor_sensors.c drivers/hodor_battery.c drivers/hodor_gyro.c library/src/AD.c library/src/BOARD.c library/src/ES_Framework.c library/src/IO_Ports.c library/src/pwm.c library/src/roach.c library/src/serial.c library/src/RC_Servo.c library/src/LED.c library/src/i2c_master.c statemachines/FindRuling/FindRuling_2ndLevel.c statemachines/FindRuling/SearchCastleSE_3rdLevel.c statemachines/FindRuling/SearchCastleSW_3rdLevel.c statemachines/FindRuling/SearchCastleNW_3rdLevel.c statemachines/AlignReverse.c statemachines/ReturnCenter.c statemachines/SearchCastle.c statemachines/Rotate.c statemachines/LeaveHome/LeaveHome_2ndLevel.c statemachines/LeaveHome/StartPoint_3rdLevel.c statemachines/toplevel.c EventCheckers.c statemachines/RetrieveCrown_2ndLevel.c statemachines/ReturnHome_2ndLevel.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/drivers/hodor_mech.o: drivers/hodor_mech.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_mech.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_mech.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_mech.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_mech.o.d" -o ${OBJECTDIR}/drivers/hodor_mech.o drivers/hodor_mech.c   
	
${OBJECTDIR}/drivers/hodor_motors.o: drivers/hodor_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_motors.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_motors.o.d" -o ${OBJECTDIR}/drivers/hodor_motors.o drivers/hodor_motors.c   
	
${OBJECTDIR}/drivers/hodor_sensors.o: drivers/hodor_sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_sensors.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_sensors.o.d" -o ${OBJECTDIR}/drivers/hodor_sensors.o drivers/hodor_sensors.c   
	
${OBJECTDIR}/drivers/hodor_battery.o: drivers/hodor_battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_battery.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_battery.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_battery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_battery.o.d" -o ${OBJECTDIR}/drivers/hodor_battery.o drivers/hodor_battery.c   
	
${OBJECTDIR}/drivers/hodor_gyro.o: drivers/hodor_gyro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_gyro.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_gyro.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_gyro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_gyro.o.d" -o ${OBJECTDIR}/drivers/hodor_gyro.o drivers/hodor_gyro.c   
	
${OBJECTDIR}/library/src/AD.o: library/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/AD.o.d 
	@${RM} ${OBJECTDIR}/library/src/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/AD.o.d" -o ${OBJECTDIR}/library/src/AD.o library/src/AD.c   
	
${OBJECTDIR}/library/src/BOARD.o: library/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/library/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/BOARD.o.d" -o ${OBJECTDIR}/library/src/BOARD.o library/src/BOARD.c   
	
${OBJECTDIR}/library/src/ES_Framework.o: library/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/library/src/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/ES_Framework.o.d" -o ${OBJECTDIR}/library/src/ES_Framework.o library/src/ES_Framework.c   
	
${OBJECTDIR}/library/src/IO_Ports.o: library/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/library/src/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/IO_Ports.o.d" -o ${OBJECTDIR}/library/src/IO_Ports.o library/src/IO_Ports.c   
	
${OBJECTDIR}/library/src/pwm.o: library/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/pwm.o.d 
	@${RM} ${OBJECTDIR}/library/src/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/pwm.o.d" -o ${OBJECTDIR}/library/src/pwm.o library/src/pwm.c   
	
${OBJECTDIR}/library/src/roach.o: library/src/roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/roach.o.d 
	@${RM} ${OBJECTDIR}/library/src/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/roach.o.d" -o ${OBJECTDIR}/library/src/roach.o library/src/roach.c   
	
${OBJECTDIR}/library/src/serial.o: library/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/serial.o.d 
	@${RM} ${OBJECTDIR}/library/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/serial.o.d" -o ${OBJECTDIR}/library/src/serial.o library/src/serial.c   
	
${OBJECTDIR}/library/src/RC_Servo.o: library/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/library/src/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/RC_Servo.o.d" -o ${OBJECTDIR}/library/src/RC_Servo.o library/src/RC_Servo.c   
	
${OBJECTDIR}/library/src/LED.o: library/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/LED.o.d 
	@${RM} ${OBJECTDIR}/library/src/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/LED.o.d" -o ${OBJECTDIR}/library/src/LED.o library/src/LED.c   
	
${OBJECTDIR}/library/src/i2c_master.o: library/src/i2c_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/library/src/i2c_master.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/i2c_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/i2c_master.o.d" -o ${OBJECTDIR}/library/src/i2c_master.o library/src/i2c_master.c   
	
${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o: statemachines/FindRuling/FindRuling_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o statemachines/FindRuling/FindRuling_2ndLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o: statemachines/FindRuling/SearchCastleSE_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o statemachines/FindRuling/SearchCastleSE_3rdLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o: statemachines/FindRuling/SearchCastleSW_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o statemachines/FindRuling/SearchCastleSW_3rdLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o: statemachines/FindRuling/SearchCastleNW_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o statemachines/FindRuling/SearchCastleNW_3rdLevel.c   
	
${OBJECTDIR}/statemachines/AlignReverse.o: statemachines/AlignReverse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/AlignReverse.o.d 
	@${RM} ${OBJECTDIR}/statemachines/AlignReverse.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/AlignReverse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/AlignReverse.o.d" -o ${OBJECTDIR}/statemachines/AlignReverse.o statemachines/AlignReverse.c   
	
${OBJECTDIR}/statemachines/ReturnCenter.o: statemachines/ReturnCenter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/ReturnCenter.o.d 
	@${RM} ${OBJECTDIR}/statemachines/ReturnCenter.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/ReturnCenter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/ReturnCenter.o.d" -o ${OBJECTDIR}/statemachines/ReturnCenter.o statemachines/ReturnCenter.c   
	
${OBJECTDIR}/statemachines/SearchCastle.o: statemachines/SearchCastle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/SearchCastle.o.d 
	@${RM} ${OBJECTDIR}/statemachines/SearchCastle.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/SearchCastle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/SearchCastle.o.d" -o ${OBJECTDIR}/statemachines/SearchCastle.o statemachines/SearchCastle.c   
	
${OBJECTDIR}/statemachines/Rotate.o: statemachines/Rotate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/Rotate.o.d 
	@${RM} ${OBJECTDIR}/statemachines/Rotate.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/Rotate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/Rotate.o.d" -o ${OBJECTDIR}/statemachines/Rotate.o statemachines/Rotate.c   
	
${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o: statemachines/LeaveHome/LeaveHome_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/LeaveHome 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o statemachines/LeaveHome/LeaveHome_2ndLevel.c   
	
${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o: statemachines/LeaveHome/StartPoint_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/LeaveHome 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o statemachines/LeaveHome/StartPoint_3rdLevel.c   
	
${OBJECTDIR}/statemachines/toplevel.o: statemachines/toplevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/toplevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/toplevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/toplevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/toplevel.o.d" -o ${OBJECTDIR}/statemachines/toplevel.o statemachines/toplevel.c   
	
${OBJECTDIR}/EventCheckers.o: EventCheckers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/EventCheckers.o 
	@${FIXDEPS} "${OBJECTDIR}/EventCheckers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/EventCheckers.o.d" -o ${OBJECTDIR}/EventCheckers.o EventCheckers.c   
	
${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o: statemachines/RetrieveCrown_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o statemachines/RetrieveCrown_2ndLevel.c   
	
${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o: statemachines/ReturnHome_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o statemachines/ReturnHome_2ndLevel.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
else
${OBJECTDIR}/drivers/hodor_mech.o: drivers/hodor_mech.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_mech.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_mech.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_mech.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_mech.o.d" -o ${OBJECTDIR}/drivers/hodor_mech.o drivers/hodor_mech.c   
	
${OBJECTDIR}/drivers/hodor_motors.o: drivers/hodor_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_motors.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_motors.o.d" -o ${OBJECTDIR}/drivers/hodor_motors.o drivers/hodor_motors.c   
	
${OBJECTDIR}/drivers/hodor_sensors.o: drivers/hodor_sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_sensors.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_sensors.o.d" -o ${OBJECTDIR}/drivers/hodor_sensors.o drivers/hodor_sensors.c   
	
${OBJECTDIR}/drivers/hodor_battery.o: drivers/hodor_battery.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_battery.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_battery.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_battery.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_battery.o.d" -o ${OBJECTDIR}/drivers/hodor_battery.o drivers/hodor_battery.c   
	
${OBJECTDIR}/drivers/hodor_gyro.o: drivers/hodor_gyro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/drivers 
	@${RM} ${OBJECTDIR}/drivers/hodor_gyro.o.d 
	@${RM} ${OBJECTDIR}/drivers/hodor_gyro.o 
	@${FIXDEPS} "${OBJECTDIR}/drivers/hodor_gyro.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/drivers/hodor_gyro.o.d" -o ${OBJECTDIR}/drivers/hodor_gyro.o drivers/hodor_gyro.c   
	
${OBJECTDIR}/library/src/AD.o: library/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/AD.o.d 
	@${RM} ${OBJECTDIR}/library/src/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/AD.o.d" -o ${OBJECTDIR}/library/src/AD.o library/src/AD.c   
	
${OBJECTDIR}/library/src/BOARD.o: library/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/BOARD.o.d 
	@${RM} ${OBJECTDIR}/library/src/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/BOARD.o.d" -o ${OBJECTDIR}/library/src/BOARD.o library/src/BOARD.c   
	
${OBJECTDIR}/library/src/ES_Framework.o: library/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/library/src/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/ES_Framework.o.d" -o ${OBJECTDIR}/library/src/ES_Framework.o library/src/ES_Framework.c   
	
${OBJECTDIR}/library/src/IO_Ports.o: library/src/IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/library/src/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/IO_Ports.o.d" -o ${OBJECTDIR}/library/src/IO_Ports.o library/src/IO_Ports.c   
	
${OBJECTDIR}/library/src/pwm.o: library/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/pwm.o.d 
	@${RM} ${OBJECTDIR}/library/src/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/pwm.o.d" -o ${OBJECTDIR}/library/src/pwm.o library/src/pwm.c   
	
${OBJECTDIR}/library/src/roach.o: library/src/roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/roach.o.d 
	@${RM} ${OBJECTDIR}/library/src/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/roach.o.d" -o ${OBJECTDIR}/library/src/roach.o library/src/roach.c   
	
${OBJECTDIR}/library/src/serial.o: library/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/serial.o.d 
	@${RM} ${OBJECTDIR}/library/src/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/serial.o.d" -o ${OBJECTDIR}/library/src/serial.o library/src/serial.c   
	
${OBJECTDIR}/library/src/RC_Servo.o: library/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/library/src/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/RC_Servo.o.d" -o ${OBJECTDIR}/library/src/RC_Servo.o library/src/RC_Servo.c   
	
${OBJECTDIR}/library/src/LED.o: library/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/LED.o.d 
	@${RM} ${OBJECTDIR}/library/src/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/LED.o.d" -o ${OBJECTDIR}/library/src/LED.o library/src/LED.c   
	
${OBJECTDIR}/library/src/i2c_master.o: library/src/i2c_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/library/src 
	@${RM} ${OBJECTDIR}/library/src/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/library/src/i2c_master.o 
	@${FIXDEPS} "${OBJECTDIR}/library/src/i2c_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/library/src/i2c_master.o.d" -o ${OBJECTDIR}/library/src/i2c_master.o library/src/i2c_master.c   
	
${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o: statemachines/FindRuling/FindRuling_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/FindRuling_2ndLevel.o statemachines/FindRuling/FindRuling_2ndLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o: statemachines/FindRuling/SearchCastleSE_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSE_3rdLevel.o statemachines/FindRuling/SearchCastleSE_3rdLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o: statemachines/FindRuling/SearchCastleSW_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleSW_3rdLevel.o statemachines/FindRuling/SearchCastleSW_3rdLevel.c   
	
${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o: statemachines/FindRuling/SearchCastleNW_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/FindRuling 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/FindRuling/SearchCastleNW_3rdLevel.o statemachines/FindRuling/SearchCastleNW_3rdLevel.c   
	
${OBJECTDIR}/statemachines/AlignReverse.o: statemachines/AlignReverse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/AlignReverse.o.d 
	@${RM} ${OBJECTDIR}/statemachines/AlignReverse.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/AlignReverse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/AlignReverse.o.d" -o ${OBJECTDIR}/statemachines/AlignReverse.o statemachines/AlignReverse.c   
	
${OBJECTDIR}/statemachines/ReturnCenter.o: statemachines/ReturnCenter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/ReturnCenter.o.d 
	@${RM} ${OBJECTDIR}/statemachines/ReturnCenter.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/ReturnCenter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/ReturnCenter.o.d" -o ${OBJECTDIR}/statemachines/ReturnCenter.o statemachines/ReturnCenter.c   
	
${OBJECTDIR}/statemachines/SearchCastle.o: statemachines/SearchCastle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/SearchCastle.o.d 
	@${RM} ${OBJECTDIR}/statemachines/SearchCastle.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/SearchCastle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/SearchCastle.o.d" -o ${OBJECTDIR}/statemachines/SearchCastle.o statemachines/SearchCastle.c   
	
${OBJECTDIR}/statemachines/Rotate.o: statemachines/Rotate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/Rotate.o.d 
	@${RM} ${OBJECTDIR}/statemachines/Rotate.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/Rotate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/Rotate.o.d" -o ${OBJECTDIR}/statemachines/Rotate.o statemachines/Rotate.c   
	
${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o: statemachines/LeaveHome/LeaveHome_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/LeaveHome 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/LeaveHome/LeaveHome_2ndLevel.o statemachines/LeaveHome/LeaveHome_2ndLevel.c   
	
${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o: statemachines/LeaveHome/StartPoint_3rdLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines/LeaveHome 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o.d" -o ${OBJECTDIR}/statemachines/LeaveHome/StartPoint_3rdLevel.o statemachines/LeaveHome/StartPoint_3rdLevel.c   
	
${OBJECTDIR}/statemachines/toplevel.o: statemachines/toplevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/toplevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/toplevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/toplevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/toplevel.o.d" -o ${OBJECTDIR}/statemachines/toplevel.o statemachines/toplevel.c   
	
${OBJECTDIR}/EventCheckers.o: EventCheckers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/EventCheckers.o 
	@${FIXDEPS} "${OBJECTDIR}/EventCheckers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/EventCheckers.o.d" -o ${OBJECTDIR}/EventCheckers.o EventCheckers.c   
	
${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o: statemachines/RetrieveCrown_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/RetrieveCrown_2ndLevel.o statemachines/RetrieveCrown_2ndLevel.c   
	
${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o: statemachines/ReturnHome_2ndLevel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/statemachines 
	@${RM} ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d 
	@${RM} ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o 
	@${FIXDEPS} "${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o.d" -o ${OBJECTDIR}/statemachines/ReturnHome_2ndLevel.o statemachines/ReturnHome_2ndLevel.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -I"drivers" -I"library/include" -I"statemachines" -I"../I2CTest.X" -I"statemachines/LeaveHome" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/I2CTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
