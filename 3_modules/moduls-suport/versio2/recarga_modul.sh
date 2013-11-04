#!/bin/bash

sudo rmmod mychardrv
make
sudo insmod ./mychardrv.ko
