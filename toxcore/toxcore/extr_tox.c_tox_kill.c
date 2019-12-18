#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  group_chat_object; } ;
typedef  TYPE_1__ Tox ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  kill_groupchats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_messenger (TYPE_1__*) ; 
 int /*<<< orphan*/  logger_kill_global () ; 

void tox_kill(Tox *tox)
{
    Messenger *m = tox;
    kill_groupchats(m->group_chat_object);
    kill_messenger(m);
    logger_kill_global();
}