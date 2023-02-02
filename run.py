from ctypes import *

import numpy as np
import cv2
import keyboard

import time

import threading

def get_buttons() -> int:
    """
    (Start, Select, A, B, Up, Down, Left, Right)
    """
    out = 0
    if keyboard.is_pressed('enter'):
        out |= 0b10000000
    if keyboard.is_pressed('shift'):
        out |= 0b01000000
    if keyboard.is_pressed('l'): # a
        out |= 0b00100000
    if keyboard.is_pressed('k'): # b
        out |= 0b00010000
    if keyboard.is_pressed('w'):
        out |= 0b00001000
    if keyboard.is_pressed('s'):
        out |= 0b00000100
    if keyboard.is_pressed('a'):
        out |= 0b00000010
    if keyboard.is_pressed('d'):
        out |= 0b00000001
    return out

def calculate_fps():
    if not hasattr(calculate_fps, "start_time"):
        calculate_fps.counter = 0
        calculate_fps.start_time = time.time()


    if time.time() - calculate_fps.start_time >= 1:
        print(f"FPS: {calculate_fps.counter / (time.time() - calculate_fps.start_time):.2f}")
        calculate_fps.start_time = time.time()
        calculate_fps.counter = 0
    else:
        calculate_fps.counter += 1

DLL_PATH = "C:/Users/Gerald/Projects/GBEmu/build/Debug/GBEmu.dll"

ROM_PATH = b"C:/Users/Gerald/Projects/GBEmu/roms/"
# ROM_PATH += b"pokemon.gb"
# ROM_PATH += b"drMario.gb"
ROM_PATH += b"zelda.gb"


dll = cdll.LoadLibrary(DLL_PATH)

dll.emu_init.argtypes = [c_char_p, POINTER(c_uint8)]
dll.emu_init.restype = None
dll.emu_frame.argtypes = [c_uint8]
dll.emu_frame.restype = None
dll.emu_stop.argtypes = None
dll.emu_stop.restype = None


buffer = (c_uint8 * 23040)(*([0]*23040))
frame = np.ctypeslib.as_array(buffer).reshape(144, 160)

dll.emu_init(ROM_PATH, buffer)

running = True

def renderImage():
    global running
    while (running):
        cv2.imshow("frame", frame)
        if cv2.waitKey(1) == 27:
            cv2.destroyAllWindows()
            running = False

display = threading.Thread(target=renderImage)
display.start()

while running:

    dll.emu_frame(get_buttons())

    calculate_fps()

dll.emu_stop()