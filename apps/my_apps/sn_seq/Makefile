# $Id$

################################################################################
# following setup taken from environment variables
################################################################################

PROCESSOR =	$(MIOS32_PROCESSOR)
FAMILY    = 	$(MIOS32_FAMILY)
BOARD	  = 	$(MIOS32_BOARD)
LCD       =     $(MIOS32_LCD)


################################################################################
# Source Files, include paths and libraries
################################################################################

# add C files here
THUMB_SOURCE    = seq.c \
				  my_seq_lcd.c \
				  $(MIOS32_PATH)/apps/sequencers/midibox_seq_v4/core/seq_blm8x8.c \
				  $(MIOS32_PATH)/apps/sequencers/midibox_seq_v4/core/seq_hwcfg.c \
				  $(MIOS32_PATH)/modules/blm/blm.c \
#				  $(MIOS32_PATH)/modules/file/file.c \
#				  $(MIOS32_PATH)/modules/fatfs/src/ff.c \
#				  $(MIOS32_PATH)/modules/fatfs/src/diskio.c

# add C++ files here
THUMB_CPP_SOURCE = app.cpp \
				   Editor.cpp \
				   Display.cpp \
				   hwcfg.cpp \
				   Sequencer.cpp

# (following source stubs not relevant for Cortex M3 derivatives)
THUMB_AS_SOURCE =
ARM_SOURCE      =
ARM_AS_SOURCE   =

C_INCLUDE = 	-I . \
				-I $(MIOS32_PATH)/apps/sequencers/midibox_seq_v4/core/ \
				-I $(MIOS32_PATH)/modules/file/ \
				-I $(MIOS32_PATH)/modules/fatfs/src/

A_INCLUDE = 	-I .

LIBS = 		


################################################################################
# Remaining variables
################################################################################

LD_FILE   = 	$(MIOS32_PATH)/etc/ld/$(FAMILY)/$(PROCESSOR).ld
PROJECT   = 	project

DEBUG     =	-g
OPTIMIZE  =	-Os

CFLAGS =	$(DEBUG) $(OPTIMIZE)


################################################################################
# Include source modules via additional makefiles
################################################################################

# sources of programming model
include $(MIOS32_PATH)/programming_models/traditional/programming_model.mk

# application specific LCD driver (selected via makefile variable)
include $(MIOS32_PATH)/modules/app_lcd/$(LCD)/app_lcd.mk

# Notestack functions
include $(MIOS32_PATH)/modules/notestack/notestack.mk

# generic sequencer modules
include $(MIOS32_PATH)/modules/sequencer/sequencer.mk

# common make rules
# Please keep this include statement at the end of this Makefile. Add new modules above.
include $(MIOS32_PATH)/include/makefile/common.mk
