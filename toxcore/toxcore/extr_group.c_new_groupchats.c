#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fr_c; TYPE_1__* m; } ;
struct TYPE_7__ {TYPE_2__* group_chat_object; int /*<<< orphan*/  fr_c; } ;
typedef  TYPE_1__ Messenger ;
typedef  TYPE_2__ Group_Chats ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  handle_friend_invite_packet ; 
 int /*<<< orphan*/  m_callback_group_invite (TYPE_1__*,int /*<<< orphan*/ *) ; 

Group_Chats *new_groupchats(Messenger *m)
{
    if (!m)
        return NULL;

    Group_Chats *temp = calloc(1, sizeof(Group_Chats));

    if (temp == NULL)
        return NULL;

    temp->m = m;
    temp->fr_c = m->fr_c;
    m->group_chat_object = temp;
    m_callback_group_invite(m, &handle_friend_invite_packet);

    return temp;
}