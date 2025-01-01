#!/usr/bin/env bash

# export GTK_THEME=Adwaita:dark
# export QT_STYLE_OVERRIDE=Adwaita-Dark
# export GTK_RC_FILES=/usr/share/themes/Adwaita-dark/gtk-2.0/gtkrc

# set background color
# gruvbox
# xsetroot -solid "#282828"
# kanagawa solid color
# xsetroot -solid "#1f1f28"

pids=()

function start_services()
{
    slstatus &
    pids+=( $! )
    # replaced with networkmanager_dmenu
    # nm-applet &
    # pids+=( $! )
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
