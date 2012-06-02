################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PROTO_RFS

dependents:
	-cd /home/utnso/Desarrollo/Proyectos/TAD_sockets/Debug && $(MAKE) all

# Tool invocations
PROTO_RFS: $(OBJS) $(USER_OBJS) /home/utnso/Desarrollo/Proyectos/TAD_sockets/Debug/libTAD_sockets.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/utnso/Desarrollo/Proyectos/TAD_sockets/Debug" -o "PROTO_RFS" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) PROTO_RFS
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/utnso/Desarrollo/Proyectos/TAD_sockets/Debug/libTAD_sockets.so:

-include ../makefile.targets
