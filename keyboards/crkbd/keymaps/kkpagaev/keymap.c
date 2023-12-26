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
#include <stdio.h>

#define frame_size 512
#define ONESHOT_TAP_TOGGLE 0  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 100  /* Time (in ms) before the one shot key is released */
#define OS_ON true  /* Time (in ms) before the one shot key is released */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// #define OLED_SCREENSAVER_TIMEOUT 5000

enum custom_keycodes {
    ALTTAB = SAFE_RANGE,
    WINTAB,
    SALTTAB,
    SGRV,
    CTAB,
    SCTAB,
    STAB,
};

enum combos {
    SD_GUI,
    HJ_FULL,
    // AS_WIN,
    // JK_TAB,
    // QW_SFT,
    // SD_LAYER,
    UIO_CAPS,
    XC_ESC,
    // KL_TAB
};

const uint16_t PROGMEM ab_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {LT(4, KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM uio_combo[] = {KC_U, KC_I, KC_O, COMBO_END};
// const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM as_combo[] = {KC_A, KC_S, COMBO_END};

combo_t key_combos[] = {
    [SD_GUI] = COMBO(ab_combo, KC_LGUI),
    [HJ_FULL] = COMBO(hj_combo, LALT(KC_ENT)),
    // [HJ_FULL] = COMBO(hj_combo, KC_LGUI),
    [UIO_CAPS] = COMBO(uio_combo, KC_CAPS),
    [XC_ESC] = COMBO(xc_combo, KC_ESC),
//     [KL_TAB] = COMBO(df_combo, KC_TAB),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LEFT_BRACKET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      // KC_LCTL,    KC_A,    KC_S,    KC_D,    MT(MOD_LSFT, KC_F),    KC_G,                         KC_H,    MT(MOD_LSFT, KC_J),    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    LT(4, KC_Z),    LT(4, KC_X),    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MO(6),  MO(1),  KC_SPC,     KC_LSFT,   MO(2), MO(4)
                                      // `--------------------------'  `--------------------------'
                                           // KC_LGUI,   KC_LALT,  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)
  ),
    // nav
    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ALTTAB,  LALT(KC_Q),   LALT(KC_W), LALT(KC_E), KC_UP,  LALT(KC_T),                      KC_RIGHT, LCTL(KC_U), LCTL(KC_I), LCTL(KC_O),  LALT(KC_P), LALT(KC_LEFT_BRACKET),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LCTL, LALT(KC_S), CTAB, KC_TAB, LCTL(KC_SPC),                      KC_LEFT, KC_BSPC, LCTL(KC_K), KC_DOWN, LCTL(KC_SCLN),LALT(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, TG(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      LALT(KC_N), KC_ENT,  LCTL(KC_COMM), XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, OSL(1),  KC_SPC,     KC_LSFT, OSL(3), KC_RALT

    ),

    // symb
    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                ,-----------------------------------------------------.
       KC_TAB, KC_TAB,   KC_2, KC_3,  KC_GRV, LSFT(KC_GRV),                                 LSFT(KC_1), LSFT(KC_RBRC), KC_4, KC_0, KC_RBRC, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                                 |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_QUOT, KC_7, KC_LBRC, KC_5, KC_6,                                          KC_1,  KC_8, KC_9, _______, _______,  _______,
  //|--------+--------+--------+--------+--------+--------|                                 |--------+--------+--------+--------+--------+--------|
      KC_LSFT, LSFT(KC_EQL), KC_MINS, LSFT(KC_BACKSLASH), LSFT(KC_QUOT), LSFT(KC_LBRC),     KC_EQL, KC_BACKSLASH, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_ESC,   KC_ESC,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    // number
    [3] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  LSFT(KC_2), LSFT(KC_3),LSFT(KC_4),LSFT(KC_5), LSFT(KC_6),       LSFT(KC_MINUS),    LSFT(KC_7),    LSFT(KC_8),    LSFT(KC_9), LSFT(KC_0), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(1),  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    // system
    [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_MS_UP,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_7,    KC_MS_BTN2,    KC_MS_BTN3,    KC_MS_BTN1,    KC_9,            KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, TG(4), LCTL(KC_Z), KC_MS_WH_DOWN, KC_MS_WH_UP, XXXXXXX,                      XXXXXXX, KC_MS_BTN1, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(1),  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
                                      //`--------------------------'  `--------------------------'

  //      KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  // //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //     KC_LCTL,    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                         KC_8,    KC_0,    KC_2,    KC_4,    KC_6, XXXXXXX,
  // //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //     KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  // //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
  //                                         KC_LGUI, MO(3),  KC_SPC,     KC_ENT,   MO(3), KC_RALT
  ),
  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LEFT_BRACKET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  MO(1),  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)
                                      //`--------------------------'  `--------------------------'
                                          // KC_LGUI,   KC_LALT,  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)

  ),

  [6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LEFT_BRACKET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_SCLN,    KC_L,    KC_K,    KC_J,    KC_H,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_SLSH, KC_DOT,    KC_COMM,    KC_M,    KC_N,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  MO(1),  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)
                                      //`--------------------------'  `--------------------------'
                                          // KC_LGUI,   KC_LALT,  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)

  ),
};

