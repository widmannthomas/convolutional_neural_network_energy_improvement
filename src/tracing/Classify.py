import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow import keras
import serial
import serial.tools.list_ports
import json
import time
import struct
import io

batch_size = 32
img_height = 28
img_width = 28
img_channel = 1
number_of_classes = 10

class Classify:
    def __init__(self) -> None:
        pass


    def setup(self):
        self.load_data_result = tf.keras.datasets.fashion_mnist.load_data()
        self.class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']
        self.fashion_mnist = tf.keras.datasets.fashion_mnist
        (train_images, train_labels), (test_images, test_labels) = self.fashion_mnist.load_data()

        # reshape dataset to have a single channel
        self.train_images = train_images.reshape((train_images.shape[0], 28, 28, 1))
        self.test_images = test_images.reshape((test_images.shape[0], 28, 28, 1))

        self.train_labels = keras.utils.to_categorical(train_labels)
        self.test_labels = keras.utils.to_categorical(test_labels)
        print(self.train_labels[0])


    def connect(self, port_path, baudrate=115200, timeout=2):
        print("Connect to:", port_path)
        self.port = serial.Serial(port_path, baudrate=baudrate, timeout=timeout)
        self.port.read_all()


    def convert_float_list_to_bytes(self, data):
        data_bytes = []
        for dat in data:
            bytes_ = list(struct.pack("!f", dat))
            bytes_.reverse()
            data_bytes.extend(bytes_)

        return data_bytes


    def get_image_at_index(self, k):
        return np.float32(self.train_images[k])

    def create_image_bytes(self, image):
        image = image.reshape(28*28,)
        print(np.shape(image))
        image_bytes = self.convert_float_list_to_bytes(image)
        print(len(image_bytes))
        return image_bytes


    def send_request_classify_image(self):
        img_size = img_width * img_height * img_channel * 4
        command = {"command":0, "ds":img_size, "repeat": 1}
        command_json = json.dumps(command)
        print(command_json)

        command_json += "\n"
        self.port.write(command_json.encode())
        time.sleep(0.1)
        print(self.port.read_all())


    def send_image_to_classify(self, image_bytes):
        self.port.write(image_bytes)
        time.sleep(2)

        timing_samples = []

        while(True):
            lineData = self.port.readline()
            line = str(lineData)

            if len(lineData) == 0:
                break

            lineJsonData = io.BytesIO(lineData)
            lineJson = json.load(lineJsonData)
            print(lineJson)

            if lineJson["type"] == 1:
                data = lineJson["payload"]["data"]
                for sample in data:
                    timing_samples.append(sample["time_us"])
                    print("Time:", sample["time_us"] / 1000, "ms")

                
                #print(lineJson)

        timing_samples = np.array(timing_samples)
        return timing_samples

