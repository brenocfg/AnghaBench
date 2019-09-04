#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hFile; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int /*<<< orphan*/  HPSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MCIERR_INVALID_FILE ; 
 int /*<<< orphan*/  WARN (char*,TYPE_1__*) ; 
 long mmioRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DWORD MIDI_mciReadByte(WINE_MCIMIDI* wmm, BYTE *lpbyt)
{
    DWORD	ret = 0;

    if (mmioRead(wmm->hFile, (HPSTR)lpbyt, sizeof(BYTE)) != (long)sizeof(BYTE)) {
	WARN("Error reading wmm=%p\n", wmm);
	ret = MCIERR_INVALID_FILE;
    }

    return ret;
}