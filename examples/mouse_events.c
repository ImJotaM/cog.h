#define COG_IMPLEMENTATION
#include <cog.h>

int main() {

    cog_window* window = cog_create_window("Primitives Example", 1280, 720);

    while(!cog_window_should_close(window)) {
        cog_poll_events();

        cog_vec2 mouse_pos = cog_get_mouse_position(window);
    
        if (cog_is_mouse_button_pressed(window, COG_MOUSE_BUTTON_LEFT)) {
            printf("Left mouse button pressed in position: X: %.2f, Y: %.2f\n", mouse_pos.x, mouse_pos.y);
        }
        
        if (cog_is_mouse_button_released(window, COG_MOUSE_BUTTON_LEFT)) {
            printf("Left mouse button released in position: X: %.2f, Y: %.2f\n", mouse_pos.x, mouse_pos.y);
        }

        if (cog_is_mouse_button_down(window, COG_MOUSE_BUTTON_RIGHT)) {
            printf("Right mouse button down in position: X: %.2f, Y: %.2f\n", mouse_pos.x, mouse_pos.y);
        }

        if (cog_is_mouse_button_up(window, COG_MOUSE_BUTTON_MIDDLE)) {
            printf("Middle mouse button down in position: X: %.2f, Y: %.2f\n", mouse_pos.x, mouse_pos.y);
        }

        cog_clear_background((cog_color){ 0x00, 0x00, 0x00, 0xff });

        cog_render(window);
    }

    cog_destroy_window(window);

    return 0;
}