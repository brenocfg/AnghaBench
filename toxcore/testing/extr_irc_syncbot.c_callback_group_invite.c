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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int current_group ; 
 int tox_join_groupchat (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void callback_group_invite(Tox *tox, int fid, uint8_t type, const uint8_t *data, uint16_t length, void *userdata)
{
    if (current_group == -1)
        current_group = tox_join_groupchat(tox, fid, data, length);
}