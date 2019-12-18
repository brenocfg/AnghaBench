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
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ info_t ;
typedef  int /*<<< orphan*/  info_category_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  info_Delete (TYPE_1__*) ; 
 TYPE_1__* info_category_FindInfo (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int info_category_DeleteInfo(info_category_t *cat, const char *name)
{
    info_t *info = info_category_FindInfo(cat, name);
    if (info != NULL) {
        vlc_list_remove(&info->node);
        info_Delete(info);
        return VLC_SUCCESS;
    }
    return VLC_EGENERIC;
}