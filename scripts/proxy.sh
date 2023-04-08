#!/bin/sh
. ./.secrets
mosquitto_sub -h $MQTT_HOST -t '#' -u $MQTT_USER -P $MQTT_PASSWORD | mosquitto_pub -h 127.0.0.1 -t /foo -l

