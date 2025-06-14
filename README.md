# gethostname

[![C/C++ CI](https://github.com/elulcao/gethostname/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/elulcao/gethostname/actions/workflows/c-cpp.yml)

gethostname is a package to mock the gethostname() Sys call with a custom host name The gethostname() Sys call is intercepted via LD_PRELOAD before other libs are loaded.

The main intention of this change is to allow Host Names with "_" characters.

## Installation

Execute the yum or dnf command and verify `/usr/lib64/libgethostname.so.1` has been added to the container path:

```bash
dnf install -y gethostname
```

## Usage

Define NEWHOSTNAME and LD_PRELOAD to spoof the container Host Name inside a container.

```bash
$ export NEWHOSTNAME=my_host_name
$ export LD_PRELOAD=/usr/lib64/libgethostname.so.1
$ hostname
my_host_name
```

## Test

Makefile can be used to verify the result for modifying the hostname.

```bash
$ make build
gcc -fPIC -rdynamic -g -Wall -shared -Wl,-soname,libgethostname.so.1 -lc -ldl -o libgethostname.so.1 gethostname.c

$ make test
LD_PRELOAD=~/GitLab/cicd/gethostname/libgethostname.so.1 NEWHOSTNAME=my_host_name hostname
my_host_name
```