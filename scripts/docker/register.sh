#!/bin/sh

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
curl 'http://localhost:8123/api/onboarding/users' -X POST  --data-raw '{"client_id":"http://localhost:8123/","name":"voorkant","username":"voorkant","password":"v00rk4nt","language":"en-GB"}' > auth_code.json
MSG=`jq -r '.message' auth_code.json`
if [ "${MSG}" != "User step already done" ]; then
    CODE=`jq -r '.auth_code' auth_code.json`
    curl 'http://localhost:8123/auth/token' -X POST --trace trace.txt -F "grant_type=authorization_code" -F "code=${CODE}" -F "client_id=http://localhost:8123/" > token.json
    TOKEN=`jq -r '.access_token' token.json`

    # To complete setup, you have to set some other stuff. For whatever reason (might be because demo mode) these requests are empty in our capture.
    curl 'http://localhost:8123/api/onboarding/core_config' -X POST -H "authorization: Bearer ${TOKEN}"
    curl 'http://localhost:8123/api/onboarding/analytics' -X POST -H "authorization: Bearer ${TOKEN}"
    curl 'http://localhost:8123/api/onboarding/integration'  -X POST -H "authorization: Bearer ${TOKEN}" -d '{"client_id":"http://localhost:8123/","redirect_uri":"http://localhost:8123/?auth_callback=1"}'
fi

# rm auth_code.json
# rm token.json