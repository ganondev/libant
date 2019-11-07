# libant (in beta)

![AWS CodeBuild](https://codebuild.us-east-1.amazonaws.com/badges?uuid=eyJlbmNyeXB0ZWREYXRhIjoiaHhyU3BJNmZ0NEE1MkFlQUJ4VFVRWXlLWVh1aURZYWxZR2IvNXJVaFlLaTJwb3p1blZheEk2TERKK002RE93Vk0xdEJOQjRjbGQwY2tWOStNNmxQc0QwPSIsIml2UGFyYW1ldGVyU3BlYyI6Ijl0N3hJWFEweWdOY1JnL2giLCJtYXRlcmlhbFNldFNlcmlhbCI6MX0%3D&branch=master)

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
* Conceptually simple modifications to an existing automata may be very difficult to express
* _And much more!_

