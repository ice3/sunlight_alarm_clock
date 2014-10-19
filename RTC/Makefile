# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

# if you have placed the alternate core in your sketchbook directory, then you can just mention the core name alone.
#ALTERNATE_CORE = attiny
# If not, you might have to include the full path.
#ALTERNATE_CORE_PATH = /home/sudar/Dropbox/code/arduino-sketches/hardware/attiny/

# ARDUINO_DIR       = /usr/share/arduino
BOARDS_TXT = /home/mfalce/sketchbook/hardware/arduina/boards.txt
# ARDUINO_VAR_PATH = /usr/share/arduino/hardware/arduino/variants
BOARD_TAG    = atmega328bb	
ISP_PORT = /dev/ttyACM0
include $(ARDMK_DIR)/Arduino.mk

# MCU = atmega328p
# F_CPU = 8000000
AVRDUDE_ARD_PROGRAMMER = arduino
AVRDUDE_ARD_BAUDRATE = 57600


# !!! Important. You have to use make ispload to upload when using ISP programmer