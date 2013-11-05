#!/bin/bash

sudo rmmod mychardrv
sudo make
sudo insmod ./mychardrv.ko
