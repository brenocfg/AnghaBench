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
struct TYPE_3__ {int /*<<< orphan*/  accepted_key_list; } ;
typedef  TYPE_1__ TCP_Server ;

/* Variables and functions */
 int bs_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int get_TCP_connection_index(const TCP_Server *TCP_server, const uint8_t *public_key)
{
    return bs_list_find(&TCP_server->accepted_key_list, public_key);
}