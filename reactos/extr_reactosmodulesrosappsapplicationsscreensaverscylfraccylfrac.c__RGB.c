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

float _RGB(float H, float M1, float M2)
{
    if(H < 0.0) H += 360.0;
        else if(H > 360.0) H -= 360.0;
    if(H < 60) return M1 + (M2 - M1) * H / 60.0;
    if((H >= 60 )&&(H < 180)) return M2;
    if((H >= 180)&&(H < 240)) return M1 + (M2 - M1)*(240 - H) / 60.0;
    return M1;
}