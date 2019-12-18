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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;

/* Variables and functions */
 scalar_t__ LookupCat (int /*<<< orphan*/ ,char const**,int) ; 

const char *vlc_fourcc_GetDescription(int cat, vlc_fourcc_t fourcc)
{
    const char *ret;

    return LookupCat(fourcc, &ret, cat) ? ret : "";
}