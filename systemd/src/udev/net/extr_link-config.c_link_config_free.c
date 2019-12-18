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
struct TYPE_4__ {struct TYPE_4__* alias; struct TYPE_4__* name; struct TYPE_4__* name_policy; struct TYPE_4__* mac; struct TYPE_4__* description; int /*<<< orphan*/  conditions; int /*<<< orphan*/  match_property; int /*<<< orphan*/  match_name; int /*<<< orphan*/  match_type; int /*<<< orphan*/  match_driver; int /*<<< orphan*/  match_path; int /*<<< orphan*/  match_mac; struct TYPE_4__* filename; } ;
typedef  TYPE_1__ link_config ;

/* Variables and functions */
 int /*<<< orphan*/  condition_free_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_config_free(link_config *link) {
        if (!link)
                return;

        free(link->filename);

        set_free_free(link->match_mac);
        strv_free(link->match_path);
        strv_free(link->match_driver);
        strv_free(link->match_type);
        strv_free(link->match_name);
        strv_free(link->match_property);
        condition_free_list(link->conditions);

        free(link->description);
        free(link->mac);
        free(link->name_policy);
        free(link->name);
        free(link->alias);

        free(link);
}