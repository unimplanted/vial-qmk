# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/PlumSTM32F103/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/PlumSTM32F103

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
