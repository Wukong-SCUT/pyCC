# pyCC
This library is a decomposition strategy library under the advanced Cooperation Coevolution （CC） framework, implemented in Python to supplement the lack of Python implementations for many strategies.

We categorize some important problem decomposition strategies under the CC framework into three distinct groups：Static Grouping, Strategies Based On Probabilistic And Statistical, and Strategies Based On Variable Interactions.

# Static Decomposition
Static decomposition involves a one-time random decomposition, with each subgroup independently optimized and then combined to form the final optimization result.

| Strategy     | Paper Link | Year | Description |
| ----------- | ----------- |---------|----------|
| CCGA      | A Cooperative Coevolutionary Approach to Function Optimization|  1994 | The first decomposition strategy|
| CPSO  |A Cooperative Approach to Particle Swarm Optimization         | 2004 | $𝑘-𝑠$ dimensional decomposition|
| CCDE  |Cooperative Co-evolutionary Differential Evolution for Function Optimization             | 2005 | Bipartite decomposition|


# Strategies Based On Probabilistic And Statistical
Strategies based on probabilistic and statistical aiming mitigate the issues inherent in static decomposition by capturing problem structure and variable interactions, with multiple rounds of decomposition before forming the final optimization result.

## Random Decomposition (RD)
| Strategy     | Paper Link | Year | Description |
| ----------- | ----------- |---------|----------|
| FEPCC | Scaling up fast evolutionary programming with cooperative coevolution | 2001 | |
| DECC-G | Large scale evolutionary optimization using cooperative coevolution |   2008         |Introduce the random decomposition scheme |
| MLCC |Cooperative Co-evolution for Large Scale Optimization Through More frequent Random Grouping        |   2010   |Self-adaptation of the subcomponent sizes|


# Strategie Based On Variable Interactions
