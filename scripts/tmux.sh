#!/bin/sh -x

PWD=`pwd`
ROOT=`dirname $0`/..


SESSIONNAME="VOORKANT"
tmux has-session -t $SESSIONNAME

if [ $? != 0 ] 
then
    tmux new-session -s $SESSIONNAME -n HA -d
    tmux send-keys -t $SESSIONNAME "cd ${ROOT}/scripts/docker && docker-compose up" C-m
    tmux new-window -t $SESSIONNAME -n REGISTER 
    tmux send-keys -t $SESSIONNAME "cd ${ROOT}/scripts/docker && ./register.sh" C-m
fi

tmux attach -t $SESSIONNAME
