// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum mitosis_layers {
	_WORKMAN,
	_SYM,
	_NUM,
    _FUN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_WORKMAN] = { /* Workman layout */
{ KC_Q,    KC_D,    KC_R,    KC_W,     KC_B,                           KC_J,    KC_F,     KC_U,    KC_P,    KC_QUOT },
{ LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LSFT_T(KC_T), KC_G,        KC_Y,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_O), RGUI_T(KC_I) },
{ KC_Z,    KC_X,    KC_M,    KC_C,     KC_V,                           KC_K,    KC_L,     KC_COMM, KC_DOT,  KC_SLSH },
{ XXXXXXX, XXXXXXX, KC_CAPS, KC_ESC,   KC_TAB,                         KC_TAB,  KC_APP,   KC_DEL,  XXXXXXX, XXXXXXX },
{ XXXXXXX, XXXXXXX, TT(_NUM), TT(_SYM), KC_ENT,                        KC_SPC,  TT(_FUN), KC_BSPC, XXXXXXX, XXXXXXX }
},

[_SYM] = {
{ KC_TILD, KC_HASH, KC_ASTR, KC_LBRC, KC_RBRC,        KC_BSLS, KC_EXLM, KC_GRV,  KC_DQT,  _______ },
{ KC_DLR,  KC_PIPE, KC_EQL,  KC_LPRN, KC_RPRN,        KC_DOT,  KC_COLN, KC_MINS, KC_UNDS, KC_PLUS },
{ KC_CIRC, KC_PERC, KC_AT,   KC_LCBR, KC_RCBR,        KC_AMPR, KC_SCLN, KC_LT,   KC_GT,   KC_QUES },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX }
},

[_NUM] = {
{ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        KC_EQL,  KC_7,    KC_8,    KC_9,    KC_MINS },
{ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_DLR,         KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PLUS },
{ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PERC,        KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        KC_0,    _______, _______, _______, XXXXXXX }
},

[_FUN] = {
{ KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MNXT,        KC_VOLU, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX },
{ KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_MPLY,        KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX },
{ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_MPRV,        KC_VOLD, KC_HOME, XXXXXXX, KC_END,  XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX }
}

};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
//    debug_enable=true;
//    debug_matrix=true;
//    debug_keyboard=true;
    //debug_mouse=true;
}

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state); // get the current layer
    
    switch (layer) {
        case _WORKMAN:
            set_led_off;
            break;
        case _SYM:
            set_led_red;
            break;
        case _NUM:
            set_led_blue;
            break;
        case _FUN:
            set_led_green;
            break;
        default:
            break;
  }
};