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
typedef  int DWORD ;

/* Variables and functions */
#define  MIXERLINE_TARGETTYPE_AUX 133 
#define  MIXERLINE_TARGETTYPE_MIDIIN 132 
#define  MIXERLINE_TARGETTYPE_MIDIOUT 131 
#define  MIXERLINE_TARGETTYPE_UNDEFINED 130 
#define  MIXERLINE_TARGETTYPE_WAVEIN 129 
#define  MIXERLINE_TARGETTYPE_WAVEOUT 128 

__attribute__((used)) static const char * target_type(DWORD dwType)
{
#define TYPE_TO_STR(x) case x: return #x
    switch (dwType) {
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_UNDEFINED);
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_WAVEOUT);
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_WAVEIN);
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_MIDIOUT);
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_MIDIIN);
    TYPE_TO_STR(MIXERLINE_TARGETTYPE_AUX);
    }
#undef TYPE_TO_STR
    return "UNKNOWN";
}