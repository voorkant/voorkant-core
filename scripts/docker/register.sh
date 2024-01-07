#!/bin/sh

# We need to compile our code for the ha-long-token
cd ../../
meson setup build
meson compile -C build


CHECK_COUNT=0
curl 'http://localhost:8123/'
while [ $? -ne 0 ]
do
    if [ $CHECK_COUNT -gt 10 ]; then
        echo "HA doesn't seem to be started after a while, giving up."
        exit 1
    fi

    echo 'HA still down...'
    sleep 1
    CHECK_COUNT=$((CHECK_COUNT+1))

    # Keep on the last line because of exit status check
    curl 'http://localhost:8123'
done


# Create voorkant user
curl 'http://localhost:8123/api/onboarding/users' -s -X POST  --data-raw '{"client_id":"http://localhost:8123/","name":"voorkant","username":"voorkant","password":"v00rk4nt","language":"en-GB"}' > auth_code.json
MSG=`jq -r '.message' auth_code.json`
if [ "${MSG}" != "User step already done" ]; then
    CODE=`jq -r '.auth_code' auth_code.json`
    curl 'http://localhost:8123/auth/token' -s -X POST -F "grant_type=authorization_code" -F "code=${CODE}" -F "client_id=http://localhost:8123/" > token.json
    TOKEN=`jq -r '.access_token' token.json`
    # To complete setup, you have to set some other stuff. For whatever reason (might be because demo mode) these requests are empty in our capture.
    curl 'http://localhost:8123/api/onboarding/core_config' -s -X POST -H "authorization: Bearer ${TOKEN}" > /dev/null
    curl 'http://localhost:8123/api/onboarding/analytics' -s -X POST -H "authorization: Bearer ${TOKEN}" > /dev/null
    curl 'http://localhost:8123/api/onboarding/integration'  -s -X POST -H "authorization: Bearer ${TOKEN}" -d '{"client_id":"http://localhost:8123/","redirect_uri":"http://localhost:8123/?auth_callback=1"}' > /dev/null
fi

rm auth_code.json
rm token.json

HA_WS_URL=ws://localhost:8123/api/websocket HA_API_TOKEN="${TOKEN}" LD_LIBRARY_PATH=build/subprojects/curl-8.5.0/build/lib/.libs/ build/client-cli ha-get-token 1>longtoken.txt

echo HA_WS_URL=ws://localhost:8123/api/websocket HA_API_TOKEN="`cat longtoken.txt`"
rm longtoken.txt