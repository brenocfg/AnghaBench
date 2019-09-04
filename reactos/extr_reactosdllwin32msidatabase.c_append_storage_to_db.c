#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  transforms; } ;
struct TYPE_5__ {int /*<<< orphan*/  entry; int /*<<< orphan*/ * stg; } ;
typedef  TYPE_1__ MSITRANSFORM ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  IStorage ;

/* Variables and functions */
 int /*<<< orphan*/  IStorage_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* msi_alloc (int) ; 

void append_storage_to_db( MSIDATABASE *db, IStorage *stg )
{
    MSITRANSFORM *t;

    t = msi_alloc( sizeof *t );
    t->stg = stg;
    IStorage_AddRef( stg );
    list_add_head( &db->transforms, &t->entry );
}