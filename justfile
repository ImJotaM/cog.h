# --- Configuration ---
CC := "gcc"
CFLAGS := "-I./src -I./vendor"
LDFLAGS := "-lopengl32 -lgdi32"

default: build-release

# --- Library Release ---
build-release:
    mkdir -p release
    python ./scripts/embed.py ./src/cog.h ./vendor/stb_image.h stb_image.h ./release/cog.h

# --- Examples ---
compile-example example: build-release
    mkdir -p bin
    gcc ./examples/{{example}}.c -o ./bin/{{example}}.exe {{LDFLAGS}} -I./release/

compile-run-example example: (compile-example example)
    ./bin/{{example}}.exe

# --- Utility ---
clean:
    rm -f ./bin/*

# --- Test helpers ---
compile-test:
    mkdir -p bin
    {{CC}} ./tests/test.c -o ./bin/test.exe {{CFLAGS}} {{LDFLAGS}}

compile-run-test: compile-test
    ./bin/test.exe