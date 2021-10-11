/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "bootloader.h"
// #ifdef PROTOCOL_LUFA
//   #include "lufa.h"
//   #include "split_util.h"
// #endif
// #ifdef SSD1306OLED
//   #include "ssd1306.h"
// #endif

extern keymap_config_t keymap_config;
extern rgblight_config_t rgblight_config;
extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  KC_A_UMLAUT,
  KC_O_UMLAUT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST

#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_LPLAIN RGB_MODE_PLAIN
#define KC_LRAIN  RGB_MODE_RAINBOW
#define KC_LXMAS  RGB_MODE_XMAS
#define KC_KNIGHT RGB_MODE_KNIGHT 

#define KC_CTLTB   CTL_T(KC_TAB)

#define KC_CTLESC  CTL_T(KC_ESC)
#define KC_SFTCAPS SFT_T(KC_CAPS)
#define KC_COPY    LGUI(KC_C)
#define KC_PASTE   LGUI(KC_V)
#define KC_UNDO    LGUI(KC_Z)
#define KC_CUT     LGUI(KC_X)
#define KC_GUITAB  LGUI(KC_TAB)
#define KC_VOLUP   0x80
#define KC_VOLDOWN 0x81
#define KC_VOLOFF  0x7f


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       TAB,   SCLN,  COMM,   DOT,     P,     Y,                      F,     G,     C,     R,     L,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLESC,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    SFTCAPS,  QUOT,     Q,     J,     K,     X,                      B,     M,     W,     V,     Z,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     GUITAB,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      CTLTB,VOLOFF,VOLDOWN,VOLUP,  PGUP,  PGDN,                   LEFT,  DOWN,    UP, RIGHT,  HOME,   END,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,  UNDO,   CUT,  COPY, PASTE,    F5,                     F6,    F7,    F8,    F9,   F10, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                  BSLS ,  ASTR,  LPRN,  RPRN,  AMPR,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    CTLTB ,A_UMLAUT,O_UMLAUT, XXXXX, XXXXX, XXXXX,                  PIPE ,   EQL,  LCBR,  RCBR,  QUES, GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     LSFT ,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  SLSH ,  PLUS,  LBRC,  RBRC,  TILD,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX,LPLAIN, LRAIN,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, LXMAS,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX,KNIGHT,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ) 
};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef OLED_DRIVER_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  #endif // OLED_DRIVER_ENABLE
 
  switch (keycode) {
    case KC_A_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("u")"a");
        }
        return false; 
        break;
    case KC_O_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("u")"o");
        }   
        return false;
        break;
  }
  return true;
}

// const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 27, HSV_RED}
// );
// const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {3, 3, HSV_RED}
// );
// const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 3, HSV_BLUE}
// );

// // Now define the array of layers. Later layers take precedence
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     capslock_layer,
//     lower_layer,
//     raise_layer
// );

// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Both layers will light up if both kb layers are active
//     rgblight_set_layer_state(1, layer_state_cmp(state, 1));
//     rgblight_set_layer_state(2, layer_state_cmp(state, 2));
//     return state;
// }

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     rgblight_set_layer_state(1, led_state.caps_lock);
//     return true;
// }