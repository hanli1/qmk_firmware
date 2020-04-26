// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
// RGB_MATRIX_EFFECT(my_cool_effect1)
// RGB_MATRIX_EFFECT(my_cool_effect2)
// RGB_MATRIX_EFFECT(my_cool_effect3)
// RGB_MATRIX_EFFECT(my_cool_effect4)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_SIMPLE_math(HSV hsv, uint16_t offset) {
    hsv.h = hsv.h - scale8(hsv.h-85, offset);
    hsv.s = hsv.s - scale8(hsv.s-150, offset);
    return hsv;
}

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  uint16_t max_tick = 65535 / rgb_matrix_config.speed;
  for (uint8_t i = led_min; i < led_max; i++) {
      RGB_MATRIX_TEST_LED_FLAGS();
      uint16_t tick = max_tick;
      // Reverse search to find most recent key hit
      for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
          if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
              tick = g_last_hit_tracker.tick[j];
              break;
          }
      }

      if(tick != max_tick) {
        // this key should be faded to white
        uint16_t offset = scale16by8(tick, rgb_matrix_config.speed);
        RGB      rgb    = hsv_to_rgb(SOLID_REACTIVE_SIMPLE_math(rgb_matrix_config.hsv, offset));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      }
      else {
        // this is just normal backlit key
        HSV hsv;
        hsv.h = 85;
        hsv.s = 150;
        hsv.v = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      }
  }
  return led_max < DRIVER_LED_TOTAL;
}

// static bool my_cool_effect1(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);

//   for (uint8_t i = led_min; i < led_max; i++) {
//       RGB_MATRIX_TEST_LED_FLAGS();
//         HSV hsv;
//         hsv.h = 85;
//         hsv.s = 0;
//         hsv.v = rgb_matrix_config.hsv.v;
//         RGB rgb = hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   }
//   return led_max < DRIVER_LED_TOTAL;
// }
// static bool my_cool_effect2(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);

//   for (uint8_t i = led_min; i < led_max; i++) {
//       RGB_MATRIX_TEST_LED_FLAGS();
//         HSV hsv;
//         hsv.h = 85;
//         hsv.s = 50;
//         hsv.v = rgb_matrix_config.hsv.v;
//         RGB rgb = hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   }
//   return led_max < DRIVER_LED_TOTAL;
// }
// static bool my_cool_effect3(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);

//   for (uint8_t i = led_min; i < led_max; i++) {
//       RGB_MATRIX_TEST_LED_FLAGS();
//         HSV hsv;
//         hsv.h = 85;
//         hsv.s = 150;
//         hsv.v = rgb_matrix_config.hsv.v;
//         RGB rgb = hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   }
//   return led_max < DRIVER_LED_TOTAL;
// }
// static bool my_cool_effect4(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);

//   for (uint8_t i = led_min; i < led_max; i++) {
//       RGB_MATRIX_TEST_LED_FLAGS();
//         HSV hsv;
//         hsv.h = 85;
//         hsv.s = 255;
//         hsv.v = rgb_matrix_config.hsv.v;
//         RGB rgb = hsv_to_rgb(hsv);
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   }
//   return led_max < DRIVER_LED_TOTAL;
// }


// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
// static uint8_t some_global_state;
// static void my_cool_effect2_complex_init(effect_params_t* params) {
//   some_global_state = 1;
// }
// static bool my_cool_effect2_complex_run(effect_params_t* params) {
//   RGB_MATRIX_USE_LIMITS(led_min, led_max);
//   for (uint8_t i = led_min; i < led_max; i++) {
//     rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff);
//   }

//   return led_max < DRIVER_LED_TOTAL;
// }
// static bool my_cool_effect2(effect_params_t* params) {
//   if (params->init) my_cool_effect2_complex_init(params);
//   return my_cool_effect2_complex_run(params);
// }

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS