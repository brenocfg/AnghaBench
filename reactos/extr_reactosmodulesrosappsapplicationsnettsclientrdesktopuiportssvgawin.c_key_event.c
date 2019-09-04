#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int KBD_FLAG_EXT ; 
 int /*<<< orphan*/  LED_CAP ; 
 int /*<<< orphan*/  LED_NUM ; 
 int /*<<< orphan*/  LED_SCR ; 
 int MOUSE_FLAG_BUTTON4 ; 
 int MOUSE_FLAG_BUTTON5 ; 
 int MOUSE_FLAG_DOWN ; 
 int /*<<< orphan*/  RDP_INPUT_MOUSE ; 
 int /*<<< orphan*/  RDP_INPUT_SCANCODE ; 
 int RDP_KEYPRESS ; 
 int RDP_KEYRELEASE ; 
#define  SCANCODE_BREAK 146 
 int SCANCODE_CAPSLOCK ; 
#define  SCANCODE_CURSORBLOCKDOWN 145 
#define  SCANCODE_CURSORBLOCKLEFT 144 
#define  SCANCODE_CURSORBLOCKRIGHT 143 
#define  SCANCODE_CURSORBLOCKUP 142 
#define  SCANCODE_END 141 
#define  SCANCODE_HOME 140 
#define  SCANCODE_INSERT 139 
#define  SCANCODE_KEYPADDIVIDE 138 
#define  SCANCODE_KEYPADENTER 137 
#define  SCANCODE_LEFTWIN 136 
 int SCANCODE_NUMLOCK ; 
#define  SCANCODE_PAGEDOWN 135 
#define  SCANCODE_PAGEUP 134 
#define  SCANCODE_PRINTSCREEN 133 
#define  SCANCODE_REMOVE 132 
#define  SCANCODE_RIGHTALT 131 
#define  SCANCODE_RIGHTCONTROL 130 
#define  SCANCODE_RIGHTWIN 129 
#define  SCANCODE_SCROLLLOCK 128 
 int /*<<< orphan*/  UpAndRunning ; 
 int capslock ; 
 int mouse_getx () ; 
 int /*<<< orphan*/  mouse_gety () ; 
 int numlock ; 
 int /*<<< orphan*/  rdp_send_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int scrolllock ; 
 int /*<<< orphan*/  setled (int /*<<< orphan*/ ,int) ; 

void key_event(int scancode, int pressed)
{
  int rdpkey;
  int ext;

  if (!UpAndRunning)
    return;
  rdpkey = scancode;
  ext = 0;

  // Keyboard LEDS
  if ((scancode == SCANCODE_CAPSLOCK) && pressed)
  {
     capslock = !capslock;
     setled(LED_CAP, capslock);
  }
  if ((scancode == SCANCODE_SCROLLLOCK) && pressed)
  {
     scrolllock = !scrolllock;
     setled(LED_SCR, scrolllock);
  }

  if ((scancode == SCANCODE_NUMLOCK) && pressed)
  {
     numlock = !numlock;
     setled(LED_NUM, numlock);
  }

  switch (scancode)
  {
    case SCANCODE_CURSORBLOCKUP:    rdpkey = 0xc8; ext = KBD_FLAG_EXT; break; // up arrow
    case SCANCODE_CURSORBLOCKDOWN:  rdpkey = 0xd0; ext = KBD_FLAG_EXT; break; // down arrow
    case SCANCODE_CURSORBLOCKRIGHT: rdpkey = 0xcd; ext = KBD_FLAG_EXT; break; // right arrow
    case SCANCODE_CURSORBLOCKLEFT:  rdpkey = 0xcb; ext = KBD_FLAG_EXT; break; // left arrow
    case SCANCODE_PAGEDOWN:         rdpkey = 0xd1; ext = KBD_FLAG_EXT; break; // page down
    case SCANCODE_PAGEUP:           rdpkey = 0xc9; ext = KBD_FLAG_EXT; break; // page up
    case SCANCODE_HOME:             rdpkey = 0xc7; ext = KBD_FLAG_EXT; break; // home
    case SCANCODE_END:              rdpkey = 0xcf; ext = KBD_FLAG_EXT; break; // end
    case SCANCODE_INSERT:           rdpkey = 0xd2; ext = KBD_FLAG_EXT; break; // insert
    case SCANCODE_REMOVE:           rdpkey = 0xd3; ext = KBD_FLAG_EXT; break; // delete
    case SCANCODE_KEYPADDIVIDE:     rdpkey = 0x35; break; // /
    case SCANCODE_KEYPADENTER:      rdpkey = 0x1c; break; // enter
    case SCANCODE_RIGHTCONTROL:     rdpkey = 0x1d; break; // right ctrl
    case SCANCODE_RIGHTALT:         rdpkey = 0x38; break; // right alt
    case SCANCODE_LEFTWIN:          rdpkey = 0x5b; ext = KBD_FLAG_EXT; break; // left win
    case SCANCODE_RIGHTWIN:         rdpkey = 0x5c; ext = KBD_FLAG_EXT; break; // right win
    case 127:                       rdpkey = 0x5d; ext = KBD_FLAG_EXT; break; // menu key
    case SCANCODE_PRINTSCREEN:      rdpkey = 0x37; ext = KBD_FLAG_EXT; break; // print screen
    case SCANCODE_BREAK:            //rdpkey = 0; break; // break
    {
      if (pressed)
      {
        ext = KBD_FLAG_EXT;
        rdp_send_input(0, RDP_INPUT_SCANCODE, RDP_KEYPRESS | ext, 0x46, 0);
        rdp_send_input(0, RDP_INPUT_SCANCODE, RDP_KEYPRESS | ext, 0xc6, 0);
      }
      rdpkey = 0;
    }
    case SCANCODE_SCROLLLOCK:       rdpkey = 0x46; break; // scroll lock
    case 112: // mouse down
    {
      rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_DOWN | MOUSE_FLAG_BUTTON4,
                     mouse_getx(), mouse_gety());
      return;
    }
    case 113: // mouse up
    {
      rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_DOWN | MOUSE_FLAG_BUTTON5,
                     mouse_getx(), mouse_gety());
      return;
    }
  }
//  printf("%d %d\n", scancode, pressed);
  if (pressed)
    rdp_send_input(0, RDP_INPUT_SCANCODE, RDP_KEYPRESS | ext, rdpkey, 0);
  else
    rdp_send_input(0, RDP_INPUT_SCANCODE, RDP_KEYRELEASE | ext, rdpkey, 0);


}