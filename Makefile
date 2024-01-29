coolerpad: coolerpad.o temperature.o pwm.o
	gcc -o coolerpad coolerpad.o temperature.o pwm.o

coolerpad.o: coolerpad.c temperature.h pwm.h
	gcc -c coolerpad.c

temperature.o: temperature.c temperature.h
	gcc -c temperature.c

pwm.o: pwm.c pwm.h
	gcc -c pwm.c

clean:
	rm -f coolerpad *.o