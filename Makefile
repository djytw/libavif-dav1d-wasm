all:
	@mkdir -p build
	emcc libavif.c libavif/build/libavif.a libavif/ext/dav1d/build/src/libdav1d.a \
	-Wall -Ilibavif/include -s STANDALONE_WASM -Oz --no-entry \
	-s EXPORTED_FUNCTIONS="['_avif_decode', '_malloc', '_free']" \
	-o build/libavif.wasm

clean:
	rm -rf build
