// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "mitosis.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum mitosis_layers {
	_WORKMAN,
	_SHIFTED,
	_FUNCTION,
    _FUNCSHIFT,
    _MOUSE
};

enum {
    FN = 0,
    SH
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_WORKMAN] = { /* Workman layout */
{ KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,           KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN },
{ KC_A,    KC_S,    KC_H,    KC_T,    KC_G,           KC_Y,    KC_N,    KC_E,    KC_O,    KC_I    },
{ KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,           KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH },
{ XXXXXXX, KC_HOME, KC_LGUI, KC_TAB,  KC_CAPS,        KC_ESC,  KC_BSPC, KC_DEL,  KC_PGUP, XXXXXXX },
{ XXXXXXX, KC_END,  KC_LCTL, KC_ENT,  TD(FN),         TD(SH),  KC_SPC,  KC_LALT, KC_PGDN, XXXXXXX }
},

[_SHIFTED] = { /* Shifted Layer, layered so that tri_layer can be used, or selectively
                                 able to modify individual key's shifted behavior */
{ _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______ },
{ _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______ },
{ _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______ },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX }
},

[_FUNCTION] = { /* Function Layer */
{ KC_GRV,  KC_AMPR, KC_ASTR, _______, KC_VOLU,        KC_MINS, KC_7,    KC_8,    KC_9,    KC_LCBR },
{ KC_QUOT, KC_DLR,  KC_PERC, KC_CIRC, KC_MUTE,        KC_LBRC, KC_4,    KC_5,    KC_6,    KC_LPRN },
{ _______, KC_EXLM, KC_AT,   KC_HASH, KC_VOLD,        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_BSLS },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, KC_INS,  KC_CAPS, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, KC_0,    KC_MENU, KC_PSCR, XXXXXXX }
},

[_FUNCSHIFT] = { /* Function Shifted Layer */
{ KC_TILDE, _______, KC_UP,  _______, KC_F10,         _______, KC_F7,   KC_F8,   KC_F9,   KC_RCBR },
{ _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_F11,         KC_RBRC, KC_F4,   KC_F5,   KC_F6,   KC_RPRN },
{ _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_F12,         _______, KC_F1,   KC_F2,   KC_F3,   _______ },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX },
{ XXXXXXX, _______, _______, _______, _______,        _______, _______, _______, _______, XXXXXXX }
},

[_MOUSE] = { /* Mouse layer */
{ XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX },
{ XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,        XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX },
{ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX },
{ XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
{ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX }
}

};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	uint8_t layer;
    layer = biton32(layer_state);  // get the current layer

    //FUNCSHIFT has been shifted by the SHIFT handling, some keys need to be excluded
    if (layer == _FUNCSHIFT) {
        //F1-F12 should be sent as unshifted keycodes, 
        //and ] needs to be unshifted or it is sent as }
        //arrow keys as well
        if ( (keycode >= KC_F1 && keycode <= KC_F12)
            || keycode == KC_RBRC
            || keycode == KC_UP || keycode == KC_DOWN || keycode == KC_LEFT || keycode == KC_RGHT ) {
                if (record->event.pressed) {
                    unregister_mods(MOD_LSFT);
                } else {
                    register_mods(MOD_LSFT);
                }
        }
    }

    return true;
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    
    switch (layer) {
        case _WORKMAN:
            set_led_off;
            break;
        case _FUNCTION:
            set_led_red;
            break;
        case _SHIFTED:
            set_led_blue;
            break;
        case _FUNCSHIFT:
            set_led_magenta;
            break;
        case _MOUSE:
            set_led_green;
        default:
            break;
  }

    // TODO determine way to show caps lock reliably
    //if(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
    //  set_led_white;
};

bool is_fn_held;

void fn_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->pressed) {
        layer_on(_FUNCTION);
        is_fn_held = true;
    }
    if(state->count == 1 && !state->pressed) {
        layer_off(_FUNCTION);
        is_fn_held = false;
    }
    if(state->count == 2) {
        layer_on(_FUNCTION);
    }

    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
}

void fn_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    if(is_fn_held) {
        layer_off(_FUNCTION);
        is_fn_held = false;
    }

    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
}



bool is_shift_held;

void shift_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->pressed) {
        layer_on(_SHIFTED);
        register_code(KC_LSFT);
        is_shift_held = true;
    }
    if(state->count == 1 && !state->pressed) {
        layer_off(_SHIFTED);
        unregister_code(KC_LSFT);
        is_shift_held = false;
    }
    if(state->count == 2) {
        register_code(KC_LSFT);
        layer_on(_SHIFTED);
    }

    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
}

void shift_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    if(is_shift_held) {
        layer_off(_SHIFTED);
        unregister_code(KC_LSFT);
        is_shift_held = false;
    }

    update_tri_layer(_FUNCTION, _SHIFTED, _FUNCSHIFT);
}

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [FN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_dance_finished, fn_dance_reset),
    [SH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_dance_finished, shift_dance_reset)
};