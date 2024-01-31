coolerpad: coolerpad.o temperature.o pwm.o motor.o
	gcc -o coolerpad coolerpad.o temperature.o pwm.o motor.o

coolerpad.o: coolerpad.c temperature.h pwm.h motor.h
	gcc -c coolerpad.c

temperature.o: temperature.c temperature.h
	gcc -c temperature.c

pwm.o: pwm.c pwm.h
	gcc -c pwm.c

motor.o: motor.c motor.h
	gcc -c motor.c

clean:
	rm -f coolerpad *.o