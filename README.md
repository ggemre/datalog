# Datalog
An interpreter for the Datalog language.

## What is this?

> Datalog is a [declarative](https://en.wikipedia.org/wiki/Declarative_programming) [logic programming](https://en.wikipedia.org/wiki/Logic_programming) language. While it is syntactically a subset of [Prolog](https://en.wikipedia.org/wiki/Prolog), Datalog generally uses a bottom-up rather than top-down evaluation model. This difference yields significantly different behavior and properties from [Prolog](https://en.wikipedia.org/wiki/Prolog). It is often used as a query language for deductive databases. Datalog has been applied to problems in data integration, networking, program analysis, and more.
> 
> \- [Wikipedia - Datalog](https://en.wikipedia.org/wiki/Datalog)

## Usage
To compile the program you can use `g++` like so:

```sh
$ g++ -Wall -Werror -std=c++17 -g src/*.cpp -o datalog
```

Then, simply run the compiled executable with a datalog file passed in as a cli argument:

```sh
$ ./datalog hello.d
```

You can optionally use the scripts as provided:

```sh
$ scripts/run.sh hello.d
  Hello, world
$ scripts/test.sh
  Running unit tests
  ...
```
