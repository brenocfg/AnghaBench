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
struct TYPE_4__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  priority_queue_start; } ;
typedef  TYPE_1__ TCP_Secure_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wipe_priority_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_TCP_connection(TCP_Secure_Connection *con)
{
    wipe_priority_list(con->priority_queue_start);
    kill_sock(con->sock);
    sodium_memzero(con, sizeof(TCP_Secure_Connection));
}