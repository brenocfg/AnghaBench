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
typedef  int UINT ;

/* Variables and functions */
#define  TIME_BYTES 133 
#define  TIME_MIDI 132 
#define  TIME_MS 131 
#define  TIME_SAMPLES 130 
#define  TIME_SMPTE 129 
#define  TIME_TICKS 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char * wave_time_format(UINT type)
{
    static char msg[32];
#define TIME_FORMAT(f) case f: return #f
    switch (type) {
    TIME_FORMAT(TIME_MS);
    TIME_FORMAT(TIME_SAMPLES);
    TIME_FORMAT(TIME_BYTES);
    TIME_FORMAT(TIME_SMPTE);
    TIME_FORMAT(TIME_MIDI);
    TIME_FORMAT(TIME_TICKS);
    }
#undef TIME_FORMAT
    sprintf(msg, "Unknown(0x%04x)", type);
    return msg;
}