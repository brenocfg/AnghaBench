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
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  new_name; int /*<<< orphan*/  name; int /*<<< orphan*/  unmerge_state; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_2__* data; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  GString ;
typedef  TYPE_1__ GList ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_RENAMED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

char *
format_diff_results(GList *results)
{
    GList *ptr;
    GString *fmt_status;
    DiffEntry *de;

    fmt_status = g_string_new("");

    for (ptr = results; ptr; ptr = ptr->next) {
        de = ptr->data;

        if (de->status != DIFF_STATUS_RENAMED)
            g_string_append_printf(fmt_status, "%c %c %d %u %s\n",
                                   de->type, de->status, de->unmerge_state,
                                   (int)strlen(de->name), de->name);
        else
            g_string_append_printf(fmt_status, "%c %c %d %u %s %u %s\n",
                                   de->type, de->status, de->unmerge_state,
                                   (int)strlen(de->name), de->name,
                                   (int)strlen(de->new_name), de->new_name);
    }

    return g_string_free(fmt_status, FALSE);
}