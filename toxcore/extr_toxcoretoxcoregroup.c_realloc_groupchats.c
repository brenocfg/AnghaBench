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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * chats; } ;
typedef  int /*<<< orphan*/  Group_c ;
typedef  TYPE_1__ Group_Chats ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int realloc_groupchats(Group_Chats *g_c, uint32_t num)
{
    if (num == 0) {
        free(g_c->chats);
        g_c->chats = NULL;
        return 0;
    }

    Group_c *newgroup_chats = realloc(g_c->chats, num * sizeof(Group_c));

    if (newgroup_chats == NULL)
        return -1;

    g_c->chats = newgroup_chats;
    return 0;
}