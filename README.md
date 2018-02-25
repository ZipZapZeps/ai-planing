# AI Planing

This library has been build for demonstrating basic AI algorithms using C++.

The following ideas/requirements were guiding the implementation:
* Use of STL containers, when possible
* Minimization of external dependencies
* Separation of the algorithm from the domain using the StateSpace template parameter
* Minimization of memory allocations
* AStar: No explicit modelling of actions/state transitions
* AStar: Separation of the implementation of the openlist and the closedlist as some implementation may not have a closed list at all