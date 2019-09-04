#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwMicroSecPerFrame; } ;
struct TYPE_5__ {int dwMciTimeFormat; TYPE_1__ mah; } ;
typedef  TYPE_2__ WINE_MCIAVI ;
typedef  scalar_t__* LPDWORD ;
typedef  int DWORD ;

/* Variables and functions */
#define  MCI_FORMAT_FRAMES 129 
#define  MCI_FORMAT_MILLISECONDS 128 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static DWORD MCIAVI_ConvertFrameToTimeFormat(WINE_MCIAVI* wma, DWORD val, LPDWORD lpRet)
{
    DWORD	   ret = 0;

    switch (wma->dwMciTimeFormat) {
    case MCI_FORMAT_MILLISECONDS:
        ret = (val * wma->mah.dwMicroSecPerFrame) / 1000;
	break;
    case MCI_FORMAT_FRAMES:
	ret = val;
	break;
    default:
	WARN("Bad time format %u!\n", wma->dwMciTimeFormat);
    }
    TRACE("val=%u=0x%08x [tf=%u] => ret=%u\n", val, val, wma->dwMciTimeFormat, ret);
    *lpRet = 0;
    return ret;
}