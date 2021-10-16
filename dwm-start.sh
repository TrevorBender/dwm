#!/bin/sh

# status line
slstatus &

# set background color
xsetroot -solid "#282828"

nm-applet &
blueman-applet &
pasystray &
dunst &

# start dwm
mkdir -p ~/.cache/dwm
while true ; do
    MSG="DWM START $(date)"
    echo "$MSG" >> ~/.cache/dwm/stderr
    # if dwm exits with 0 the loop continues,
    # otherwise break and exit
    dwm 2>> ~/.cache/dwm/stderr || break
done
