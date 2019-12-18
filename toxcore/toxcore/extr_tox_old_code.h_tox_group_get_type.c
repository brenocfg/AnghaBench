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
struct TYPE_4__ {int /*<<< orphan*/  group_chat_object; } ;
typedef  TYPE_1__ Tox ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int group_get_type (int /*<<< orphan*/ ,int) ; 

int tox_group_get_type(const Tox *tox, int groupnumber)
{
    const Messenger *m = tox;
    return group_get_type(m->group_chat_object, groupnumber);
}