#!/bin/bash

set -xe

make -s

gnome-terminal --geometry=40x20+0+0 -- bash -c "timeout 100 ./philo 5 800 200 200 | tee /dev/tty"
gnome-terminal --geometry=40x20+360+0 -- bash -c "timeout 100 ./philo 5 800 200 200 7 | tee /dev/tty | grep eating | wc -l && sleep 2"timeout 100 
gnome-terminal --geometry=40x20+720+0 -- bash -c "timeout 100 ./philo 4 410 200 200 | tee /dev/tty"timeout 100 
gnome-terminal --geometry=40x20+1080+0 -- bash -c "timeout 100 ./philo 4 310 200 100 | tee /dev/tty && sleep 2"timeout 100 
gnome-terminal --geometry=40x20+1420+0 -- bash -c "timeout 100 ./philo 200 120 60 60 | tee /dev/tty"timeout 100 

gnome-terminal --geometry=40x20+0+600 -- bash -c "timeout 100 valgrind --tool=helgrind ./philo 5 800 200 200 | tee /dev/tty"timeout 100 
gnome-terminal --geometry=40x20+360+600 -- bash -c "timeout 100 valgrind --tool=helgrind ./philo 5 800 200 200 7 | tee /dev/tty | grep eating | wc -l && sleep 2"timeout 100 
gnome-terminal --geometry=40x20+720+600 -- bash -c "timeout 100 valgrind --tool=helgrind ./philo 4 410 200 200 | tee /dev/tty"timeout 100 
gnome-terminal --geometry=40x20+1080+600 -- bash -c "timeout 100 valgrind --tool=helgrind ./philo 4 310 200 100 | tee /dev/tty && sleep 2"timeout 100 
gnome-terminal --geometry=40x20+1420+600 -- bash -c "timeout 100 valgrind --tool=helgrind ./philo 200 120 60 60 | tee /dev/tty"timeout 100 
