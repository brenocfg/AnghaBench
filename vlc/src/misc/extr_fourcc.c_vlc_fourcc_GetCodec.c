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
typedef  scalar_t__ vlc_fourcc_t ;

/* Variables and functions */
 scalar_t__ LookupCat (scalar_t__,int /*<<< orphan*/ *,int) ; 

vlc_fourcc_t vlc_fourcc_GetCodec(int cat, vlc_fourcc_t fourcc)
{
    vlc_fourcc_t codec = LookupCat(fourcc, NULL, cat);
    return codec ? codec : fourcc;
}