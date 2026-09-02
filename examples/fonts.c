#define COG_IMPLEMENTATION
#include <cog.h>

int main() {

    cog_window* window = cog_create_window("Primitives Example", 1280, 720);

    cog_font* font = cog_load_font("examples/assets/fonts/0xProtoNerdFont-Regular.ttf");
    
    const char* text_example = "Hello, World!";
    float fontsize = 32.0f;

    cog_vec2 size = cog_measure_text(font, text_example, fontsize);
    int x = (cog_get_window_size(window).x - size.x) / 2.0f;
    int y = (cog_get_window_size(window).y - size.y) / 2.0f;

    while(!cog_window_should_close(window)) {
        cog_poll_events();

        cog_clear_background((cog_color){ 0x00, 0x00, 0x00, 0xff });

        cog_draw_text(window, font, text_example, x, y, fontsize, (cog_color){ 0xff, 0xff, 0xff, 0xff });

        cog_render(window);
    }

    cog_destroy_font(font);

    cog_destroy_window(window);

    return 0;
}