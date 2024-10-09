#pragma once

// Device identification

#ifdef PRODUCT
	#undef PRODUCT
#endif

//#define VENDOR_ID 0x1234
//#define PRODUCT_ID 0x5678
//#define DEVICE_VER 0x0100
//#define MANUFACTURER "DZTech"
#define PRODUCT "TOFU65"

// Disable stuff that's not needed
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#define NO_MUSIC_MODE

#define LAYER_STATE_8BIT

// Macros
#define DYNAMIC_MACRO_NO_NESTING

// Indicators
#define INDICATOR_SCROLL_LOCK 29
#define INDICATOR_CAPS_LOCK 30
#define INDICATOR_DYNAMIC_MACRO 0
#define	INDICATOR_LAYER

// RGB

#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGBLIGHT_HUE_STEP 5

#ifndef RGB_MATRIX_ENABLE
	#define	RGB_MATRIX_ENABLE
#endif

#define	RGB_MATRIX_FRAMEBUFFER_EFFECTS

#undef	RGB_MATRIX_KEYRELEASES
#define	RGB_MATRIX_KEYPRESSES


// Enable/disable RGB modes
#define ENABLE_RGB_MATRIX_SOLID_COLOR				// Static single hue, no speed support
#undef	ENABLE_RGB_MATRIX_ALPHAS_MODS				// Static dual hue, speed is hue for secondary hue
#undef	ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN			// Static gradient top to bottom, speed controls how much gradient changes
#undef	ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT		// Static gradient left to right	speed controls how much gradient changes
#undef	ENABLE_RGB_MATRIX_BREATHING					// Single hue brightness cycling animation
#undef	ENABLE_RGB_MATRIX_BAND_SAT					// Single hue band fading saturation scrolling left to right
#undef	ENABLE_RGB_MATRIX_BAND_VAL					// Single hue band fading brightness scrolling left to right
#undef	ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT			// Single hue 3 blade spinning pinwheel fades saturation
#undef	ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL			// Single hue 3 blade spinning pinwheel fades brightness
#undef	ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT			// Single hue spinning spiral fades saturation
#undef	ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL			// Single hue spinning spiral fades brightness
#undef	ENABLE_RGB_MATRIX_CYCLE_ALL					// Full keyboard solid hue cycling through full gradient
#undef	ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT			// Full gradient scrolling left to right
#undef	ENABLE_RGB_MATRIX_CYCLE_UP_DOWN				// Full gradient scrolling top to bottom
#undef	ENABLE_RGB_MATRIX_CYCLE_OUT_IN				// Full gradient scrolling out to in
#undef	ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL			// Full dual gradients scrolling out to in
#undef	ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON	// Full gradent Chevron shapped scrolling left to right
#undef	ENABLE_RGB_MATRIX_CYCLE_PINWHEEL			// Full gradient spinning pinwheel around center of keyboard
#undef	ENABLE_RGB_MATRIX_CYCLE_SPIRAL				// Full gradient spinning spiral around center of keyboard
#undef	ENABLE_RGB_MATRIX_DUAL_BEACON				// Full gradient spinning around center of keyboard
#undef	ENABLE_RGB_MATRIX_RAINBOW_BEACON			// Full tighter gradient spinning around center of keyboard
#undef	ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS			// Full dual gradients spinning two halfs of keyboard
#define	ENABLE_RGB_MATRIX_RAINDROPS					// Randomly changes a single key's hue
#define	ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS		// Randomly changes a single key's hue and saturation
#undef	ENABLE_RGB_MATRIX_HUE_BREATHING				// Hue shifts up a slight ammount at the same time, then shifts back
#undef	ENABLE_RGB_MATRIX_HUE_PENDULUM				// Hue shifts up a slight ammount in a wave to the right, then back to the left
#undef	ENABLE_RGB_MATRIX_HUE_WAVE					// Hue shifts up a slight ammount and then back down in a wave to the right
#define	ENABLE_RGB_MATRIX_PIXEL_FRACTAL				// Single hue fractal filled keys pulsing horizontally out to edges
#define	ENABLE_RGB_MATRIX_PIXEL_FLOW				// Pulsing RGB flow along LED wiring with random hues
#define	ENABLE_RGB_MATRIX_PIXEL_RAIN				// Randomly light keys with random hues

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
	#define	ENABLE_RGB_MATRIX_TYPING_HEATMAP	// How hot is your WPM!
	#undef	ENABLE_RGB_MATRIX_DIGITAL_RAIN		// That famous computer simulation
    #define	ENABLE_RGB_MATRIX_CUSTOM_DIGITAL_RAIN_HUE  // !
#endif

#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
	#define	ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE			// Pulses keys hit to hue & value then fades value out
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE				// Static single hue, pulses keys hit to shifted hue then fades to current hue
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE			// Hue & value pulse near a single key hit then fades value out
	#define	ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE		// Hue & value pulse near multiple key hits then fades value out
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS			// Hue & value pulse the same column and row of a single key hit then fades value out
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS		// Hue & value pulse the same column and row of multiple key hits then fades value #define ENABLE_out
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS			// Hue & value pulse away on the same column and row of a single key hit then fades #define ENABLE_value out
	#undef	ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS		// Hue & value pulse away on the same column and row of multiple key hits then fades #define ENABLE_value out
	#undef	ENABLE_RGB_MATRIX_SPLASH						// Full gradient & value pulse away from a single key hit then fades value out
	#undef	ENABLE_RGB_MATRIX_MULTISPLASH					// Full gradient & value pulse away from multiple key hits then fades value out
	#undef	ENABLE_RGB_MATRIX_SOLID_SPLASH					// Hue & value pulse away from a single key hit then fades value out
	#define	ENABLE_RGB_MATRIX_SOLID_MULTISPLASH				// Hue & value pulse away from multiple key hits then fades value out
#endif

// Startup RGB mode
#ifdef RGB_MATRIX_DEFAULT_MODE
	#undef RGB_MATRIX_DEFAULT_MODE
#endif
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_DIGITAL_RAIN_HUE
#define RGB_MATRIX_DEFAULT_HUE 100
#define RGB_MATRIX_DEFAULT_SPD 20
