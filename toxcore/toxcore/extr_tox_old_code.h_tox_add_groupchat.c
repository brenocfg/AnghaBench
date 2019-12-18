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
 int /*<<< orphan*/  GROUPCHAT_TYPE_TEXT ; 
 int add_groupchat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tox_add_groupchat(Tox *tox)
{
    Messenger *m = tox;
    return add_groupchat(m->group_chat_object, GROUPCHAT_TYPE_TEXT);
}