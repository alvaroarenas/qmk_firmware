#include QMK_KEYBOARD_H
#include "sendstring_finnish.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _FUNCTION,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Custom keycodes for layer keys
// Dual function escape with left command
#define KC_LGESC LGUI_T(KC_ESC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  KC_RACL, // right alt / colon
  KC_A_UMLAUT,
  KC_O_UMLAUT 
};

#define KC_ALT_ESC RALT_T(KC_ESC)
#define KC_CMD_ESC CMD_T(KC_ESC)
#define KC_CTLCAPS CTL_T(KC_CAPS)
#define KC_ALT_V   MT(MOD_RALT,KC_V)
#define KC_ALT_CMD_B MT(MOD_RALT|MOD_LGUI,KC_B)
#define KC_ALT_CMD_N   MT(MOD_LGUI,KC_N)
#define KC_ALT_M MT(MOD_RALT,KC_M)
#define KC_COPY    LGUI(KC_C)
#define KC_PASTE   LGUI(KC_V)
#define KC_UNDO    LGUI(KC_Z)
#define KC_CUT     LGUI(KC_X)
#define KC_CLOSEW  LGUI(KC_W)
#define KC_GUITAB  LGUI(KC_TAB)
#define KC_VOLUP   0x80
#define KC_VOLDOWN 0x81
#define KC_VOLOFF  0x7f
#define LAG(kc) (QK_LALT | QK_LGUI | (kc))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_QWERTY] = LAYOUT(
  //,-----------------------------------------.                ,---------------------------------------------.
     KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,   KC_I,  KC_O,  KC_P,  KC_BSPC,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
   KC_ESC,KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H, KC_J, KC_K,  KC_L, FI_QUOT, FI_DQUO,
  //|------+------+------+------+------+------|                |------+------+-------+------+-------+--------|
    KC_LSFT,KC_Z, KC_X,  KC_C, KC_ALT_V, KC_ALT_CMD_B,   KC_ALT_CMD_N,KC_ALT_M,KC_COMM,KC_DOT,FI_MINS, KC_RSFT,
  //|------+------+------+------+------+------+------|  |------+------+------+-------+------+-------+--------|
                        KC_LCMD,LOWER, RCTL_T(KC_SPC),   RCTL_T(KC_ENT), RAISE, KC_CMD_ESC
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------------.                ,-----------------------------------------.
   LGUI(KC_GRV),  KC_1, KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,  KC_7,  KC_8,  KC_9,  KC_0, KC_DEL,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
   LGUI(KC_GRV),LAG(KC_1),LAG(KC_2),LAG(KC_3),LAG(KC_4),LAG(KC_5),   KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,FI_ODIA,FI_ADIA,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
   KC_LSFT,KC_UNDO,KC_CUT,KC_COPY,KC_PASTE,KC_CLOSEW,                KC_HOME,KC_PGDN,KC_PGUP,KC_END,FI_TILD,KC_NO,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT
                                  //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_ESC,KC_EXLM,FI_AT,KC_HASH,FI_DLR,KC_PERC,              FI_PLUS,FI_BSLS, FI_LPRN, FI_RPRN, FI_AMPR, FI_DIAE,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
   KC_LCTL, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,              FI_EQL, FI_PIPE, FI_LCBR, FI_RCBR, FI_QUES, FI_ACUT,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT, KC_F6, KC_F7, KC_F8, KC_F9,KC_F10,                FI_ASTR,FI_SLSH , FI_LBRC, FI_RBRC, FI_LABK, KC_NO,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------.                ,-----------------------------------------.
    RGBRST,LCA(KC_Q),LCA(KC_W),LCA(KC_E),LCA(KC_R),LCA(KC_T),  KC__VOLUP,LCA(KC_U), LCA(KC_I),  LCA(KC_O), LCA(KC_P), KC_NO, 
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,LCA(KC_A),LCA(KC_S),LCA(KC_D),LCA(KC_F),LCA(KC_G), KC__MUTE,LCA(KC_J), LCA(KC_K),  LCA(KC_L), FI_QUOT, FI_DQUO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,LCA(KC_Z),LCA(KC_X),LCA(KC_C),LCA(KC_V),LCA(KC_B), KC__VOLDOWN,LCA(KC_M), LCA(KC_COMM),LCA(KC_DOT), LCA(FI_MINS), KC_NO, 
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT
                              //`--------------------'  `--------------------'
  ),


};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
    #endif
    // set_timelog();
  }
  static uint16_t my_colon_timer;

  switch (keycode) {
    case KC_A_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("u")"a");
        }
        break;
    case KC_O_UMLAUT:
        if (record->event.pressed) {
            SEND_STRING(SS_RALT("u")"o");
        }   
        break;
  }

  switch (keycode) {
    // case QWERTY:
    //   if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    //     rgb_matrix_set_color_all(204, 0, 0)
    //   }
    //   else {

    //   }
    case KC_CTLCAPS:
        if (record -> event.pressed) {
            rgb_matrix_toggle();
        }
        return true;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case KC_RACL:
        if (record->event.pressed) {
          my_colon_timer = timer_read();
          register_code(KC_RALT);
        } else {
          unregister_code(KC_RALT);
          if (timer_elapsed(my_colon_timer) < TAPPING_TERM) {
            SEND_STRING(":"); // Change the character(s) to be sent on tap here
          }
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void rgb_matrix_indicators_user(void) {
    // if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    //     rgb_matrix_set_color(8, 0xFF, 0xFF, 0xFF);
    // }
}

#endif
