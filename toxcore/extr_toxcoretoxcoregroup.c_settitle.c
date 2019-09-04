#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  title_callback_userdata; int /*<<< orphan*/  m; int /*<<< orphan*/  (* title_callback ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  title_len; int /*<<< orphan*/  title; } ;
typedef  TYPE_1__ Group_c ;
typedef  TYPE_2__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NAME_LENGTH ; 
 TYPE_1__* get_group_c (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int settitle(Group_Chats *g_c, int groupnumber, int peer_index, const uint8_t *title, uint8_t title_len)
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

    if (g_c->title_callback)
        g_c->title_callback(g_c->m, groupnumber, peer_index, title, title_len, g_c->title_callback_userdata);

    return 0;
}