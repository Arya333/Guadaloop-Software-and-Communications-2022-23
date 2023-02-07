import serial
import time
from serial.tools import list_ports
port = list(list_ports.comports())
s = serial.Serial('COM4',baudrate=115200)
while True:
    # res = s.read()
    print()
    s.reset_input_buffer()
    t_end = time.time() +1
    while time.time() < t_end:
        time.sleep(0.1)
        s.write("AT+SEND=1,4,op\r\n".encode())
        res = s.read()
        print(res)
    print()
    s.reset_input_buffer()
    t_end = time.time() +1
    while time.time() < t_end:
        time.sleep(0.1)
        res = s.read()
        print(res)
    print()