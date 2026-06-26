# Fibonacci Generator

This repository contains three implementations that calculate an arbitrary number of Fibonacci numbers.
The focus lies on the generator implementation of the sequence.

## Build instructions

First, you need to install the GMP library: follow [these](https://gmplib.org/gmp-man-6.3.0.pdf#Installing%20GMP) instructions.

Next, install the main application:

```
make
```

## Usage

```
Usage: ./main <number> (--generator | --trivial | --array) [--runtime]
```
With number you can set the index, up to which the Fibonacci sequence shall be calculated.
With either the --generator, --array or --trivial flags you decide, which implementation you want to use.
When setting the runtime flag, the numbers don't get printed and the runtime performance of the implementation will be measured.

## Memory performance

To measure the memory performance, we use the valgrind tool massif:

```
valgrind --tool=massif --massif-out-file=./massif.out ./main <number> (--generator | --trivial | --array) [--runtime]
ms_print ./massif.out
```

The heap usage at specific timepoints of the execution are displayed afterwards.
