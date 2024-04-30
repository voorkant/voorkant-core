# Build

These instructions are for Debian 12 (bookworm).
On Debian 11 (bullseye), you need meson from backports.

```
$ sudo apt install build-essential cmake meson ninja-build nlohmann-json3-dev pkg-config libssl-dev libsdl2-dev
$ git submodule update --init
$ meson setup build/
$ meson compile -C build/
```

# Dev environment

In the `scripts/` directory, there's a `tmux.sh` file that can be used to start up a HA docker container and complete the registration steps.
It then spits out the HA_WS_URL and HA_API_TOKEN.
If `client-cli` already exists, then it will spit out a Long-Lived token and you do not need to create it manually.


# Prepare HA

If you did not get a Long-Lived token from `tmux.sh`, then in HA, click your username (bottom left), this takes you to `/profile`.
Scroll down and create a Long-Lived Access Token.

Don't forget to save it - I keep it in a file called `.secrets` that I can source with `. .secrets`

# Run

```
$ export HA_WS_URL=ws://homeassistant.local:8123/api/websocket
$ export HA_API_TOKEN=xxxx
$ # or run `. .secrets` if you put those lines in there
$ build/client-ftxui
```

Push q or ctrl-C to exit.

Besides `client-ftxui`, there is `client-cli` which has simpler line based output.
`client-lvgl` is the nice UI.

If it hangs, `killall -9` it and try to find out how you caused that :-)

# Dependency map

| Dependency    | License        | Import method    |
|---------------|----------------|------------------|
| argparse      | MIT            | git submodule    |
| FTXUI         | MIT            | meson wrap       |
| libcurl       | MIT-like       | meson wrap       |
| LVGL          | MIT            | git submodule    |
| magic_enum    | MIT            | git submodule    |
| nlohmann/json | MIT            | header assumed present on system (perhaps it should be a meson wrap instead)
| openssl       | Apache (in v3) | assumed present on system |
| SDL2          | zlib           | assumed present on system |
