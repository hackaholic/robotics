import sys
import time
import threading
import RPi.GPIO as gpio

from curtsies import Input
from distance import *
gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)

LED_PIN = 40
INFRA_FRONT_LEFT, INFRA_FRONT_RIGHT = 31, 32
ULTRASONIC_FRONT_TRIG, ULTRASONIC_FRONT_ECHO = 37, 38
ULTRASONIC_BACK_TRIG, ULTRASONIC_BACK_ECHO = 21, 22
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
gpio.setup(INFRA_FRONT_LEFT, gpio.IN)
gpio.setup(INFRA_FRONT_RIGHT, gpio.IN)

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


def distance_check_front():
    while distance(ULTRASONIC_FRONT_TRIG, ULTRASONIC_FRONT_ECHO)>20:
        pass
    clock(C1A, C1B)
    clock(C2A, C2B)
    time.sleep(0.1)
    stop(C1A, C1B)
    stop(C2A, C2B)

def distance_check_back():
    while distance(ULTRASONIC_BACK_TRIG, ULTRASONIC_BACK_ECHO)>20:
        pass
    anticlock(C1A, C1B)
    anticlock(C2A, C2B)
    time.sleep(0.1)
    stop(C1A, C1B)
    stop(C2A, C2B) 

def proximity_check(pin):
    while not gpio.input(pin):
        pass
    clock(C1A, C1B)
    clock(C2A, C2B)
    time.sleep(0.1)
    stop(C1A, C1B)
    stop(C2A, C2B)

       

def main():
    try:
        with Input(keynames='curses') as input_generator:
            for key in input_generator:
                if key == 'KEY_UP' and distance(ULTRASONIC_FRONT_TRIG, ULTRASONIC_FRONT_ECHO)>3:
                    anticlock(C1A, C1B)
                    anticlock(C2A, C2B)
                    t_front = threading.Thread(target=distance_check_front)
                    t_front.start()
                    t_front1 = threading.Thread(target=proximity_check, args=(INFRA_FRONT_LEFT,))
                    t_front2 = threading.Thread(target=proximity_check, args=(INFRA_FRONT_RIGHT,))
                    t_front1.start()
                    t_front2.start()
  
                if key == 'KEY_DOWN' and distance(ULTRASONIC_BACK_TRIG, ULTRASONIC_BACK_ECHO)>3:
                    clock(C1A, C1B)
                    clock(C2A, C2B)
                    t_back = threading.Thread(target=distance_check_back)
                    t_back.start()
            
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
