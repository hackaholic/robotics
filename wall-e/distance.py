import RPi.GPIO as gpio
import time

#disabling warning
gpio.setwarnings(False) 

#selecting board
gpio.setmode(gpio.BOARD)

def distance(trig, echo):
    gpio.setup(trig,gpio.OUT)
    gpio.output(trig,0)

    gpio.setup(echo,gpio.IN)

    time.sleep(0.1)

    gpio.output(trig,1)
    time.sleep(0.00001)
    gpio.output(trig,0)
    start_check=time.time()
    while gpio.input(echo) == 0:
        if time.time()-start_check > 1:
            return 100
        pass
    
    start = time.time()
    start_check = time.time()
    while gpio.input(echo) == 1:
        if time.time()-start_check > 1:
            return 100
        pass
    stop = time.time()

    k = (stop-start)*17000
    print str(k) + " cm"
    return int(k)
