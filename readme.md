## Introduction
This project aims to offer the tools required to analyze and forecast time series using [VAR models](https://en.wikipedia.org/wiki/Vector_autoregression).

To generate synthetic data see GenTS.

To find the best model for a given data see SolverTS.

## Dependencies
Make sure you have installed the dependencies:
 - g++ 4.7 or later
 - GNU make 3.81 or later
 - Intel MKL 2017 or later

## How to use
GenTS: `./gen -var N -dep N -instances N [-ivar N -idep N] [-noise R]`

SolverTS: `./test [-training R] < dataFile`


## Authors
This repository contains the source code of GenTS and SolverTS. Both projects are at early stages and under active development. The developer of the project is [Alfonso L. Castaño](https://fylux.github.io/about/), advised by [D. Giménez](http://dis.um.es/~domingo/) et al. as part of the project *Desarrollo y estudio de algoritmos para la busqueda del mejor modelo econometrico en problemas de ciencias de la salud*.
