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
 int /*<<< orphan*/  VAProcFilterSharpening ; 
 int /*<<< orphan*/  vlc_sharpen_sigma_range ; 

__attribute__((used)) static int
OpenSharpenFilter(vlc_object_t * obj)
{
    return OpenBasicFilter(obj, VAProcFilterSharpening, "sharpen-sigma",
                           &vlc_sharpen_sigma_range);
}