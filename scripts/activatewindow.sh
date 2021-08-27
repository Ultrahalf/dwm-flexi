#!/bin/sh
# dmenu script to jump between tags

wmctrl -l -x | awk -F " " '{print $1, $3}' > /tmp/windowlist
selwin="$(cat /tmp/windowlist | cut -d '.' -f 2 | dmenu -p 'Window list' -l 5 -c)" || exit 1
winid="$(cat /tmp/windowlist | grep $selwin | cut -d ' ' -f 1)"
wmctrl -i -a $winid
