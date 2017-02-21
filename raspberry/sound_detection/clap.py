import RPi.GPIO as gpio
import time

gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)
gpio.setup(11, gpio.IN)

try:
    while True:
        if gpio.input(11) == 0:
            print "clap detected"
            time.sleep(1)
except KeyboardInterrupt:
    print "Killed By User"
