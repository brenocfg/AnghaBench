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
struct TYPE_5__ {struct TYPE_5__* next_in_directory; int /*<<< orphan*/  extension_on_cd; int /*<<< orphan*/  name_on_cd; TYPE_1__* parent; } ;
struct TYPE_4__ {TYPE_2__* first_record; } ;
typedef  TYPE_2__* PDIR_RECORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL cdname_exists(PDIR_RECORD d)
{
    PDIR_RECORD p = d->parent->first_record;
    while (p)
    {
        if ( p != d
            && !strcasecmp(p->name_on_cd, d->name_on_cd)
            && !strcasecmp(p->extension_on_cd, d->extension_on_cd) )
            return TRUE;
        p = p->next_in_directory;
    }
    return FALSE;
}