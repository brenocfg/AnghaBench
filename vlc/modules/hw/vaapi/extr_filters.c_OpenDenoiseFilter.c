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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int OpenBasicFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VAProcFilterNoiseReduction ; 
 int /*<<< orphan*/  vlc_denoise_sigma_range ; 

__attribute__((used)) static int
OpenDenoiseFilter(vlc_object_t * obj)
{
    return OpenBasicFilter(obj, VAProcFilterNoiseReduction, "denoise-sigma",
                           &vlc_denoise_sigma_range);
}