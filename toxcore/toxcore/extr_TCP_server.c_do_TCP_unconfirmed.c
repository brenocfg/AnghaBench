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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  TCP_Server ;

/* Variables and functions */
 scalar_t__ MAX_INCOMMING_CONNECTIONS ; 
 int /*<<< orphan*/  do_unconfirmed (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void do_TCP_unconfirmed(TCP_Server *TCP_server)
{
    uint32_t i;

    for (i = 0; i < MAX_INCOMMING_CONNECTIONS; ++i) {
        do_unconfirmed(TCP_server, i);
    }
}