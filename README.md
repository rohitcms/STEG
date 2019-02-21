# STEG

 Simple Toy Event Generator

## Running the code:

```
[tuos@gw345 STEG]$ root -l proSTEG.C 
root [0] 
Processing proSTEGvn.C...
0 events processed
20 events processed
40 events processed
60 events processed
80 events processed
writing tree
writing to file
closing file
THE END
root [1] .q
```

## Read the produced tree and make a histogram for the pT distribution of the produced particles

```
[tuos@gw346 STEG]$ root -l eventAnalysis.C 
root [0] 
Processing eventAnalysis.C...
Have run 0 of the total 100 events; 
Have run 20 of the total 100 events; 
Have run 40 of the total 100 events; 
Have run 60 of the total 100 events; 
Have run 80 of the total 100 events; 
Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1
root [1] .q
```



