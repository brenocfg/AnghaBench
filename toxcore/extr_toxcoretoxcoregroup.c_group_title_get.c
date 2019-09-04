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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ title_len; int /*<<< orphan*/  title; } ;
typedef  TYPE_1__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 scalar_t__ MAX_NAME_LENGTH ; 
 TYPE_1__* get_group_c (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

int group_title_get(const Group_Chats *g_c, int groupnumber, uint8_t *title, uint32_t max_length)
{
    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    if (g->title_len == 0 || g->title_len > MAX_NAME_LENGTH)
        return -1;

    if (max_length > g->title_len)
        max_length = g->title_len;

    memcpy(title, g->title, max_length);
    return max_length;
}