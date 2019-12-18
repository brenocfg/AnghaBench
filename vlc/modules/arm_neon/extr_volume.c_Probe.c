#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {scalar_t__ format; int /*<<< orphan*/  amplify; } ;
typedef  TYPE_1__ audio_volume_t ;

/* Variables and functions */
 int /*<<< orphan*/  AmplifyFloat ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_CPU_ARM_NEON () ; 

__attribute__((used)) static int Probe(vlc_object_t *obj)
{
    audio_volume_t *volume = (audio_volume_t *)obj;

    if (!vlc_CPU_ARM_NEON())
        return VLC_EGENERIC;
    if (volume->format == VLC_CODEC_FL32)
        volume->amplify = AmplifyFloat;
    else
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}