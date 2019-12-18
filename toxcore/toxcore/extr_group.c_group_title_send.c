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
struct TYPE_3__ {int numpeers; int /*<<< orphan*/  title_len; int /*<<< orphan*/  title; } ;
typedef  TYPE_1__ Group_c ;
typedef  int /*<<< orphan*/  Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  GROUP_MESSAGE_TITLE_ID ; 
 int /*<<< orphan*/  MAX_NAME_LENGTH ; 
 TYPE_1__* get_group_c (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ send_message_group (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int group_title_send(const Group_Chats *g_c, int groupnumber, const uint8_t *title, uint8_t title_len)
{
    if (title_len > MAX_NAME_LENGTH || title_len == 0)
        return -1;

    Group_c *g = get_group_c(g_c, groupnumber);

    if (!g)
        return -1;

    /* same as already set? */
    if (g->title_len == title_len && !memcmp(g->title, title, title_len))
        return 0;

    memcpy(g->title, title, title_len);
    g->title_len = title_len;

    if (g->numpeers == 1)
        return 0;

    if (send_message_group(g_c, groupnumber, GROUP_MESSAGE_TITLE_ID, title, title_len))
        return 0;
    else
        return -1;
}