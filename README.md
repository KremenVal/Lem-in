# Lem-in
Lem-in - flow network simulator, graph theory.

Lem-in is a project where ants are guided through an anthill from a start to finish node. Each anthill is a graph of nodes and tunnels. The goal is to find the combination of paths that result in the least number of turns, while maintaining a max flow rate of one ant per node per turn.

# Installation:

git clone https://github.com/KremenVal/Filler.git

make

Usage:

./lem-in -help

To create map, use generator.dms. How to use it:

./generator --help

or for example

./generator --flow-ten > ten

Than use this map with ./lem-in

./lem-in < ten
