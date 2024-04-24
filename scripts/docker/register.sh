#!/bin/sh

CHECK_COUNT=0
curl -s 'http://0.0.0.0:8123/' 1>/dev/null
while [ $? -ne 0 ]
do
    if [ $CHECK_COUNT -gt 15 ]; then
        echo "HA doesn't seem to be started after a while, giving up."
        exit 1
    fi

    echo 'HA still down...'
    sleep 1
    CHECK_COUNT=$((CHECK_COUNT+1))

    # Keep on the last line because of exit status check
    curl -s 'http://0.0.0.0:8123' 1>/dev/null
done


# Create voorkant user
curl 'http://0.0.0.0:8123/api/onboarding/users' -s -X POST  --data-raw '{"client_id":"http://0.0.0.0:8123/","name":"voorkant","username":"voorkant","password":"v00rk4nt","language":"en-GB"}' > auth_code.json
MSG=`jq -r '.message' auth_code.json`
if [ "${MSG}" != "User step already done" ]; then
    CODE=`jq -r '.auth_code' auth_code.json`
    curl 'http://0.0.0.0:8123/auth/token' -s -X POST -F "grant_type=authorization_code" -F "code=${CODE}" -F "client_id=http://0.0.0.0:8123/" > token.json
    TOKEN=`jq -r '.access_token' token.json`
    # To complete setup, you have to set some other stuff. For whatever reason (might be because demo mode) these requests are empty in our capture.
    curl 'http://0.0.0.0:8123/api/onboarding/core_config' -s -X POST -H "authorization: Bearer ${TOKEN}" > /dev/null
    curl 'http://0.0.0.0:8123/api/onboarding/analytics' -s -X POST -H "authorization: Bearer ${TOKEN}" > /dev/null
    curl 'http://0.0.0.0:8123/api/onboarding/integration'  -s -X POST -H "authorization: Bearer ${TOKEN}" -d '{"client_id":"http://0.0.0.0:8123/","redirect_uri":"http://0.0.0.0:8123/?auth_callback=1"}' > /dev/null

    rm auth_code.json
    rm token.json


    CLI=""
    if [ -x "../../build/client-cli" ]
    then
        CLI="../../build/client-cli"
    fi
    if [ -x "../../builddir/client-cli" ]
    then
        CLI="../../builddir/client-cli"
    fi
    if [ -x ${CLI} ]
    then
        HA_WS_URL=ws://0.0.0.0:8123/api/websocket HA_API_TOKEN="${TOKEN}" ${CLI} ha-get-token 2>register.log 1>longtoken.txt
        echo "Providing long lived token"
        echo HA_WS_URL=ws://0.0.0.0:8123/api/websocket HA_API_TOKEN="`cat longtoken.txt`"
    else
        echo "WARNING - could not find build/client-cli. Providing SHORT lived token"
        echo HA_WS_URL=ws://0.0.0.0:8123/api/websocket HA_API_TOKEN="${TOKEN}"
    fi
else
    if [ -e "longtoken.txt" ]
    then
        echo "Registration in HA was already completed, but found old long lived token."
        echo HA_WS_URL=ws://0.0.0.0:8123/api/websocket HA_API_TOKEN="`cat longtoken.txt`"
    else
        echo "Registration in HA has already been completed, can't provide a token."
        echo HA_WS_URL=ws://0.0.0.0:8123/api/websocket
    fi
fi
