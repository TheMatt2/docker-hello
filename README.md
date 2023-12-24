# Hello Docker

Simple test at using the `scratch` docker image for creating very minimalists programs.

## Build

```
docker build -t hello .
```

## Run

```
docker run -it --rm hello /bin/hello_c tree /bin
```

## Minimal Image Contents

Using the tools in `hello.c`, this is the only files present on this minimalisitic image.

```
/
├── etc
│   ├── resolv.conf
│   ├── hostname
│   ├── mtab
│   └── hosts
├── dev
│   ├── console
│   ├── core
│   ├── stderr
│   ├── stdout
│   ├── stdin
│   ├── fd
│   ├── ptmx
│   ├── urandom
│   ├── zero
│   ├── tty
│   ├── full
│   ├── random
│   ├── null
│   ├── shm
│   ├── mqueue
│   └── pts
├── .dockerenv
├── proc
│   ├── 1
│   ├── acpi
│   ├── buddyinfo
│   ├── bus
│   ├── cgroups
│   ├── cmdline
│   ├── config.gz
│   ├── consoles
│   ├── cpuinfo
│   ├── crypto
│   ├── devices
│   ├── diskstats
│   ├── dma
│   ├── docker
│   ├── driver
│   ├── execdomains
│   ├── fb
│   ├── filesystems
│   ├── fs
│   ├── interrupts
│   ├── iomem
│   ├── ioports
│   ├── irq
│   ├── kallsyms
│   ├── kcore
│   ├── key-users
│   ├── keys
│   ├── kmsg
│   ├── kpagecgroup
│   ├── kpagecount
│   ├── kpageflags
│   ├── loadavg
│   ├── locks
│   ├── meminfo
│   ├── misc
│   ├── modules
│   ├── mounts
│   ├── mpt
│   ├── mtrr
│   ├── net
│   ├── pagetypeinfo
│   ├── partitions
│   ├── self
│   ├── softirqs
│   ├── stat
│   ├── swaps
│   ├── sys
│   ├── sysrq-trigger
│   ├── sysvipc
│   ├── thread-self
│   ├── timer_list
│   ├── tty
│   ├── uptime
│   ├── version
│   ├── vmallocinfo
│   ├── vmstat
│   └── zoneinfo
└── sys
    ├── block
    ├── bus
    ├── class
    ├── dev
    ├── devices
    ├── firmware
    ├── fs
    ├── kernel
    ├── module
    └── power
```
