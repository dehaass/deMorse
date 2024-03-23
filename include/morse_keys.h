#ifndef MORSE_KEYS_H
#define MORSE_KEYS_H

class MorseCode {
public:
    const int mode;
    const String morse;
    const uint8_t key_code;
    const uint8_t modifier_keys;
    //const char* comment;

    MorseCode(int mode, const String& morse, uint8_t key_code, uint8_t modifier_keys)
        : mode(mode), morse(morse), key_code(key_code), modifier_keys(modifier_keys) {}
};

// class SpecialCode {
//     public:
//         const int mode;
//         const String morse;
//         const String name;

//     SpecialCode(int mode, const String& morse, const String& name)
//         : mode(mode), morse(morse), name(name) {}
// };


// Define the global array of MorseCode objects
const MorseCode codes_lookup[] = {
{1, ".-", 0x04, 0b0010}, //KEY_A
{1, "-...", 0x05, 0b0000}, //KEY_B
{1, "-.-.", 0x06, 0b0000}, //KEY_C
{1, "-..", 0x07, 0b0000}, //KEY_D
{1, ".", 0x08, 0b0000}, //KEY_E
{1, "..-.", 0x09, 0b0000}, //KEY_F
{1, "--.", 0x0a, 0b0000}, //KEY_G
{1, "....", 0x0b, 0b0000}, //KEY_H
{1, "..", 0x0c, 0b0000}, //KEY_I
{1, ".---", 0x0d, 0b0000}, //KEY_J
{1, "-.-", 0x0e, 0b0000}, //KEY_K
{1, ".-..", 0x0f, 0b0000}, //KEY_L
{1, "--", 0x10, 0b0000}, //KEY_M
{1, "-.", 0x11, 0b0000}, //KEY_N
{1, "---", 0x12, 0b0000}, //KEY_O
{1, ".--.", 0x13, 0b0000}, //KEY_P
{1, "--.-", 0x14, 0b0000}, //KEY_Q
{1, ".-.", 0x15, 0b0000}, //KEY_R
{1, "...", 0x16, 0b0000}, //KEY_S
{1, "-", 0x17, 0b0000}, //KEY_T
{1, "..-", 0x18, 0b0000}, //KEY_U
{1, "...-", 0x19, 0b0000}, //KEY_V
{1, ".--", 0x1a, 0b0000}, //KEY_W
{1, "-..-", 0x1b, 0b0000}, //KEY_X
{1, "-.--", 0x1c, 0b0000}, //KEY_Y
{1, "--..", 0x1d, 0b0000}, //KEY_Z
{1, "-----", 0x27, 0b0000}, //KEY_0
{1, ".----", 0x1e, 0b0000}, //KEY_1
{1, "..---", 0x1f, 0b0000}, //KEY_2
{1, "...--", 0x20, 0b0000}, //KEY_3
{1, "....-", 0x21, 0b0000}, //KEY_4
{1, ".....", 0x22, 0b0000}, //KEY_5
{1, "-....", 0x23, 0b0000}, //KEY_6
{1, "--...", 0x24, 0b0000}, //KEY_7
{1, "---..", 0x25, 0b0000}, //KEY_8
{1, "----.", 0x26, 0b0000}, //KEY_9
{1, "..--", 0x2c, 0b0000}, //KEY_SPACE
{1, ".-.-", 0x28, 0b0000}, //KEY_ENTER
{1, "----", 0x2a, 0b0000}, //KEY_BACKSPACE
{1, ".-..-", 0x52, 0b0000}, //KEY_UP
{1, ".--..", 0x51, 0b0000}, //KEY_DOWN
{1, ".-.-..", 0x50, 0b0000}, //KEY_LEFT
{1, ".-.-.", 0x4f, 0b0000}, //KEY_RIGHT
{1, "---...-", 0x53, 0b0000}, //KEY_NUMLOCK
{1, "--.-..", 0x47, 0b0000}, //KEY_SCROLLLOCK
{1, "-----.", 0x39, 0b0000}, //KEY_CAPSLOCK
{1, "--....", 0x29, 0b0000}, //KEY_ESC
{1, "-.-..", 0x49, 0b0000}, //KEY_INSERT
{1, "-.--..", 0x4c, 0b0000} //KEY_DELETE
};


// const SpecialCode special_codes[] = {
// {1, "..-..", "repeat"},
// {1, "..-..-", "Hold/Rel"},
// {1, "...-.", "Toggle MODE"},
// {2, "...-.", "Toggle MODE"},
// {2, "-", "m up"},
// {2, "--", "m dwn"},
// {2, "...", "m rt"},
// {2, "..", "m lt"},
// {2, ".", "repeat"},
// {2, "...--", "m zoom"},
// {2, "..---", "double m"},
// {2, ".-", "mb left"},
// {2, ".--", "mb right"},
// {2, "..-", "mb double left"},
// {2, "..--", "mb double right"},
// {2, "-.", "mb click&hold left"},
// {2, "-..", "mb click&hold right"},
// {2, "-.-.", "Ctrl"},
// {2, "--.--", "Alt"},
// {2, "--...-", "Shft"}
// };

#endif // MORSECODE_H
