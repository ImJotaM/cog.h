#define COG_IMPLEMENTATION
#include <cog.h>

int main() {

    cog_window* window = cog_create_window("Primitives Example", 1280, 720);

    while(!cog_window_should_close(window)) {
        cog_poll_events();

        cog_clear_background((cog_color){ 0x00, 0x00, 0x00, 0xff });

        cog_draw_rectangle(window, 0, 0, 100, 100, (cog_color){ 255, 0, 0, 255 });
        cog_draw_triangle(window, (cog_vec2){ 150, 0 }, (cog_vec2){ 200, 100 }, (cog_vec2){ 100, 100 }, (cog_color){ 0, 255, 0, 255 });
        cog_draw_circle(window, 250, 50, 50, (cog_color){ 0, 0, 255, 255 });

        cog_render(window);
    }

    cog_destroy_window(window);

    return 0;
}