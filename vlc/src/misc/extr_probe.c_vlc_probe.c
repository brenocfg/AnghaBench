#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t count; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ vlc_probe_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/ * module_need (TYPE_1__*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void *vlc_probe (vlc_object_t *obj,
                 const char *capability, size_t *restrict pcount)
{
    vlc_probe_t *probe = vlc_custom_create (obj, sizeof(*probe), "probe");
    if (unlikely(probe == NULL))
    {
        *pcount = 0;
        return NULL;
    }
    probe->list = NULL;
    probe->count = 0;

    module_t *mod = module_need (probe, capability, NULL, false);
    if (mod != NULL)
    {
        msg_Warn (probe, "probing halted");
        module_unneed (probe, mod);
    }

    void *ret = probe->list;
    *pcount = probe->count;
    vlc_object_delete(probe);
    return ret;
}