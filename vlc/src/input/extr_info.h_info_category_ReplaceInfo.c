#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  node; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ info_t ;
struct TYPE_9__ {int /*<<< orphan*/  infos; } ;
typedef  TYPE_2__ info_category_t ;

/* Variables and functions */
 int /*<<< orphan*/  info_Delete (TYPE_1__*) ; 
 TYPE_1__* info_category_FindInfo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void info_category_ReplaceInfo(info_category_t *cat,
                                             info_t *info)
{
    info_t *old = info_category_FindInfo(cat, info->psz_name);
    if (old) {
        vlc_list_remove(&old->node);
        info_Delete(old);
    }
    vlc_list_append(&info->node, &cat->infos);
}