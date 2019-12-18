#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {unsigned int optflagc; int* optflagv; int /*<<< orphan*/  lock; TYPE_2__* opaques; int /*<<< orphan*/ * ppsz_options; scalar_t__ i_options; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_2__ input_item_opaque_t ;

/* Variables and functions */
 int VLC_INPUT_OPTION_TRUSTED ; 
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_OptionParse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_item_ApplyOptions(vlc_object_t *obj, input_item_t *item)
{
    vlc_mutex_lock(&item->lock);
    assert(item->optflagc == (unsigned)item->i_options);

    for (unsigned i = 0; i < (unsigned)item->i_options; i++)
        var_OptionParse(obj, item->ppsz_options[i],
                        !!(item->optflagv[i] & VLC_INPUT_OPTION_TRUSTED));

    for (const input_item_opaque_t *o = item->opaques; o != NULL; o = o->next)
    {
        var_Create(obj, o->name, VLC_VAR_ADDRESS);
        var_SetAddress(obj, o->name, o->value);
    }

    vlc_mutex_unlock(&item->lock);
}