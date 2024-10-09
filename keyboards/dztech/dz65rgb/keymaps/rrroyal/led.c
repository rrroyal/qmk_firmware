#include QMK_KEYBOARD_H

// MARK: - INDICATOR_SCROLL_LOCK

#ifdef INDICATOR_SCROLL_LOCK

/*
    Lights up `INDICATOR_SCROLL_LOCK` if scroll lock is enabled.
*/

static bool last_state_scroll_lock = false;

void handle_indicator_scroll_lock(void) {
    bool is_scroll_lock_on = host_keyboard_led_state().scroll_lock;
	if (is_scroll_lock_on) {
		rgb_matrix_set_color(INDICATOR_SCROLL_LOCK, 0xFF, 0xFF, 0xFF);
	} else if (is_scroll_lock_on != last_state_scroll_lock) {
        rgb_matrix_set_color(INDICATOR_SCROLL_LOCK, 0x00, 0x00, 0x00);
    }
    last_state_scroll_lock = is_scroll_lock_on;
}
#endif

// MARK: - INDICATOR_CAPS_LOCK

#ifdef INDICATOR_CAPS_LOCK

/*
    Lights up `INDICATOR_CAPS_LOCK` if caps lock is enabled.
*/

static bool last_state_caps_lock = false;

void handle_indicator_caps_lock(void) {
    bool is_caps_lock_on = host_keyboard_led_state().caps_lock;
	if (is_caps_lock_on) {
		rgb_matrix_set_color(INDICATOR_CAPS_LOCK, RGB_WHITE);
	} else if (is_caps_lock_on != last_state_caps_lock) {
        rgb_matrix_set_color(INDICATOR_CAPS_LOCK, 0x00, 0x00, 0x00);
    }
    last_state_caps_lock = is_caps_lock_on;
}
#endif

// MARK: - INDICATOR_DYNAMIC_MACRO

#ifdef INDICATOR_DYNAMIC_MACRO

/*
    Lights up `INDICATOR_DYNAMIC_MACRO` depending on `dynamic_macro_state`.
*/

static int8_t dynamic_macro_state = 0;

bool dynamic_macro_record_start_user(int8_t direction) {
    rgb_matrix_set_color(INDICATOR_DYNAMIC_MACRO, RGB_RED);
    dynamic_macro_state = 1;
    return 0;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    rgb_matrix_set_color(INDICATOR_DYNAMIC_MACRO, RGB_BLACK);
    dynamic_macro_state = 0;
    return 0;
}

bool dynamic_macro_play_user(int8_t direction) {
    rgb_matrix_set_color(INDICATOR_DYNAMIC_MACRO, RGB_GREEN);
    dynamic_macro_state = 0;
    dynamic_macro_led_blink();
    return 0;
}

void handle_indicator_dynamic_macro(void) {
    switch (dynamic_macro_state) {
        case 0:
            break;
        case 1:
            rgb_matrix_set_color(INDICATOR_DYNAMIC_MACRO, RGB_RED);
            break;
        case 2:
            rgb_matrix_set_color(INDICATOR_DYNAMIC_MACRO, RGB_GREEN);
            break;
        default:
            break;
    }
}
#endif

// MARK: - INDICATOR_LAYER

#ifdef INDICATOR_LAYER

/*
    Lights up all keys that have a binding on active layer (if layer > 0).
*/

void handle_indicator_layer(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer <= 0) return;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            // if !(index >= led_min && index < led_max && index != NO_LED) continue;

            if (keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                rgb_matrix_set_color(index, RGB_WHITE);
            } else {
                rgb_matrix_set_color(index, RGB_BLACK);
            }
        }
    }
}
#endif

// MARK: - rgb_matrix_indicators_kb

// bool rgb_matrix_indicators_kb(void) {
//     #ifdef INDICATOR_SCROLL_LOCK
//     handle_indicator_scroll_lock();
// 	#endif
//
// 	#ifdef INDICATOR_CAPS_LOCK
//     handle_indicator_caps_lock();
// 	#endif
//
//     #ifdef INDICATOR_DYNAMIC_MACRO
//     handle_indicator_dynamic_macro();
//     #endif
//
//     return false;
// }

// MARK: - rgb_matrix_indicators_advanced_user

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    #ifdef INDICATOR_SCROLL_LOCK
    handle_indicator_scroll_lock();
	#endif

	#ifdef INDICATOR_CAPS_LOCK
    handle_indicator_caps_lock();
	#endif

    #ifdef INDICATOR_DYNAMIC_MACRO
    handle_indicator_dynamic_macro();
    #endif

    #ifdef INDICATOR_LAYER
    handle_indicator_layer(led_min, led_max);
    #endif

    return false;
}
