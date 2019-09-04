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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WINE_MCIMIDI ;
typedef  int* LPDWORD ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ MIDI_mciReadByte (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static WORD MIDI_mciReadVaryLen(WINE_MCIMIDI* wmm, LPDWORD lpdw)
{
    BYTE	byte;
    DWORD	value = 0;
    WORD	len = 0;

    do {
	if (MIDI_mciReadByte(wmm, &byte) != 0) {
	    return 0;
	}
	value = (value << 7) + (byte & 0x7F);
	len++;
    } while (byte & 0x80);
    *lpdw = value;
    return len;
}