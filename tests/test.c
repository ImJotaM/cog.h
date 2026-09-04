#define COG_IMPLEMENTATION
#include <cog.h>

int main(void) {
    cog_window* window = cog_create_window("Primitives Example", 1280, 720);

    while (!cog_window_should_close(window)) {
        cog_poll_events();

        cog_clear_background((cog_color){ 20, 20, 20, 255 });

        // Filled primitives
        cog_draw_rectangle(window, 400, 170, 120, 120, (cog_color){ 255, 70, 70, 255 });
        cog_draw_triangle(window, (cog_vec2){ 640, 170 }, (cog_vec2){ 580, 290 }, (cog_vec2){ 700, 290 }, (cog_color){ 70, 255, 70, 255 });
        cog_draw_circle(window, 820, 230, 60, 0, (cog_color){ 70, 140, 255, 255 });

        // Outline primitives
        cog_draw_rectangle_lines(window, 400, 350, 120, 120, 3.0f, (cog_color){ 255, 70, 70, 255 });
        cog_draw_triangle_lines(window, (cog_vec2){ 640, 350 }, (cog_vec2){ 580, 470 }, (cog_vec2){ 700, 470 }, 3.0f, (cog_color){ 70, 255, 70, 255 });
        cog_draw_circle_lines(window, 820, 410, 60, 3.0f, 0, (cog_color){ 70, 140, 255, 255 });

        // Line primitive
        cog_draw_line(window, 400, 530, 880, 530, 4.0f, (cog_color){ 255, 215, 0, 255 });

        cog_render(window);
    }

    cog_destroy_window(window);
    return 0;
}