from ctypes import *

import numpy as np
import cv2
import matplotlib.pyplot as plt

dll = cdll.LoadLibrary("C:/Users/Gerald/Projects/GBEmu/build/Debug/GBEmu.dll")
# dll = cdll.LoadLibrary("C:/Users/Gerald/Projects/GBEmu/build/GBEmu.dll")

dll.emu_frame.argtypes = [POINTER(c_uint8), c_bool]

# dll.emu_init(b"C:/Users/Gerald/Projects/GBEmu/roms/dmg-acid2.gb")
dll.emu_init(b"C:/Users/Gerald/Downloads/Dr. Mario (World)/drMario.gb")

buffer = (c_uint8 * 23040)(*([0]*23040))

TICKS = 1_000_000
# TICKS = 1_000
# TICKS = 55_500

for tick in range(TICKS):
    
    select = 1 if tick % 50 == 0 else 0 
    
    dll.emu_frame(buffer, select)

    print(tick)

    frame = np.ctypeslib.as_array(buffer).reshape(144, 160)

    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == 27:
        cv2.destroyAllWindows()
        break