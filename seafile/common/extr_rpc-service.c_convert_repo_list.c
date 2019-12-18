#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * data; struct TYPE_9__* next; } ;
typedef  int /*<<< orphan*/  SeafRepo ;
typedef  int /*<<< orphan*/  GObject ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/ * convert_repo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_repo_obj ; 
 int /*<<< orphan*/  g_list_free_full (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_list_prepend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* g_list_reverse (TYPE_1__*) ; 

__attribute__((used)) static GList *
convert_repo_list (GList *inner_repos)
{
    GList *ret = NULL, *ptr;
    GObject *repo = NULL;

    for (ptr = inner_repos; ptr; ptr=ptr->next) {
        SeafRepo *r = ptr->data;
        repo = convert_repo (r);
        if (!repo) {
            g_list_free_full (ret, free_repo_obj);
            return NULL;
        }

        ret = g_list_prepend (ret, repo);
    }

    return g_list_reverse (ret);
}