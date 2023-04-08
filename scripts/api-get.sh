#!/bin/sh
. ./.secrets
curl -s \
     -H "Authorization: Bearer ${HA_API_TOKEN}" \
     -H "Content-Type: application/json" ${HA_API_URL}api/$1