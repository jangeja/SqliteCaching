# Extending Sqlite with a custom caching algorithm

The team wants to  add a caching feature to SQLite if one is not present. If a
caching algorithm exists, the team aims to modify the caching algorithm to
improve performance.

## Development

These instructions are for developers only.

### Development Directory

This directory should be where you make modifications to the source code. The
OriginalSqlite directory should be untouched. We will run our modifications
against benchmarks and use the original source code as our baseline of
performance.

### Compiling

* [SQLiteCompile](https://www.sqlite.org/howtocompile.html) - Compilation
instructions


Execute this command within the directory that contains the source code
```
gcc -Os -I. -DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_FTS4 \
   -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 \
   -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_EXPLAIN_COMMENTS \
   -DHAVE_USLEEP -DHAVE_READLINE \
   shell.c sqlite3.c -ldl -lreadline -lncurses -o sqlite3
```




## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [SQLite](https://www.sqlite.org) - Open source DBMS used

## Authors

* **Joey Angeja** - *Initial work* - [jangeja94](https://github.com/jangeja94)
* **Andrew Kim** - *Initial work* - [jangeja94](https://github.com/jangeja94)
* **Jonathan Tan** - *Initial work* - [jonatan1626](https://github.com/jonatan1626)
* **Pierson Yieh** - *Initial work* - [jangeja94](https://github.com/jangeja94)

See also the list of [contributors](https://github.com/jangeja94/SqliteCaching/contributors) who participated in this project.

## Acknowledgments

* Professor Stanchev
* Cal Poly
* Friends and Family
