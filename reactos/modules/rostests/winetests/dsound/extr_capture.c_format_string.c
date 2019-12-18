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
struct TYPE_3__ {int nSamplesPerSec; int wBitsPerSample; int nChannels; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_1__ WAVEFORMATEX ;

/* Variables and functions */
 char* get_format_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,char*) ; 

const char * format_string(const WAVEFORMATEX* wfx)
{
    static char str[64];

    sprintf(str, "%5dx%2dx%d %s",
	wfx->nSamplesPerSec, wfx->wBitsPerSample, wfx->nChannels,
        get_format_str(wfx->wFormatTag));

    return str;
}