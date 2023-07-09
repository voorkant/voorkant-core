# tying things together here until I get better at Meson

all:
#	cd libs/imtui && cmake -Bbuild -DCMAKE_INSTALL_PREFIX=./build/_install && cmake --build build/ --target install

	meson setup --reconfigure build
	ninja -C build

clean:
	ninja -C build clean
