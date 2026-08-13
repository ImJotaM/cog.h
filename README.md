# cog

> [!WARNING]
> **UNDER ACTIVE DEVELOPMENT**: This library is currently in an experimental stage. The API is subject to frequent and breaking changes. It is **not recommended for use in production projects** at this time.

`cog` is a portable, single-header graphics library written in C. It provides a straightforward API for window creation, OpenGL context management, texture handling, and hardware-accelerated rendering. The library goal is to give a single file to drop into your project and provide a hassle-free foundation for building graphical applications, tools, and games without the burden of complex build systems or heavy dependencies.

## Features

* **Single-Header Design:** Drop `cog.h` into your project to start using it.
* **Batch Rendering:** Automatically batches draw calls for primitives (rectangles, circles) and textures to maximize GPU performance.
* **Texture Management:** Built-in image loading and texture handling using `stb_image.h`.
* **Platform Support:** Currently targets Windows natively (using GDI32 for windowing and OpenGL32 for rendering). No heavy external frameworks required.

## Integration

To use `cog` in your project, download `cog.h` on releases page.

In exactly **one** C or C++ file, define `COG_IMPLEMENTATION` before including the header to compile the underlying implementation:

```c
#define COG_IMPLEMENTATION
#include "cog.h"

```

In all other files where you need to access the library, simply include the header normally:

```c
#include "cog.h"

```

## Quick Start

Here is a minimal example demonstrating how to initialize a window, draw shapes, and manage the render loop.

```c
#define COG_IMPLEMENTATION
#include "cog.h"

int main(void) {
    // Initialize window and rendering context
    cog_window* window = cog_create_window("cog Application", 800, 600);
    
    // Main application loop
    while (!cog_window_should_close(window)) {
        cog_poll_events();
        
        // Clear the screen (assuming a clear function exists in your API)
        cog_clear_background((cog_color){ 0, 0, 0, 255 });

        // Queue rendering operations
        cog_draw_rectangle(window, 100, 100, 200, 150, (cog_color){ 255, 0, 0, 255 });

        // Flush the batch array to the GPU and swap buffers
        cog_render(window);
    }

    cog_destroy_window(window);
    return 0;
}
```

## Compilation

When compiling an application that uses `cog` on Windows, link against the standard OpenGL and GDI libraries:

```bash
gcc main.c -lopengl32 -lgdi32
```

## Development

If you are modifying the library itself, this repository uses `just` as a command runner.

### Generating the Release Header

The library development files are located in `src/`. To bundle them into the distributable single-header format, run the packaging script:

```bash
just
```
or
```bash
just build-release
```

This executes `scripts/embed.py`, which generates `release/cog.h`.

### Running Examples

Examples are located in the `examples/` directory.

Compile and run a specific example file (e.g., `examples/textures.c`):

```bash
just run-example textures
```

Clean the build output:

```bash
just clean
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.