#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int statusmessage_length; int /*<<< orphan*/  statusmessage; } ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int m_copy_self_statusmessage(const Messenger *m, uint8_t *buf)
{
    memcpy(buf, m->statusmessage, m->statusmessage_length);
    return m->statusmessage_length;
}