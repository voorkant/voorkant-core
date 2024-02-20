# tying things together here until I get better at Meson

all:
	meson setup --reconfigure build
	ninja -C build

clean:
	ninja -C build clean

build-targets:
	cd scripts/build-targets && make
