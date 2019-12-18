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
struct TYPE_4__ {int /*<<< orphan*/  infos; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ info_category_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  vlc_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline info_category_t *info_category_New(const char *name)
{
    info_category_t *cat = malloc(sizeof(*cat));
    if (!cat)
        return NULL;
    cat->psz_name = strdup(name);
    vlc_list_init(&cat->infos);
    return cat;
}