bool should_process_keypress(void) { return true; }

bool is_symb_layer = false;
bool is_anything_pressed = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    is_symb_layer = get_highest_layer(state) == 2;
    is_anything_pressed = false;
    return state;
}

bool is_alt_tab_active = false;
bool is_win_active = false;
bool is_ctrl_tab_active = false;
bool is_pipe_pressed = false;
bool is_eq_pressed = false;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (is_symb_layer) {
        if (!is_anything_pressed && keycode == KC_SPC ) {
            register_code16(RALT(KC_SPC));
        } else {
            if (keycode != RALT(KC_SPC)) {
                is_anything_pressed = true;
            }
        }
    }
    switch (keycode) {
        case KC_6:
            if (record->event.pressed) {
                is_eq_pressed = true;
            }
            return true;
            break;
        case LSFT(KC_LBRC):
            if (record->event.pressed && is_eq_pressed) {
                SEND_STRING("E");
                return false;
            }

            break;
        case LSFT(KC_BACKSLASH):
            if (record->event.pressed) {
                is_pipe_pressed = true;
            }
            return true;
            break;
        case  LSFT(KC_QUOT):
            if (record->event.pressed && is_pipe_pressed) {
                SEND_STRING("E");
                return false;
            }
            break;
        case ALTTAB: // ALT+TAB
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return true;
            break;
        case CTAB: // CTRL+TAB
            if (record->event.pressed) {
                if (!is_ctrl_tab_active) {
                    is_ctrl_tab_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return true;
            break;
        case STAB: // CTRL+TAB
            if (record->event.pressed) {
                if (!is_win_active) {
                    is_win_active = true;
                    register_code(KC_LGUI);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
            break;
        case SGRV: // CTRL+TAB
            if (record->event.pressed) {
                if (!is_win_active) {
                    is_win_active = true;
                    register_code(KC_LGUI);
                }
                register_code(KC_GRV);
            } else {
                unregister_code(KC_GRV);
            }
            return false;
            break;
        case SALTTAB: // ALT+SHIFT+TAB
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                register_code16(S(KC_TAB));
            } else {
                unregister_code16(S(KC_TAB));
            }
            return false;
            break;
    }

    is_pipe_pressed = false;
    is_eq_pressed = false;
    return true;
}

void matrix_scan_user(void) {
    if (is_win_active) {
        if (IS_LAYER_OFF(1)){
            unregister_code(KC_LGUI);
            is_win_active = false;
        }
    }

    if (is_alt_tab_active) {
        if (IS_LAYER_OFF(1)){
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    if (is_ctrl_tab_active) {
        if (IS_LAYER_OFF(1)){
            unregister_code(KC_LCTL);
            is_ctrl_tab_active = false;
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

static const char PROGMEM logo_clean[frame_size] = {
    // 'res', 32x128px
    0x00, 0xff, 0x11, 0x11, 0x09, 0x06, 0x00, 0x0e, 0x11, 0xce, 0xe0, 0xf0, 0xf9, 0x06, 0x08, 0x04,
    0x08, 0x06, 0xf9, 0xf0, 0xe0, 0xce, 0x15, 0x15, 0x00, 0xff, 0x11, 0x31, 0x49, 0x86, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x80, 0xc0, 0x70, 0x18, 0x0c, 0x92, 0x8f, 0x0f, 0x0f, 0x0f, 0x01, 0x01, 0x1a,
    0x15, 0x01, 0x8f, 0x0f, 0x0f, 0x0f, 0x01, 0x12, 0x04, 0x3c, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0xf0, 0x0e, 0x03, 0x00, 0xf0, 0x6c, 0x23, 0x21, 0x70, 0x30, 0x70, 0xd8, 0xee, 0x0d, 0x1c,
    0x02, 0xf8, 0x1c, 0x1f, 0xb0, 0x20, 0x41, 0x42, 0x44, 0x48, 0x88, 0x31, 0x47, 0xbe, 0xc0, 0x00,
    0x00, 0xff, 0x00, 0x00, 0x8f, 0x00, 0xff, 0xe0, 0xe4, 0xee, 0xe4, 0xe0, 0x1c, 0x00, 0x00, 0xf8,
    0x1f, 0xe1, 0xfe, 0xfe, 0xe0, 0xe4, 0xee, 0xe4, 0xe0, 0xfe, 0xfd, 0xfa, 0x3c, 0xc3, 0xfc, 0x00,
    0x00, 0x83, 0x78, 0x08, 0x08, 0x88, 0x61, 0x11, 0x0b, 0xcb, 0x6b, 0x2b, 0x04, 0x04, 0x05, 0x05,
    0x04, 0x0e, 0x12, 0x15, 0xa5, 0x49, 0x71, 0x81, 0x03, 0x0b, 0x31, 0x40, 0x80, 0x9f, 0x3f, 0x00,
    0x1e, 0xe1, 0x00, 0x0c, 0x23, 0xf8, 0x06, 0x00, 0x08, 0xf0, 0x20, 0x60, 0xc0, 0x88, 0x98, 0xf0,
    0x22, 0x64, 0xc8, 0x00, 0x80, 0x47, 0x20, 0x19, 0x1e, 0x00, 0x0c, 0xb0, 0x04, 0x7a, 0x81, 0x00,
    0x00, 0x00, 0x07, 0x38, 0xc0, 0x00, 0x01, 0x80, 0x02, 0x09, 0x17, 0x2f, 0xdf, 0xd5, 0x57, 0xdb,
    0xdf, 0x2f, 0x04, 0x08, 0x40, 0x30, 0x00, 0x30, 0x8c, 0x00, 0x00, 0x03, 0x1c, 0x80, 0x3f, 0xc0,
    0x00, 0x38, 0xe4, 0xa2, 0x41, 0x1c, 0x6b, 0xf4, 0xf8, 0xfa, 0x7c, 0x3f, 0xbf, 0xfd, 0xfe, 0xfd,
    0x7f, 0x3f, 0x1e, 0x00, 0x0e, 0xff, 0xff, 0xff, 0xfe, 0x01, 0x00, 0x00, 0xc0, 0x39, 0x06, 0x01,
    0x00, 0x08, 0x30, 0x40, 0x04, 0x06, 0x80, 0x00, 0x00, 0xc0, 0x60, 0x80, 0x0c, 0x00, 0x00, 0x00,
    0xc2, 0x04, 0x02, 0x00, 0xc0, 0x21, 0x03, 0x03, 0x31, 0x08, 0x04, 0x03, 0x00, 0x40, 0x00, 0x00,
    0x00, 0x24, 0x40, 0x80, 0x30, 0x9e, 0x1f, 0x0c, 0x08, 0x80, 0x00, 0x01, 0xc4, 0x86, 0x98, 0x20,
    0x40, 0x10, 0xc3, 0x8c, 0x10, 0x00, 0x00, 0x81, 0x11, 0x64, 0x83, 0x20, 0x00, 0x17, 0x60, 0x00,
    0x00, 0xf9, 0x00, 0x00, 0x07, 0xcb, 0x96, 0x3c, 0x75, 0xfc, 0xfa, 0xff, 0x7f, 0xff, 0xff, 0xcf,
    0xde, 0xfe, 0xff, 0xff, 0xfa, 0xfc, 0xf5, 0x7c, 0x34, 0x9a, 0xcd, 0x00, 0x00, 0x7c, 0x80, 0x00,
    0x00, 0xb9, 0x00, 0x50, 0x80, 0x00, 0x01, 0x03, 0x06, 0x07, 0x0f, 0x0f, 0x6f, 0xde, 0xde, 0xbf,
    0xbd, 0xbe, 0xde, 0x1f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x00, 0x40, 0x30, 0x8e, 0x60, 0x00,
    0x00, 0x0d, 0x01, 0x82, 0x64, 0x10, 0x08, 0x84, 0x42, 0x82, 0x01, 0x81, 0x01, 0x00, 0x80, 0x00,
    0x80, 0x00, 0x40, 0x81, 0x01, 0x01, 0x81, 0x01, 0x86, 0x46, 0x88, 0x08, 0x11, 0x60, 0x87, 0x00,
    0xe0, 0x20, 0x3c, 0xe3, 0xb0, 0x00, 0xfc, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0xe0, 0xfe, 0x80, 0x00,
    0x00, 0xf0, 0x1c, 0x01, 0x7c, 0xe0, 0x00, 0x00, 0xf8, 0xc0, 0x01, 0xfc, 0x00, 0xd0, 0x03, 0xfc,
    0x05, 0x0b, 0xf1, 0x1b, 0xff, 0x00, 0x00, 0x00, 0xf0, 0xee, 0xd0, 0xd0, 0xe0, 0xf8, 0xfe, 0xfe,
    0xfc, 0xfe, 0xfe, 0xfe, 0xf0, 0xee, 0xd0, 0xd0, 0xc1, 0xe3, 0x1c, 0x00, 0x00, 0xff, 0x00, 0xff,
    0x00, 0xf0, 0x0f, 0xc0, 0x1f, 0x0c, 0x10, 0x1f, 0x02, 0x05, 0xcb, 0xa3, 0x67, 0xe7, 0xd7, 0xf6,
    0x06, 0xf5, 0xd7, 0xe7, 0x67, 0xa7, 0xcb, 0x3b, 0xc5, 0x02, 0x1f, 0x10, 0x0c, 0x1f, 0xc0, 0x0f
};

bool oled_task_user(void) {
  oled_set_brightness(0);
  // arasaka_draw();
  oled_write_raw_P(logo_clean, frame_size);
  return false;
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     uint8_t layer = biton32(state);
//     switch (layer) {
//         case 0: // Bone (Linux)
//             rgblight_sethsv_noeeprom(RGB_GREEN);
//             break;
//         case 1: // Shifted Layer (Linux)
//             rgblight_sethsv_noeeprom(RGB_CYAN);
//             break;
//         case 2: // Bone (Mac)
//             rgblight_sethsv_noeeprom(RGB_RED);
//             break;
//         case 3: // Shifted (Mac)
//             rgblight_sethsv_noeeprom(RGB_ORANGE);
//             break;
//         case 4: // Utility
//             rgblight_sethsv_noeeprom(RGB_BLUE);
//             break;
//         case 5: // Utility
//             rgblight_sethsv_noeeprom(RGB_WHITE);
//             break;
//     }
//
//     return state;
// };
