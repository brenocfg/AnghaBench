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

__attribute__((used)) static float iec_scale(float dB)
{
    if (dB < -70.0f)
        return 0.0f;
    if (dB < -60.0f)
        return (dB + 70.0f) * 0.0025f;
    if (dB < -50.0f)
        return (dB + 60.0f) * 0.005f + 0.025f;
    if (dB < -40.0f)
        return (dB + 50.0f) * 0.0075f + 0.075f;
    if (dB < -30.0f)
        return (dB + 40.0f) * 0.015f + 0.15f;
    if (dB < -20.0f)
        return (dB + 30.0f) * 0.02f + 0.3f;
    if (dB < -0.001f || dB > 0.001f)  /* if (dB < 0.0f) */
        return (dB + 20.0f) * 0.025f + 0.5f;
    return 1.0f;
}