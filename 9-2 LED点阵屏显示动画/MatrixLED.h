#if !defined(__MATRIX_LED_H__)
#define __MATRIX_LED_H__

void matrix_led_show(unsigned char *cols, unsigned char ncol);
void matrix_led_show_shift_animation(unsigned char *animation, unsigned char ncol);
void matrix_led_show_frame_animation(unsigned char *animation, unsigned char ncol, unsigned char frame_delta);


#endif // __MATRIX_LED_H__
