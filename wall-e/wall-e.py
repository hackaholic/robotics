import sys
import time
import RPi.GPIO as gpio

from curtsies import Input

gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)

LED_PIN = 40
EN1, EN2 = 15, 7
C1A, C1B = 16, 18
C2A, C2B = 8, 10 

gpio.setup(EN1, gpio.OUT)
gpio.setup(EN2, gpio.OUT)
gpio.setup(C1A, gpio.OUT)
gpio.setup(C1B, gpio.OUT)
gpio.setup(C2A, gpio.OUT)
gpio.setup(C2B, gpio.OUT)
gpio.setup(LED_PIN, gpio.OUT)

gpio.output(LED_PIN, 1)
gpio.output(EN1, 1)
gpio.output(EN2, 1)

def clock(a,b):

    gpio.output(a, 1)
    gpio.output(b, 0)    

def anticlock(a,b):

    gpio.output(a, 0)
    gpio.output(b, 1) 

def stop(a, b):

    gpio.output(a, 0)
    gpio.output(b, 0) 

def main():
    try:
        with Input(keynames='curses') as input_generator:
            for key in input_generator:
                if key == 'KEY_UP':
                    anticlock(C1A, C1B)
                    anticlock(C2A, C2B)

                if key == 'KEY_DOWN':
                    clock(C1A, C1B)
                    clock(C2A, C2B)
            
                if key == 'KEY_RIGHT':
                    stop(C1A, C1B)
                    stop(C2A, C2B)
                    clock(C1A, C1B)
                    time.sleep(0.1)
                    stop(C1A, C1B)

                if key == 'KEY_LEFT':
                    stop(C1A, C1B)
                    stop(C2A, C2B)
                    clock(C2A, C2B)
                    time.sleep(0.1)
                    stop(C2A, C2B)

                if key == 's':
                    stop(C1A, C1B)
                    stop(C2A, C2B)
    except KeyboardInterrupt:
        gpio.cleanup()
        sys.exit(0)

main()
