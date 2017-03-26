import RPi.GPIO as gpio
import time

gpio.setwarnings(False)
LED_PIN = 37

gpio.setmode(gpio.BOARD)
gpio.setup(LED_PIN, gpio.OUT)

try:
    while True:
        gpio.output(LED_PIN, 1)
        time.sleep(1)
        gpio.output(LED_PIN, 0)
        time.sleep(1)
except KeyboardInterrupt:
    gpio.cleanup()
