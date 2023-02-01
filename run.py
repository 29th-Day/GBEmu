from ctypes import *

import numpy as np
import cv2
import keyboard

import time

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

DLL_PATH = "C:/Users/Gerald/Projects/GBEmu/build/Debug/GBEmu.dll"

ROM_PATH = b"C:/Users/Gerald/Projects/GBEmu/roms/"
ROM_PATH += b"pokemon.gb"
# ROM_PATH += b"drMario.gb"


dll = cdll.LoadLibrary(DLL_PATH)

dll.emu_frame.argtypes = [POINTER(c_uint8), c_uint8]

dll.emu_init(ROM_PATH)

buffer = (c_uint8 * 23040)(*([0]*23040))

TICKS = 1_000_000
# TICKS = 1_000
# TICKS = 55_500

counter = 0
start_time = time.time()

for tick in range(TICKS):


    dll.emu_frame(buffer, get_buttons())

    # print(tick)

    frame = np.ctypeslib.as_array(buffer).reshape(144, 160)

    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == 27:
        cv2.destroyAllWindows()
        break

    if time.time() - start_time >= 1:
        print(f"FPS: {counter / (time.time() - start_time):.2f}")
        start_time = time.time()
        counter = 0
    else:
        counter += 1
