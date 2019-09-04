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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  copy_friendlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tox_self_get_friend_list_size (int /*<<< orphan*/  const*) ; 

void tox_self_get_friend_list(const Tox *tox, uint32_t *list)
{
    if (list) {
        const Messenger *m = tox;
        //TODO: size parameter?
        copy_friendlist(m, list, tox_self_get_friend_list_size(tox));
    }
}