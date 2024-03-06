#!/bin/sh -x

# FIXME: this started as a copy of tmux.sh, and we should see if we can unify them

PWD=`pwd`
ROOT=`dirname $0`/..

docker pull ghcr.io/home-assistant/home-assistant:stable

cp -r ${ROOT}/scripts/docker/config ${ROOT}/scripts/docker/ha-config
( cd ${ROOT}/scripts/docker && docker-compose up -d )
( cd ${ROOT}/scripts/docker && ./register.sh )
