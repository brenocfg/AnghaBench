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
struct TYPE_7__ {int /*<<< orphan*/  group_chat_object; } ;
typedef  TYPE_1__ Tox ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  g_callback_group_namelistchange (int /*<<< orphan*/ ,void (*) (TYPE_1__*,int,int,uint8_t,void*),void*) ; 

void tox_callback_group_namelist_change(Tox *tox, void (*function)(Tox *tox, int, int, uint8_t, void *), void *userdata)
{
    Messenger *m = tox;
    g_callback_group_namelistchange(m->group_chat_object, function, userdata);
}