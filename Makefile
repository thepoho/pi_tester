##### Makefile for GAMESHOW #####
## If building on rpi, ensure export HOSTTYPE is included in your .bashrc ##
######


CC=g++
CFLAGS=-Wall -std=c++0x -pthread


ifeq ($(shell echo $(HOSTTYPE)), arm)
  DFLAGS=-D BUILD_RASPI -lwiringpi
endif

ARMCC=arm-linux-gnueabihf-g++
ARMDFLAGS=-D BUILD_RASPI -I./wiring_pi/include -L./wiring_pi/lib_arm  -Wl,--start-group ./wiring_pi/lib_arm/libWiringPi.so -Wl,--end-group

INCLUDE = 	./include
SOURCE = 	./src/*.cpp ./src/*.c

pi_tester :
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX $(DFLAGS) -iquote $(INCLUDE) $(SOURCE) -o pi_tester

arm : 
	$(ARMCC) $(CFLAGS) -D _DEBUG -D _LINUX $(ARMDFLAGS) -iquote $(INCLUDE) $(SOURCE) -o pi_tester_arm

arm_cc: 
	make arm && scp pi_tester_arm pi@192.168.0.14:/home/pi/pi_tester_arm && rsync -avz public_html pi@192.168.0.14:/home/pi/pi_tester_arm && ssh 192.168.0.14 -lpi -t 'sudo /bin/bash -c "cd /home/pi/pi_tester_arm && /home/pi/pi_tester_arm/pi_tester_arm"'


clean:
	$(RM) pi_tester
clean_arm:
	$(RM) pi_tester_arm

