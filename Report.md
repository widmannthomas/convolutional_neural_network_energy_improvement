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


## 2022-01-27

- removed gif and bitmap from dataset because these formats don't work in grayscale mode.

## 2022-01-30

- fixed https://github.com/BenWhetton/keras-surgeon/pull/62







## 2022-01-31

**Introduction:**
- [ ] Warum hilft pruning bei batteriebetriebenen Applikationen? Besser beschreiben, dass die aktive CPU Zeit verkleinert werden kann.

**Research Questions:**
- [x] Hypothesis aufstellen (Unstructured pruning wird keine Verbesserung erwartet.) Begründung - spezial HW wird benötigt.

**Network**
- [x] Keine Quantisierung durchführen.
- [x] LeNet mit fashion mnist structured / unstructured pruning.
- [x] Kleinerer Datensatz MNIST oder Fashion MNIST
- [x] Modell: LeNet

**Referenzen:**
- [x] Vollständigkeit Überprüfen (5 ist nicht vollständig)

**MISC**
- [ ] Zitierregeln (Zitat immer vor dem Satzzeichen)

### Info
- Fashion mnist without quantization works. LeNet does fit!


## 2022-02-02
- Lenet5 passt auf den controller
- structured pruning geht bei cnn und dense
- apoz geht bei cnn und dense









## 2022-04-01
### Open Questions:
- Welche Zeitform ist zu verwenden?
- Wie soll unstructured_pruning (speedup) eingebunden werden?
    - Discussion?
    - third Experiment ?


## 2022-04-06 Briefing

- Cite figures: Quelle angeben. Siehe Folien
- Forschungsfrage: Wie wirkt sich bla bla aus. Nicht: Hat bla bla einen Einfluss?    Darf nicht mit Ja/Nein beantwortet werden dürfen.