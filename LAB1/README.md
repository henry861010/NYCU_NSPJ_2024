# NYCU NSPJ 2024 LAB1
## introduction
* lab spec: SL-NSPJ24 User-Level System Call Hook-100324-145521.pdf
* enviroment: ubuntu 20.04 x86
* in this lab, we firstly understand how to use zpoline to trace the system calls called by the program, then we need to modify the src/zpoline/apps/basics/main.c to let the /src/mystery can ouput with the colorful style instead of gray only
    * the src/zpoline in this repository is cloned directly from https://github.com/yasukata/zpoline, but the src/zpoline/apps/basics/main.c was modified for second part of the lab
    * /src/mystery is the executable file for ubuntu20.04 x86 provided by school
        * run ``` chmod -x "/mystery" ``` at the first ime
        * which use execve() to call "toilet -f smblock -F border xxxxxx", the target of the part 2 is to intercept execve() (utilize poline) and add additional tag "--gay" to the argument array (what you do)

## run
* prepare
```
    $ sudo apt install binutils-dev
    $ sudo apt install toilet
```
* build
```
    $ sudo apt install binutils-dev
    (/src/zpoline/)$ make -C apps/basic
    (/src/zpoline/)$ make
```
* setup
```
    (/src/zpoline/)$ sudo sh -c "echo 0 > /proc/sys/vm/mmap_min_addr"
```
* run
```
    (/src/zpoline/)$ LIBZPHOOK=./apps/basic/libzphook_basic.so LD_PRELOAD=./libzpoline.so ../mystery
```
