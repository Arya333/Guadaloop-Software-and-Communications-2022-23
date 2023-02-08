import serial
import time
from serial.tools import list_ports

def main():

    port = list(list_ports.comports())
    s = serial.Serial('COM5',baudrate=115200)
    temp = time.time()
    message = "AT+SEND=1,4,op\r\n".encode()
    while True:
        res = s.read()
        print()
        # s.reset_input_buffer()
        count = 0
        t_end = time.time() + .5
        while time.time() < t_end:
            temp1 = time.time()
            s.write(message)
            time.sleep(.05)
            # res = s.readline()
            count += 1
        print(count)
        print()
        s.reset_input_buffer()
        t_end = time.time() + .5
        while time.time() < t_end:
            res = s.readline()
            print(str(res) + " " + str(time.time() - temp))
        print()

if __name__ == '__main__':
    main()