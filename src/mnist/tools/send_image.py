import serial
import serial.tools.list_ports
import time
import numpy as np
from tensorflow import keras

def main():
    port = serial.Serial("/dev/cu.usbmodem101", baudrate=115200, timeout=1)

    with np.load('../train/mnist.npz') as f:
        x_train, y_train = f['x_train'], f['y_train']

    x_train = x_train/255
    y_train = keras.utils.to_categorical(y_train)

    data = np.arange(start=0, stop=100, step=1)
    port.write(data)

    time.sleep(1)

    print(port.read_all())

    port.close()
    

if __name__ == "__main__":
    main()