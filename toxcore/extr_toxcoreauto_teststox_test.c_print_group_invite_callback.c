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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 scalar_t__ TOX_GROUPCHAT_TYPE_TEXT ; 
 int /*<<< orphan*/  ck_assert_msg (int,char*) ; 
 int invite_counter ; 
 int /*<<< orphan*/ * invite_tox ; 
 int tox_join_groupchat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 

void print_group_invite_callback(Tox *tox, int32_t friendnumber, uint8_t type, const uint8_t *data, uint16_t length,
                                 void *userdata)
{
    if (*((uint32_t *)userdata) != 234212)
        return;

    if (type != TOX_GROUPCHAT_TYPE_TEXT)
        return;

    int g_num;

    if ((g_num = tox_join_groupchat(tox, friendnumber, data, length)) == -1)
        return;

    ck_assert_msg(g_num == 0, "Group number was not 0");
    ck_assert_msg(tox_join_groupchat(tox, friendnumber, data, length) == -1,
                  "Joining groupchat twice should be impossible.");

    invite_tox = tox;
    invite_counter = 4;
}