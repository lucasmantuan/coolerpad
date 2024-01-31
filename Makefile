CC = gcc
CFLAGS = -Wall

coolerpad: coolerpad.o temperature/temperature.o pwm/pwm.o motor/motor.o
	$(CC) $(CFLAGS) -o coolerpad coolerpad.o temperature/temperature.o pwm/pwm.o motor/motor.o

coolerpad.o: coolerpad.c temperature/temperature.h pwm/pwm.h motor/motor.h
	$(CC) $(CFLAGS) -c coolerpad.c

temperature/temperature.o: temperature/temperature.c temperature/temperature.h
	$(CC) $(CFLAGS) -c temperature/temperature.c -o temperature/temperature.o

pwm/pwm.o: pwm/pwm.c pwm/pwm.h
	$(CC) $(CFLAGS) -c pwm/pwm.c -o pwm/pwm.o

motor/motor.o: motor/motor.c motor/motor.h
	$(CC) $(CFLAGS) -c motor/motor.c -o motor/motor.o

clean:
	rm -f coolerpad *.o temperature/*.o pwm/*.o motor/*.o
