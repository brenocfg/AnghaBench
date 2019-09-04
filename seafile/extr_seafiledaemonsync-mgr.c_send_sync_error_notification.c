#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mq_mgr; } ;
struct TYPE_9__ {int /*<<< orphan*/  str; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_string_new (int /*<<< orphan*/ *) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_mq_manager_publish_notification (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
send_sync_error_notification (SeafRepo *repo, const char *type)
{
    GString *buf = g_string_new (NULL);
    g_string_append_printf (buf, "%s\t%s", repo->name, repo->id);
    seaf_mq_manager_publish_notification (seaf->mq_mgr,
                                          type,
                                          buf->str);
    g_string_free (buf, TRUE);
}