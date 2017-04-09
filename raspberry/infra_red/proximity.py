import RPi.GPIO as gpio

SIG_PIN = 31

gpio.setmode(gpio.BOARD)
gpio.setup(SIG_PIN, gpio.IN)

while True:
    if gpio.input(SIG_PIN):
        print "Obstacle detected"
