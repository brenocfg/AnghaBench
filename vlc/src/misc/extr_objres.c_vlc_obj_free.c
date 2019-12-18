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
 int /*<<< orphan*/  ptrcmp ; 
 int /*<<< orphan*/  vlc_objres_remove (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

void vlc_obj_free(vlc_object_t *obj, void *ptr)
{
    vlc_objres_remove(obj, ptr, ptrcmp);
}