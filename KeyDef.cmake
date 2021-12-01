# KeyCode Definitions

# Alphabet
add_compile_definitions(
        KEYBOARD_A=0x04  # Keyboard a and A
        KEYBOARD_B=0x05  # Keyboard b and B
        KEYBOARD_C=0x06  # Keyboard c and C
        KEYBOARD_D=0x07  # Keyboard d and D
        KEYBOARD_E=0x08  # Keyboard e and E
        KEYBOARD_F=0x09  # Keyboard f and F
        KEYBOARD_G=0x0A  # Keyboard g and G
        KEYBOARD_H=0x0B  # Keyboard h and H
        KEYBOARD_I=0x0C  # Keyboard i and I
        KEYBOARD_J=0x0D  # Keyboard j and J
        KEYBOARD_K=0x0E  # Keyboard k and K
        KEYBOARD_L=0x0F  # Keyboard l and L
        KEYBOARD_M=0x10  # Keyboard m and M
        KEYBOARD_N=0x11  # Keyboard n and N
        KEYBOARD_O=0x12  # Keyboard o and O
        KEYBOARD_P=0x13  # Keyboard p and P
        KEYBOARD_Q=0x14  # Keyboard q and Q
        KEYBOARD_R=0x15  # Keyboard r and R
        KEYBOARD_S=0x16  # Keyboard s and S
        KEYBOARD_T=0x17  # Keyboard t and T
        KEYBOARD_U=0x18  # Keyboard u and U
        KEYBOARD_V=0x19  # Keyboard v and V
        KEYBOARD_W=0x1A  # Keyboard w and W
        KEYBOARD_X=0x1B  # Keyboard x and X
        KEYBOARD_Y=0x1C  # Keyboard y and Y
        KEYBOARD_z=0x1D  # Keyboard z and Z
        KEYBOARD_1=0x1E  # Keyboard 1 and !
        KEYBOARD_2=0x1F  # Keyboard 2 and @
        KEYBOARD_3=0x20  # Keyboard 3 and #
        KEYBOARD_4=0x21  # Keyboard 4 and $
        KEYBOARD_5=0x22  # Keyboard 5 and %
        KEYBOARD_6=0x23  # Keyboard 6 and ^
        KEYBOARD_7=0x24  # Keyboard 7 and &
        KEYBOARD_8=0x25  # Keyboard 8 and *
        KEYBOARD_9=0x26  # Keyboard 9 and (
        KEYBOARD_0=0x27  # Keyboard 0 and )
)

# Basic Functions
add_compile_definitions(
        KEYBOARD_Enter=0x28  # Keyboard ENTER
        KEYBOARD_Esc=0x29  # Keyboard ESCAPE
        KEYBOARD_Backspace=0x2A  # Keyboard Backspace
        KEYBOARD_Tab=0x2B  # Keyboard Tab
        KEYBOARD_Space=0x2C  # Keyboard SpaceBar
        KEYBOARD_Sub=0x2D  # Keyboard - and _(underscore)
        KEYBOARD_Equal=0x2E  # Keyboard = and +
        KEYBOARD_LeftBracket=0x2F  # Keyboard [ and {
        KEYBOARD_RightBracket=0x30  # Keyboard ] and }
        KEYBOARD_BackSlash=0x31  # Keyboard \ and |
        KEYBOARD_Semicolon=0x33  # Keyboard ; and :
        KEYBOARD_DanYinHao=0x34  # Keyboard ‘ and “
        KEYBOARD_BoLangXian=0x35  # Keyboard `(Grave Accent) and ~(Tilde)
        KEYBOARD_Comma=0x36  # Keyboard, and <
        KEYBOARD_Dot=0x37  # Keyboard . and >
        KEYBOARD_Slash=0x38  # Keyboard / and ?
        KEYBOARD_CapsLock=0x39  # Keyboard Caps Lock
)

