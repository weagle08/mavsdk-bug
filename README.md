# mavsdk-bug
Repro for reproducing bugs found in MAVSDK so that they can more easily be identified and corrected

## LINKED BUG
* [SEG FAULT when retrieving all params](https://github.com/mavlink/MAVSDK/issues/1917)

## PREREQUSITE
* requires a flight controller (produced against PX4 docker container)
* update line 12 in main.cpp to have the correct connection string for your flight controller

## TO BUILD
$ ./build.sh

## RUN
$ ./build/mavsdk-bug

## ENVIRONMENT
- Ubuntu 22.04
- gcc/g++ 11.2
- gdb 11.2 (there are issues with gdb 12.* on Ubuntu 22.04 at the moment)

## REPRODUCE IN DBG
```shell
$ gdb ./build/mavsdk-bug
> b 39
> run
> n # appears to execute correctly
> n # observe seg fault originating in mavsdk stack
```


