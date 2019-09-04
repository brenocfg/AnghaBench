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
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  TOX_USER_STATUS ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  m_set_userstatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tox_self_set_status(Tox *tox, TOX_USER_STATUS user_status)
{
    Messenger *m = tox;
    m_set_userstatus(m, user_status);
}