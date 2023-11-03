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
    // XC_ESC,
    // KL_TAB
};

const uint16_t PROGMEM ab_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
// const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM uio_combo[] = {KC_U, KC_I, KC_O, COMBO_END};
// const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM as_combo[] = {KC_A, KC_S, COMBO_END};

combo_t key_combos[] = {
    [SD_GUI] = COMBO(ab_combo, KC_LGUI),
    [HJ_FULL] = COMBO(hj_combo, LALT(KC_ENT)),
    // [HJ_FULL] = COMBO(hj_combo, KC_LGUI),
    [UIO_CAPS] = COMBO(uio_combo, KC_CAPS),
//     [XC_ESC] = COMBO(xc_combo, KC_ESC),
//     [KL_TAB] = COMBO(df_combo, KC_TAB),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_LEFT_BRACKET,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  MO(1),  KC_SPC,     KC_LSFT,   MO(2), MO(4)
                                      // `--------------------------'  `--------------------------'
                                          // KC_LGUI,   KC_LALT,  KC_SPC,     KC_LSFT,   KC_RALT, MO(4)
  ),
    // nav
    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ALTTAB,  LALT(KC_Q),   LALT(KC_W), LALT(KC_E), KC_UP,  LALT(KC_T),                      KC_RIGHT, LCTL(KC_U), LCTL(KC_I), LCTL(KC_O),  LALT(KC_P), LALT(KC_LEFT_BRACKET),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LCTL, ALTTAB, CTAB, KC_TAB, XXXXXXX,                      KC_LEFT, KC_BSPC, LCTL(KC_K), KC_DOWN, LCTL(KC_SCLN),LALT(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, MO(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      LALT(KC_N), KC_ENT,  LCTL(KC_COMM), XXXXXXX, XXXXXXX, XXXXXXX,
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
                                          KC_ESC,   KC_ESC,  LALT(KC_SPC),     KC_ENT, _______, KC_RALT
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
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                         KC_8,    KC_0,    KC_2,    KC_4,    KC_6, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO(3),  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
                                      //`--------------------------'  `--------------------------'
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
};

bool should_process_keypress(void) { return true; }

bool is_alt_tab_active = false;
bool is_win_active = false;
bool is_ctrl_tab_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
