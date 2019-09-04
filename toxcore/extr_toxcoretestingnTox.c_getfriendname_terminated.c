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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int /*<<< orphan*/  tox_friend_get_name (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tox_friend_get_name_size (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int getfriendname_terminated(Tox *m, int friendnum, char *namebuf)
{
    tox_friend_get_name(m, friendnum, (uint8_t *)namebuf, NULL);
    int res = tox_friend_get_name_size(m, friendnum, NULL);

    if (res >= 0)
        namebuf[res] = 0;
    else
        namebuf[0] = 0;

    return res;
}