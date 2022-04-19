# Digilent Analog Discovery 1 Current tracing
This Python program can be used to automate the measurement of the energy consumption when classifying a sample of the FashionMNIST dataset on the Raspberry Pi Pico.

## Example
```bash
# Perform 30 measurements
python3 main.py -o <OUTPUT> -c 30 
```

## Help
```bash
usage: main.py [-h] [-o OUTPUT] [-c CYCLES] [-s START]

optional arguments:
  -h, --help            show this help message and exit
  -o OUTPUT, --Output OUTPUT
                        Output of trace files
  -c CYCLES, --Cycles CYCLES
                        Number of cycles
  -s START, --Start START
                        Index of start cycle
```