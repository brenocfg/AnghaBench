#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t num_chats; TYPE_1__* chats; } ;
struct TYPE_4__ {int /*<<< orphan*/  identifier; } ;
typedef  TYPE_2__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_IDENTIFIER_LENGTH ; 
 scalar_t__ sodium_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_group_num(const Group_Chats *g_c, const uint8_t *identifier)
{
    uint32_t i;

    for (i = 0; i < g_c->num_chats; ++i)
        if (sodium_memcmp(g_c->chats[i].identifier, identifier, GROUP_IDENTIFIER_LENGTH) == 0)
            return i;

    return -1;
}