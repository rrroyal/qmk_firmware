/*
int H = 180; // ADJUST HERE
int S = 100, V = 100; // saturation and value are 100%

int I = H / 60; // sector of the color wheel
float F = H / 60.0 - I; // fractional part of the sector

float P = V * (1 - S / 100.0);
float Q = V * (1 - (S / 100.0) * F);
float T = V * (1 - (S / 100.0) * (1 - F));

int R, G, B;
if (I == 0) {
  R = V;
  G = T;
  B = P;
} else if (I == 1) {
  R = Q;
  G = V;
  B = P;
} else if (I == 2) {
  R = P;
  G = V;
  B = T;
} else if (I == 3) {
  R = P;
  G = Q;
  B = V;
} else if (I == 4) {
  R = T;
  G = P;
  B = V;
} else if (I == 5) {
  R = V;
  G = P;
  B = Q;
}
*/

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_CUSTOM_DIGITAL_RAIN_HUE)
RGB_MATRIX_EFFECT(DIGITAL_RAIN_HUE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        ifndef RGB_DIGITAL_RAIN_DROPS
// lower the number for denser effect/wider keyboard
#            define RGB_DIGITAL_RAIN_DROPS 16
#        endif

bool DIGITAL_RAIN_HUE(effect_params_t* params) {
    // algorithm ported from https://github.com/tremby/Kaleidoscope-LEDEffect-DigitalRain
    const uint8_t drop_ticks           = 28;
    const uint8_t pure_color_intensity = (((uint16_t)rgb_matrix_config.hsv.v) * 3) >> 2;
    const uint8_t max_brightness_boost = (((uint16_t)rgb_matrix_config.hsv.v) * 3) >> 2;
    const uint8_t max_intensity        = rgb_matrix_config.hsv.v;
    const uint8_t decay_ticks          = 0xff / max_intensity;
    const float accent_multiplier      = 0.14;

    static uint8_t drop  = 0;
    static uint8_t decay = 0;

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
        drop = 0;
    }

    // const RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    decay++;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (row == 0 && drop == 0 && rand() < RAND_MAX / RGB_DIGITAL_RAIN_DROPS) {
                // top row, pixels have just fallen and we're
                // making a new rain drop in this column
                g_rgb_frame_buffer[row][col] = max_intensity;
            } else if (g_rgb_frame_buffer[row][col] > 0 && g_rgb_frame_buffer[row][col] < max_intensity) {
                // neither fully bright nor dark, decay it
                if (decay == decay_ticks) {
                    g_rgb_frame_buffer[row][col]--;
                }
            }
            // set the pixel colour
            uint8_t led[LED_HITS_TO_REMEMBER];
            uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);

            // TODO: multiple leds are supported mapped to the same row/column
            if (led_count > 0) {
                if (g_rgb_frame_buffer[row][col] > pure_color_intensity) {
                    const uint8_t boost = (uint8_t)((uint16_t)max_brightness_boost * (g_rgb_frame_buffer[row][col] - pure_color_intensity) / (max_intensity - pure_color_intensity));

                    const uint8_t r = (boost + (max_intensity * accent_multiplier));
                    const uint8_t g = boost;
                    const uint8_t b = max_intensity;
                    // const uint8_t r = rgb.r * boost;
                    // const uint8_t g = rgb.g * boost;
                    // const uint8_t b = rgb.b * boost;

                    rgb_matrix_set_color(led[0], r, g, b);
                } else {
                    const uint8_t accent = (uint8_t)((uint16_t)max_intensity * g_rgb_frame_buffer[row][col] / pure_color_intensity);

                    const uint8_t r = (accent * accent_multiplier);
                    const uint8_t g = 0;
                    const uint8_t b = accent;
                    // const uint8_t r = rgb.r;
                    // const uint8_t g = rgb.g;
                    // const uint8_t b = rgb.b;

                    rgb_matrix_set_color(led[0], r, g, b);
                }
            }
        }
    }
    if (decay == decay_ticks) {
        decay = 0;
    }

    if (++drop > drop_ticks) {
        // reset drop timer
        drop = 0;
        for (uint8_t row = MATRIX_ROWS - 1; row > 0; row--) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                // if ths is on the bottom row and bright allow decay
                if (row == MATRIX_ROWS - 1 && g_rgb_frame_buffer[row][col] == max_intensity) {
                    g_rgb_frame_buffer[row][col]--;
                }
                // check if the pixel above is bright
                if (g_rgb_frame_buffer[row - 1][col] >= max_intensity) { // Note: can be larger than max_intensity if val was recently decreased
                    // allow old bright pixel to decay
                    g_rgb_frame_buffer[row - 1][col] = max_intensity - 1;
                    // make this pixel bright
                    g_rgb_frame_buffer[row][col] = max_intensity;
                }
            }
        }
    }
    return false;
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(ENABLE_RGB_MATRIX_DIGITAL_RAIN)
