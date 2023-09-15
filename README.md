# libant 2

(Project is not abandoned. I am focused on graduating.)

## Cellular Automata from an actor's perspective

Libant makes it easier to prototype, discover, and experiment with different kinds of cellular automata that would otherwise be difficult or tedious to express in the classical way.

### The classic way
The typical way to express any CA is to:
1. Allocate space for your world
2. Scan over every discrete location in that world
3. Based on the state of the world at one or more locations, update the some other location in the world 

There are a number of issues with this approach:
* Depending on the available technology, one may be limited to a bounded world without considerable effort
* This method is conducive to a high spatial complexity
* A lot of boilerplate is involved
* Conceptually simple alterations to an existing automaton may be very difficult to express
* _And much more!_

### The libant way
Libant is built around the core concept of specialized actions which we call Ants.
1. Create one or many `Ant` instances and assing them their `directive`. The `Ant` has it's own state, separate from the world, which can be used in union with the world state to cleanly express how the `Ant` should modify the world.
2. Create a `Grid`. This is your world. Add any number of `Ant` actors to the grid.
3. `Tick` the `Grid`. This will iterate over each `Ant` tracked by `Grid` and perform it's directive. A `Tick` is by default a syncronous atomic operation, allowing the dependent application to update and analyze the world state at it's own pace.
4. After the `Tick` is finished, common information about the immediate and cumulative state of the world is readily available for analysis or presentation.

Wonderful because:
* Generalized built-in data structures optimized for discrete spatial information make it easy to track state in an unbounded world
* The actor focus encourages processing only on the important state information
* A minimal amount of boilerplate is involved
* Tracking the state of the `Ant` separately from the world makes simple rule modifications very simple
* The library is cheaper than a Mathematica license (free as in beer)

## Support Libant
I'll use this money to buy expensive coffee and gifts for my wife. This may indirectly improve code quality.

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/eddyja)
