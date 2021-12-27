# Report

## 2021-12-27
- Test environment is running on the MCU
    - send commands to controller
    - send image data to controller
    - mnist is working
- Tried different quantization and pruning optimizations
- Low magnitude pruning without surgery brings not the expected improvement.
    - My thought was that a matrix multiplication with a lot of 0's takes less time than a multiplication with a matrix without 0's.
        - I made some tests on an Atmel Atmega16 and ESP8266 controller before. => I saw an improvement.
        - Maybe the compile O0 is used?
- Found a very nice library that provides network surgery functionality.
    - Tried it => works well with a small bugfix for TF 2.4
    - ```kerassurgeon```

### ToDo
- [ ] Check compiler optimization level
- [ ] Try to run _kerassurgeon-pruned_ model on the MCU
- [ ] Further read some papers about _apoz_ and _L1-Norm_