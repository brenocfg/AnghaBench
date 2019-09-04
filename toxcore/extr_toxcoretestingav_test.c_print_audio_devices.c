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
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ PaDeviceInfo ;

/* Variables and functions */
 int Pa_GetDeviceCount () ; 
 TYPE_1__* Pa_GetDeviceInfo (int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

int print_audio_devices()
{
    int i = 0;

    for (i = 0; i < Pa_GetDeviceCount(); ++i) {
        const PaDeviceInfo *info = Pa_GetDeviceInfo(i);

        if (info)
            printf("%d) %s\n", i, info->name);
    }

    return 0;
}