#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* next_in_path_table; TYPE_1__* next_in_memory; } ;
struct TYPE_6__ {struct TYPE_6__* next_in_path_table; int /*<<< orphan*/  flags; int /*<<< orphan*/  date_and_time; struct TYPE_6__* next_in_memory; struct TYPE_6__* first_record; struct TYPE_6__* next_in_directory; scalar_t__ level; struct TYPE_6__* parent; } ;
typedef  TYPE_1__* PDIR_RECORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTORY_FLAG ; 
 TYPE_1__* calloc (int,int) ; 
 TYPE_2__ root ; 

__attribute__((used)) static PDIR_RECORD
new_empty_dirrecord(PDIR_RECORD d, BOOL directory)
{
    PDIR_RECORD new_d;
    new_d = calloc(1, sizeof(*new_d));
    new_d->parent = d;
    new_d->level = d->level + 1;
    new_d->next_in_directory = d->first_record;
    d->first_record = new_d;
    new_d->next_in_memory = root.next_in_memory;
    root.next_in_memory = new_d;
    new_d->date_and_time = d->date_and_time;
    if (directory)
    {
        new_d->flags |= DIRECTORY_FLAG;
        new_d->next_in_path_table = root.next_in_path_table;
        root.next_in_path_table = new_d;
    }
    return new_d;
}