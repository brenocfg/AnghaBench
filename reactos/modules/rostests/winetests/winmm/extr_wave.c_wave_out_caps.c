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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAVECAPS_LRVOLUME ; 
 int /*<<< orphan*/  WAVECAPS_PITCH ; 
 int /*<<< orphan*/  WAVECAPS_PLAYBACKRATE ; 
 int /*<<< orphan*/  WAVECAPS_SAMPLEACCURATE ; 
 int /*<<< orphan*/  WAVECAPS_SYNC ; 
 int /*<<< orphan*/  WAVECAPS_VOLUME ; 

__attribute__((used)) static const char * wave_out_caps(DWORD dwSupport)
{
#define ADD_FLAG(f) if (dwSupport & f) strcat(msg, " " #f)
    static char msg[256];
    msg[0] = 0;

    ADD_FLAG(WAVECAPS_PITCH);
    ADD_FLAG(WAVECAPS_PLAYBACKRATE);
    ADD_FLAG(WAVECAPS_VOLUME);
    ADD_FLAG(WAVECAPS_LRVOLUME);
    ADD_FLAG(WAVECAPS_SYNC);
    ADD_FLAG(WAVECAPS_SAMPLEACCURATE);

    return msg[0] ? msg + 1 : "";
#undef ADD_FLAG
}