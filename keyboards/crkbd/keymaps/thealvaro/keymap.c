#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 27, HSV_RED}
);
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 3, HSV_RED}
);
const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer,
    lower_layer,
    raise_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}