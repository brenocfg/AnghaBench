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
typedef  int /*<<< orphan*/  libvlc_module_description_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/ * module_description_list_get (int /*<<< orphan*/ *,char*) ; 

libvlc_module_description_t *libvlc_video_filter_list_get( libvlc_instance_t *p_instance )
{
    return module_description_list_get( p_instance, "video filter" );
}