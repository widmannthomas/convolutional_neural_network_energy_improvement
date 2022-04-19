import sys
from ctypes import *
from dwfconstants import *
import time

class Tracing:
    def __init__(self) -> None:
        self.sts = c_byte()
        self.hzAcq = c_double(500000) # 500 kHz
        self.nSamples = 800000
        self.rgdSamples = (c_double * self.nSamples)()
        self.rgdSamples2 = (c_double * self.nSamples)()


    def setup(self):
        # (1) loading Waveforms SDK
        if sys.platform.startswith("win"):
            self.dwf = cdll.LoadLibrary("dwf.dll")
        elif sys.platform.startswith("darwin"):
            self.dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
        else:
            self.dwf = cdll.LoadLibrary("libdwf.so")

        #declare ctype variables
        self.hdwf = c_int()

        # (2) open device
        print("Opening first device")
        self.dwf.FDwfDeviceOpen(c_int(-1), byref(self.hdwf))

        if self.hdwf.value == 0:
            print("failed to open device")
            szerr = create_string_buffer(512)
            self.dwf.FDwfGetLastErrorMsg(szerr)
            print(szerr.value)
            quit()


    def prepare(self):
        buffer_size_min = c_int()
        buffer_size_max = c_int()
        self.dwf.FDwfAnalogInBufferSizeInfo(self.hdwf, byref(buffer_size_min), byref(buffer_size_max))
        print("Max buffer size:", buffer_size_max)

        # set buffer size:
        self.dwf.FDwfAnalogInBufferSizeSet(self.hdwf, buffer_size_max) 

        #set up trigger
        self.dwf.FDwfAnalogInTriggerAutoTimeoutSet(self.hdwf, c_double(0)) #disable auto trigger
        self.dwf.FDwfAnalogInTriggerSourceSet(self.hdwf, trigsrcDetectorAnalogIn) #one of the analog in channels
        self.dwf.FDwfAnalogInTriggerTypeSet(self.hdwf, trigtypeEdge)
        self.dwf.FDwfAnalogInTriggerChannelSet(self.hdwf, c_int(1)) # first channel
        self.dwf.FDwfAnalogInTriggerLevelSet(self.hdwf, c_double(1)) # 1V
        self.dwf.FDwfAnalogInTriggerConditionSet(self.hdwf, trigcondRisingPositive) 

        self.dwf.FDwfAnalogInChannelEnableSet(self.hdwf, c_int(0), c_bool(True))
        self.dwf.FDwfAnalogInChannelEnableSet(self.hdwf, c_int(1), c_bool(True))

        self.dwf.FDwfAnalogInChannelRangeSet(self.hdwf, c_int(0), c_double(0.05))
        self.dwf.FDwfAnalogInChannelRangeSet(self.hdwf, c_int(1), c_double(2))

        self.dwf.FDwfAnalogInAcquisitionModeSet(self.hdwf, acqmodeRecord)
        self.dwf.FDwfAnalogInFrequencySet(self.hdwf, self.hzAcq)
        self.dwf.FDwfAnalogInRecordLengthSet(self.hdwf, c_double(self.nSamples / self.hzAcq.value)) # -1 infinite record length
        
        #wait at least 2 seconds for the offset to stabilize
        #time.sleep(2)
        
        print("Starting oscilloscope")
        self.dwf.FDwfAnalogInConfigure(self.hdwf, c_int(0), c_int(1))
        


    def trace(self):
        print("Start trace...")
        cAvailable = c_int()
        cLost = c_int()
        cCorrupted = c_int()
        cSamples = 0
    
        while cSamples < self.nSamples:
            self.dwf.FDwfAnalogInStatus(self.hdwf, c_int(1), byref(self.sts))
            if cSamples == 0 and (self.sts == DwfStateConfig or self.sts == DwfStatePrefill or self.sts == DwfStateArmed):
                # Acquisition not yet started.
                continue
        
            # get the number of samples available, lost & corrupted
            self.dwf.FDwfAnalogInStatusRecord(self.hdwf, byref(cAvailable), byref(cLost), byref(cCorrupted))
        
            cSamples += cLost.value
        
            # skip reading samples if there aren't any
            if cAvailable.value==0:
                continue
        
            # cap the available samples if the buffer would overflow from what's really available
            if cSamples+cAvailable.value > self.nSamples :
                cAvailable = c_int(self.nSamples - cSamples)
        
            # Read channel 1's available samples into the buffer
            self.dwf.FDwfAnalogInStatusData(self.hdwf, c_int(0), byref(self.rgdSamples, sizeof(c_double)*cSamples), cAvailable) # get channel 1 data
            self.dwf.FDwfAnalogInStatusData(self.hdwf, c_int(1), byref(self.rgdSamples2, sizeof(c_double)*cSamples), cAvailable) # get channel 2 data
            cSamples += cAvailable.value
            #print("Read", cSamples)

        print("Tracing done")


    def close(self):
        self.dwf.FDwfAnalogIOEnableSet(self.hdwf, c_int(False))
        self.dwf.FDwfDeviceCloseAll()
        
