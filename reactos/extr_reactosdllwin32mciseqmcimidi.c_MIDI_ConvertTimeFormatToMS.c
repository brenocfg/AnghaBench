#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwMciTimeFormat; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int DWORD ;

/* Variables and functions */
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int) ; 
#define  MCI_FORMAT_MILLISECONDS 131 
#define  MCI_FORMAT_SMPTE_24 130 
#define  MCI_FORMAT_SMPTE_25 129 
#define  MCI_FORMAT_SMPTE_30 128 
 int TIME_MS_IN_ONE_HOUR ; 
 int TIME_MS_IN_ONE_MINUTE ; 
 int TIME_MS_IN_ONE_SECOND ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static	DWORD	MIDI_ConvertTimeFormatToMS(WINE_MCIMIDI* wmm, DWORD val)
{
    DWORD	ret = 0;

    switch (wmm->dwMciTimeFormat) {
    case MCI_FORMAT_MILLISECONDS:
	ret = val;
	break;
    case MCI_FORMAT_SMPTE_24:
	ret =
	    (HIBYTE(HIWORD(val)) * 125) / 3 +             LOBYTE(HIWORD(val)) * TIME_MS_IN_ONE_SECOND +
	    HIBYTE(LOWORD(val)) * TIME_MS_IN_ONE_MINUTE + LOBYTE(LOWORD(val)) * TIME_MS_IN_ONE_HOUR;
	break;
    case MCI_FORMAT_SMPTE_25:
	ret =
	    HIBYTE(HIWORD(val)) * 40 + 		  	  LOBYTE(HIWORD(val)) * TIME_MS_IN_ONE_SECOND +
	    HIBYTE(LOWORD(val)) * TIME_MS_IN_ONE_MINUTE + LOBYTE(LOWORD(val)) * TIME_MS_IN_ONE_HOUR;
	break;
    case MCI_FORMAT_SMPTE_30:
	ret =
	    (HIBYTE(HIWORD(val)) * 100) / 3 + 		  LOBYTE(HIWORD(val)) * TIME_MS_IN_ONE_SECOND +
	    HIBYTE(LOWORD(val)) * TIME_MS_IN_ONE_MINUTE + LOBYTE(LOWORD(val)) * TIME_MS_IN_ONE_HOUR;
	break;
    default:
	WARN("Bad time format %u!\n", wmm->dwMciTimeFormat);
    }
    /*
      TRACE("val=%u=0x%08x [tf=%u] => ret=%u\n", val, val, wmm->dwMciTimeFormat, ret);
    */
    return ret;
}