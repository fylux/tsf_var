GenTS is a generator of random multivarible time series data. It aims to be a tool for testing machine learning algorithm without needing real datasets.

## Options

 + **-var** N Number of variables to predict

 + **-dep** N Number of time instants that predictable variables depend on

 + **-instances** N Number of time instants to be generated

 + [**-ivar** N] Number of independent variables

 + [**-idep** N] Number of time instants that independent variables depend on

 + [**-noise** 0..1] Percentage of noise to be added


## File format
Using the following symbolism:

 + **-var** d

 + **-dep** i

 + **-ivar** k

 + **-idep** e

 + **-instances** n 

The first 5 lines correspond to the variables:
*d*, *i*, *k*, *e*, *n*

Then *n* rows (one per time instante) with *d* floats which represent  predictable vars and *k* floats which represent independent variables. 

Finally *d*+*e*+*i* rows with *d* floats that represent the matrix X used to generate the data.

## How to use

./gen -var N -dep N -instances N [-ivar N -idep N] [-noise R]

