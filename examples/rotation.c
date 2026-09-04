#define COG_IMPLEMENTATION
#include <cog.h>

int main(void) {
    
    cog_window* window = cog_create_window("Rotation Example", 1280, 720);
    cog_set_vsync(window, true);

    cog_font* font = cog_load_font("examples/assets/fonts/0xProtoNerdFont-Regular.ttf");

    float rotation = 0.0f;

    while (!cog_window_should_close(window)) {
        cog_poll_events();

        float dt = cog_get_delta_time(window);
        rotation += 60.0f * dt;
        if (rotation >= 360.0f) rotation -= 360.0f;

        cog_clear_background((cog_color){ 20, 20, 20, 255 });

        // 1. Rotating solid rectangle (auto-origin)
        cog_set_rotation(window, rotation);
        cog_draw_rectangle(window, 405, 185, 110, 110, (cog_color){ 255, 80, 80, 255 });
        cog_reset_rotation(window);

        // 2. Rotating triangle lines (auto-origin)
        cog_set_rotation(window, -rotation * 1.5f);
        cog_draw_triangle_lines(window,
            (cog_vec2){ 640, 175 },
            (cog_vec2){ 575, 295 },
            (cog_vec2){ 705, 295 },
            3.0f, (cog_color){ 80, 255, 80, 255 });
        cog_reset_rotation(window);

        // 3. Rotating rectangle lines (auto-origin)
        cog_set_rotation(window, rotation);
        cog_draw_rectangle_lines(window, 765, 185, 110, 110, 3.0f, (cog_color){ 80, 160, 255, 255 });
        cog_reset_rotation(window);

        // 4. Rotating text (auto-origin)
        if (font) {
            float pendulum_angle = sinf(rotation * 0.05f) * 25.0f;
            cog_set_rotation(window, pendulum_angle);
            cog_draw_text(window, font, "Dynamic Rotating Text!", 475, 380, 32.0f, (cog_color){ 255, 255, 255, 255 });
            cog_reset_rotation(window);
        }

        // 5. Orbiting satellite (custom origin)
        cog_draw_circle(window, 640, 520, 8, 0, (cog_color){ 255, 255, 255, 255 });

        cog_set_rotation_origin(window, rotation * 2.0f, (cog_vec2){ 640, 520 });
        cog_draw_rectangle(window, 703, 508, 24, 24, (cog_color){ 255, 100, 200, 255 });
        cog_reset_rotation(window);

        cog_render(window);
    }

    if (font) cog_destroy_font(font);
    cog_destroy_window(window);
    return 0;
}