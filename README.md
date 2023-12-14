# Build

These instructions are for Debian 12 (bookworm).
On Debian 11 (bullseye), you need meson from backports.

```
$ sudo apt install build-essential cmake meson ninja-build nlohmann-json3-dev pkg-config libssl-dev libsdl2-dev
$ meson setup build
$ ninja -C build
```

# Prepare HA

In HA, click your username (bottom left), this takes you to `/profile`.
Scroll down and create a Long-Lived Access Token.
Don't forget to save it - I keep it in a file called `.secrets` that I can source with `. .secrets`

# Run

```
$ export HA_WS_URL=ws://homeassistant.local:8123/api/websocket
$ export HA_API_TOKEN=xxxx
$ # or run `. .secrets` if you put those lines in there
$ LD_LIBRARY_PATH=build/subprojects/curl-8.0.1/build/lib/.libs/ build/client-ftxui
```

Push q or ctrl-C to exit.

Besides `client-ftxui`, there is `client-cli` which has simpler line based output.

If it hangs, `killall -9` it and try to find out how you caused that :-)
