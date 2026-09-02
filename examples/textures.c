#define COG_IMPLEMENTATION
#include <cog.h>

int main() {

    cog_window* window = cog_create_window("Textures Example", 1280, 720);

    cog_texture* texture_1 = cog_load_texture("examples/assets/textures/texture_example_1.jpg");
    cog_texture* texture_2 = cog_load_texture("examples/assets/textures/texture_example_2.jpeg");
    cog_texture* texture_3 = cog_load_texture("examples/assets/textures/texture_example_3.png");

    while(!cog_window_should_close(window)) {
        cog_poll_events();

        cog_clear_background((cog_color){ 0x00, 0x00, 0x00, 0xff });

        cog_draw_texture(window, texture_1, 0, 0, 300, 300, (cog_color){ 0xff, 0xff, 0xff, 0xff });
        cog_draw_texture(window, texture_2, 300, 0, 300, 300, (cog_color){ 0xff, 0xff, 0xff, 0xff });
        cog_draw_texture(window, texture_3, 600, 0, 300, 300, (cog_color){ 0xff, 0xff, 0xff, 0xff });

        cog_render(window);
    }

    cog_destroy_texture(texture_1);
    cog_destroy_texture(texture_2);
    cog_destroy_texture(texture_3);

    cog_destroy_window(window);

    return 0;
}