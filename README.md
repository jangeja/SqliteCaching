# Extending Sqlite with a custom caching algorithm

The team wants to  add a caching feature to SQLite if one is not present. If a
caching algorithm exists, the team aims to modify the caching algorithm to
improve performance.

## Prerequisites

What things you need to install the software and how to install them. Must be
run on a linux machine

1. ```apt-get install cmake```

2. ```apt-get install tcl```

## Getting Started


### Compiling
* [SQLiteCompile](https://www.sqlite.org/howtocompile.html) - Compilation
instructions

1. ```cd Development/sqliteSrc```
2. Execute this command within the directory that contains the source code. The
  ```-DALGORITHM_EVICTION``` flag is used to specify the eviction algorithm to
  be used
```gcc -Os -I. -DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_FTS4 \
   -DSQLITE_ENABLE_FTS5 -DSQLITE_ENABLE_JSON1 \
   -DSQLITE_ENABLE_RTREE -DSQLITE_ENABLE_EXPLAIN_COMMENTS \
   -DHAVE_USLEEP -DHAVE_READLINE \
   shell.c sqlite3.c -ldl -lreadline -lncurses -c -o sqlite3.o -DALGORITHM_EVICTION
```
    1. ```-DQUEUE_EVICTION``` This is the standard sqlite3 eviction algorithm,
      FIFO.
    2. ```-DSTACK_EVICTION``` LIFO
    3. ```-DSECOND_CHANCE_EVICTION```
    4. ```-DCLOCK_EVICTION```
    5. ```-DWILD_WEST_EVICTION```
3. ```cp sqlite3.o ../test/sqlite3.o```
4. ```cd ../test```
5. ```cmake .```
6. ```cd build```
7. ```make```

### Initializing databases
1. ```cd Development/test/build```
2. ```./config```
    This ussually takes about 10-20 minutes to create all the tuples

### Running Tests
1. ```cd Development/test/build```
2. ```./speedTest```
    Results will begin to be printed to the screen

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
