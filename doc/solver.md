SolverTS finds the most suitable matrix for the data. The data format is the one produced from GenTS.

## Options

 + [**-training** 0..1] Percentage of data to be used for training (1 by default).

## Build Options
The macro EXAHUSTIVE can be used to check all the possible combinations of variables as dependent and independent ignoring the configuration proposed by the data file. See MAKEFILE.

## How to use

./test [-training R] < dataFile