# Basic Macros
add_compile_definitions(
        KEYBOARD_F1=0x3A  # Keyboard F1
        KEYBOARD_F2=0x3B  # Keyboard F2
        KEYBOARD_F3=0x3C  # Keyboard F3
        KEYBOARD_F4=0x3D  # Keyboard F4
        KEYBOARD_F5=0x3E  # Keyboard F5
        KEYBOARD_F6=0x3F  # Keyboard F6
        KEYBOARD_F7=0x40  # Keyboard F7
        KEYBOARD_F8=0x41  # Keyboard F8
        KEYBOARD_F9=0x42  # Keyboard F9
        KEYBOARD_F10=0x43  # Keyboard F10
        KEYBOARD_F11=0x44  # Keyboard F11
        KEYBOARD_F12=0x45  # Keyboard F12
)

# Controls
add_compile_definitions(
        KEYBOARD_PrintScreen=0x46  # Keyboard PrintScreen
        KEYBOARD_ScrollLock=0x47  # Keyboard Scroll Lock
        KEYBOARD_Pause=0x48  # Keyboard Pause
        KEYBOARD_Insert=0x49  # Keyboard Insert
        KEYBOARD_Home=0x4A  # Keyboard Home
        KEYBOARD_PageUp=0x4B  # Keyboard PageUp
        KEYBOARD_Delete=0x4C  # Keyboard Delete
        KEYBOARD_End=0x4D  # Keyboard End
        KEYBOARD_PageDown=0x4E  # Keyboard PageDown
)

# Directions
add_compile_definitions(
        KEYBOARD_Right=0x4F  # Keyboard RightArrow
        KEYBOARD_Left=0x50  # Keyboard LeftArrow
        KEYBOARD_Down=0x51  # Keyboard DownArrow
        KEYBOARD_Up=0x52  # Keyboard UpArrow
)

# Keypads
add_compile_definitions(
        KEYPAD_NumLock=0x53  # Keypad Num Lock and Clear
        KEYPAD_Divide=0x54  # Keypad /
        KEYPAD_Multiple=0x55  # Keypad *
        KEYPAD_Sub=0x56  # Keypad -
        KEYPAD_Plus=0x57  # Keypad +
        KEYPAD_Enter=0x58  # Keypad ENTER
        KEYPAD_1=0x59  # Keypad 1 and End
        KEYPAD_2=0x5A  # Keypad 2 and Down Arrow
        KEYPAD_3=0x5B  # Keypad 3 and PageDn
        KEYPAD_4=0x5C  # Keypad 4 and Left Arrow
        KEYPAD_5=0x5D  # Keypad 5
        KEYPAD_6=0x5E  # Keypad 6 and Right Arrow
        KEYPAD_7=0x5F  # Keypad 7 and Home
        KEYPAD_8=0x60  # Keypad 8 and Up Arrow
        KEYPAD_9=0x61  # Keypad 9 and PageUp
        KEYPAD_0=0x62  # Keypad 0 and Insert
        KEYPAD_Dot=0x63  # Keypad . and Delete
)

# Extra Functions
add_compile_definitions(
        KEYBOARD_Application=0x65  # Keyboard Application
        KEYBOARD_F13=0x68  # Keyboard F13
        KEYBOARD_F14=0x69  # Keyboard F14
        KEYBOARD_F15=0x6A  # Keyboard F15
        KEYBOARD_F16=0x6B  # Keyboard F16
        KEYBOARD_F17=0x6C  # Keyboard F17
        KEYBOARD_F18=0x6D  # Keyboard F18
        KEYBOARD_F19=0x6E  # Keyboard F19
        KEYBOARD_F20=0x6F  # Keyboard F20
        KEYBOARD_F21=0x70  # Keyboard F21
        KEYBOARD_F22=0x71  # Keyboard F22
        KEYBOARD_F23=0x72  # Keyboard F23
        KEYBOARD_F24=0x73  # Keyboard F24
)

# Basic Auxiliaries
add_compile_definitions(
        KEYBOARD_LeftControl=0xE0
        KEYBOARD_LeftShift=0xE1
        KEYBOARD_LeftAlt=0xE2
        KEYBOARD_LeftGUI=0xE3
        KEYBOARD_RightControl=0xE4
        KEYBOARD_RightShift=0xE5
        KEYBOARD_RightAlt=0xE6
        KEYBOARD_RightGUI=0xE7
)

# Volume Controls
add_compile_definitions(
        KEYBOARD_Mute=0x80
        KEYBOARD_VolumeUp=0x81
        KEYBOARD_VolumeDown=0x82
)