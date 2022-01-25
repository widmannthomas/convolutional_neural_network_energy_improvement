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



## 2021-12-30

- Theoretischer Hintergrund:
   Literaturrecherche 
   Was ist pruning (structured / unstructured) Pruning methoden. 
   Was ist quantisierung 8bit quantisierung, float16, ... methoden allgemein. Warum wird quantisierung gemahct?
   - Viel Zeit nehmen!
   - Disposition kann in der Arbeit übernommen werden.
- Wissenschaftliche Herangehensweise
   - Prinzipiell wird meine Arbeit ein Experiment durchführen.
      - Muss ich hier schon die abhängigen / unabhängigen Variablen definieren?
        - Abhängig: Energieverbrauch
        - Const: uC
        - Unabhängig: Begründen warum ich welche Werte ändere.
            - z.B. Pruning methonde: Warum verwende ich z.B. Filter pruning verwende
      - Muss ich die Durchführung des Experiments schon beschreiben?
    - Auswertung gedanken machen
        - Welche größen werden gemessen.
- Zeitplan
   - Wie detailliert muss der Plan sein?
       - Reichen Meilensteine aus?
