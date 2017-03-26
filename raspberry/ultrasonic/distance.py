import RPi.GPIO as gpio
import time

#disabling warning
gpio.setwarnings(False) 

#selecting board
gpio.setmode(gpio.BOARD)

trig = 37 # pin to trigger ultrasonic wave
echo = 38 # pin to recive echo
def distance():
    # setting pin 7 for output 
    gpio.setup(trig,gpio.OUT)
    gpio.output(trig,0)

    #setting pin 8 for input for return echo
    gpio.setup(echo,gpio.IN)

    time.sleep(0.1)

    gpio.output(trig,1)
    time.sleep(0.00001)
    gpio.output(trig,0)
    start_check=time.time()
    while gpio.input(echo) == 0:
        if time.time()-start_check > 1:
            distance()
        pass
    
    start = time.time()
    start_check = time.time()
    while gpio.input(echo) == 1:
        if time.time()-start_check > 1:
            distance()
        pass
    stop = time.time()

    k = (stop-start)*17000
    print str(k) + " cm"

while True:
    try:
        distance()
    except KeyboardInterrupt:
        gpio.cleanup()
