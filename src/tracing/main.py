from time import sleep
from Tracing import *
from Classify import *
import numpy
import threading
import pandas as pd
import argparse

import matplotlib as mpl
import matplotlib.pyplot as plt

classify = Classify()
tracing = Tracing()


def test_cycle(k, output):
    
    tracing.prepare()

    def start_tracing():
        tracing.trace()

    trace_thread = threading.Thread(target=start_tracing)
    trace_thread.start()

    image = classify.get_image_at_index(k)
    plt.imshow(image, cmap="gray")
    plt.show(block=False)
    plt.pause(2)

    classify.send_request_classify_image()
    image_data = classify.create_image_bytes(image)
    classify.send_image_to_classify(image_data)
    
    print("Wait for trace thread...")
    trace_thread.join()
    print("Trace thread done...")

    sample_time = 1 / tracing.hzAcq.value
    df = pd.DataFrame({'signal_V': np.array(tracing.rgdSamples), 
                       'trigger_V': np.array(tracing.rgdSamples2), 
                       'time_S': np.arange(start=0, stop=tracing.nSamples * sample_time, step=sample_time)})

    path = output + "/" + str(k) + ".csv"
    print("Write to csv file...")
    df.to_csv(path_or_buf=path, sep=',',columns=['time_S', 'signal_V', 'trigger_V'], index=None)

    plt.close()
    print("Cycle done...")
    return df


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--Output", help = "Output of trace files")
    parser.add_argument("-c", "--Cycles", help = "Number of cycles", default=30)
    parser.add_argument("-s", "--Start", help = "Index of start cycle", default=0)

    args = parser.parse_args()

    tracing.setup()
    classify.setup()
    classify.connect("/dev/cu.usbserial-010D5020")

    for i in range(int(args.Start), int(args.Cycles)):
        print("##### Cycle", i)
        test_cycle(i, args.Output)

    #plt.plot(numpy.fromiter(df.signal_V, dtype = numpy.float))
    #plt.plot(numpy.fromiter(df.trigger_V, dtype = numpy.float))
    #plt.show(block=True)
    tracing.close()

main()
print("END")