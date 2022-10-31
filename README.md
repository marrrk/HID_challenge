# Challenge Solution for Firmware Engineer Role

Instructions for building:

1. `make`
2. `make run` 

The challenge was focused on efficiently storing and parsing through a database to find the minimum distance between a sample set of co-ordinates and those found in the database. The key metric that was being aimed to be improved was in the speed of the program and as such, the following optimizations were implemented:

1. Using `float` instead of `double` for all data to minimize size and therefore computational capacity.
2. While loading the sample data, a `switch` statement was implemented as there are only two possible conditions, and thus the utlisation of a jump table by the compiler achieved greater speed.
3. While loading the database data, a little more care needed to be taken. The database contains 11 columns and as such using a `switch` would possibly be compiled into a comparison tree and thus slowing down CPU speed. However, due to the repeatability of the columns, it was possible to determine if the column was an x value or a y value depending on the column number, and therefore reducing the computation to one `if` statement per column. Additionally, the column number was also used to determine the minutia number. This solution is also implemented with the idea of being extensible to a larger database with more minutiae per ID.
4. To reduce the search time, concurrency was implemented in order to have each sample have its match searched at the same time as all the others. This produced a speed up of search time of ~8.75x

The algorithm for matching minutiae was built around the formula: 

<img src="https://latex.codecogs.com/svg.latex?\Large&space;Distance=\sqrt{(x-x_1)^2+(y-y_1)^2}" title="\Large Distance=\sqrt{(x-x_1)^2+(y-y_1)^2}" />

Each minutia in the database needed to be checked in order to determine the minimum distance and so a linear search algorithm was implemented. For each sample minutia, the distance to every minutia of every ID in the database was calculated, and if the distance was found to be less than the current minimum distance, the output was updated. Once every minutia is calculated, and every sample is matched the program prints the result.
