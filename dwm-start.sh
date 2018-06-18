#!/bin/sh

MEM_TOTAL=$(free -m | grep Mem: | awk '{print $2}')

function mem_free ()
{
    local mem_available_kb=$(awk '/MemAvailable/ {print $2}' /proc/meminfo)
    local mem_available_mb=$(echo "$mem_available_kb / 1000" | bc)
    #local mem_free=$(free -m | grep Mem: | awk '{print $4}')
    echo "$mem_available_mb/${MEM_TOTAL}MB"
}

function power ()
{
    local dir=/sys/class/power_supply/BAT0
    local capacity=$(cat $dir/capacity)
    local status=$(cat $dir/status)
    echo "[$capacity $status]"
}

function sound ()
{
    local vol=$(amixer get PCM | awk '/Front Left:/ {print $5}')
    local mute=$(amixer get Master | awk '/Mono:/ {print $6}')
    echo "$vol$mute"
}

function show_status ()
{
    local uptime_string=$(uptime | sed  's/.*://; s/,//g')
    local date_string=$(date +"%a %b %d %R")
    local mem_info=$(mem_free)
    local power_info=$(power)
    local sound_info=$(sound)
    #local notification=$(shownot)
    hsetroot -name "$sound_info $power_info [$mem_info$uptime_string] [$date_string]";
}

# status line
#while true ; do
    #mpc -q idle player > /dev/null
    #show_status
#done &
#MPD_STATUS_PID=$?

while true ; do
    show_status
    sleep 5;
done &
STATUS_PID=$?

xsetroot -solid "#fdf6e3"
#feh --bg-scale /opt/backup/storage/backup/desktop\ pics/nature.jpg

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
#kill -9 ${MPD_STATUS_PID}
