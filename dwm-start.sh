#!/bin/sh

# status line
slstatus &
STATUS_PID=$?

# set background color
xsetroot -solid "#fdf6e3"

# start dwm
mkdir -p ~/.cache/dwm
while true ; do
    MSG="DWM START $(date)"
    echo "$MSG" >> ~/.cache/dwm/stdout
    echo "$MSG" >> ~/.cache/dwm/stderr
    # if dwm exits with 0 the loop continues,
    # otherwise break and exit
    dwm >> ~/.cache/dwm/stdout 2>> ~/.cache/dwm/stderr || break
done

kill -9 ${STATUS_PID}
