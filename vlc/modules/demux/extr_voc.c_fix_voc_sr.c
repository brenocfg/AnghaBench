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

/* Variables and functions */

__attribute__((used)) static unsigned int fix_voc_sr( unsigned int sr )
{
    switch( sr )
    {
        /*case 8000:
            return 8000;*/
        case 11111:
            return 11025;

        case 22222:
            return 22050;

        case 44444:
            return 44100;
    }
    return sr;
}