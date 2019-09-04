#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int length; int /*<<< orphan*/ * items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 TYPE_1__* create_list () ; 
 TYPE_1__* get_basedirs () ; 
 int /*<<< orphan*/  list_cat (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 TYPE_1__* load_themes_in_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_loaded_themes (TYPE_1__*) ; 

void init_themes(list_t **themes, list_t **basedirs) {
	*basedirs = get_basedirs();

	*themes = create_list();
	for (int i = 0; i < (*basedirs)->length; ++i) {
		list_t *dir_themes = load_themes_in_dir((*basedirs)->items[i]);
		if (dir_themes == NULL) {
			continue;
		}
		list_cat(*themes, dir_themes);
		list_free(dir_themes);
	}

	log_loaded_themes(*themes);
}