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
struct vaapi_instance {int /*<<< orphan*/ * native; int /*<<< orphan*/  (* native_destroy_cb ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  dpy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vaapi_instance*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaTerminate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vaapi_DestroyInstance(struct vaapi_instance *inst)
{
    vaTerminate(inst->dpy);
    if (inst->native != NULL && inst->native_destroy_cb != NULL)
        inst->native_destroy_cb(inst->native);
    free(inst);
}