#!/usr/bin/env bash

pids=()

function start_services()
{
    slstatus &
    pids+=( $! )
    nm-applet &
    pids+=( $! )
    blueman-applet &
    pids+=( $! )
    pasystray &
    pids+=( $! )
    dunst &
    pids+=( $! )
    picom --backend=glx &
    pids+=( $! )
}

function stop_services()
{
    kill -9 "${pids[@]}"
    pids=()
}

# start dwm
mkdir -p ~/.cache/dwm
while true ; do
    echo "DWM START $(date)" >> ~/.cache/dwm/stderr
    start_services
    echo "pids" "${pids[@]}" >> ~/.cache/dwm/stderr
    # if dwm exits with 0 the loop continues,
    # otherwise break and exit
    dwm 2>> ~/.cache/dwm/stderr || break
    stop_services
done
