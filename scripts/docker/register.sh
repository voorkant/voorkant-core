#!/bin/sh

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
    curl 'http://localhost:8123/api/onboarding/integration'  -X POST -H "authorization: Bearer ${TOKEN}"
fi

# rm auth_code.json
# rm token.json