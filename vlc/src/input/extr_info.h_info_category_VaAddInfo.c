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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_8__ {int /*<<< orphan*/ * psz_value; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ info_t ;
struct TYPE_9__ {int /*<<< orphan*/  infos; } ;
typedef  TYPE_2__ info_category_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* info_New (char const*) ; 
 TYPE_1__* info_category_FindInfo (TYPE_2__*,char const*) ; 
 int vasprintf (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline info_t *info_category_VaAddInfo(info_category_t *cat,
                                              const char *name,
                                              const char *format, va_list args)
{
    info_t *info = info_category_FindInfo(cat, name);
    if (!info) {
        info = info_New(name);
        if (!info)
            return NULL;
        vlc_list_append(&info->node, &cat->infos);
    } else
        free(info->psz_value);
    if (vasprintf(&info->psz_value, format, args) == -1)
        info->psz_value = NULL;
    return info;
}