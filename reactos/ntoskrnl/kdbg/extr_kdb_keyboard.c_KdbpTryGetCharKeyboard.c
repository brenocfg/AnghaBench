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
typedef  int byte_t ;
typedef  scalar_t__ ULONG ;
typedef  int* PULONG ;
typedef  char CHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int KBD_STAT_OBF ; 
 int kbd_read_input () ; 
 int kbd_read_status () ; 
 char** keyb_layout ; 

CHAR
KdbpTryGetCharKeyboard(PULONG ScanCode, ULONG Retry)
{
    static byte_t last_key = 0;
    static byte_t shift = 0;
    char c;
    BOOLEAN KeepRetrying = (Retry == 0);

    while (KeepRetrying || Retry-- > 0)
    {
        while (kbd_read_status() & KBD_STAT_OBF)
        {
            byte_t scancode;

            scancode = kbd_read_input();

            /* check for SHIFT-keys */
            if (((scancode & 0x7F) == 42) || ((scancode & 0x7F) == 54))
            {
                shift = !(scancode & 0x80);
                continue;
            }

            /* ignore all other RELEASED-codes */
            if (scancode & 0x80)
            {
                last_key = 0;
            }
            else if (last_key != scancode)
            {
                //printf("kbd: %d, %d, %c\n", scancode, last_key, keyb_layout[shift][scancode]);
                last_key = scancode;
                c = keyb_layout[shift][scancode];
                *ScanCode = scancode;

                if (c > 0)
                    return c;
            }
        }
    }

    return -1;
}