#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mapping {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  keycmp ; 
 void** tfind (int /*<<< orphan*/ *,void* const*,int /*<<< orphan*/ ) ; 
 int var_SetInteger (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_key_to_action (vlc_object_t *obj, const char *varname,
                              vlc_value_t prevkey, vlc_value_t curkey, void *d)
{
    void *const *map = d;
    const void **pent;
    uint32_t keycode = curkey.i_int;

    pent = tfind (&keycode, map, keycmp);
    if (pent == NULL)
        return VLC_SUCCESS;

    const struct mapping *ent = *pent;

    (void) varname;
    (void) prevkey;
    return var_SetInteger (obj, "key-action", ent->action);
}