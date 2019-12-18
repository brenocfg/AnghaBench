#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pnBytesFreed; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_8__ {scalar_t__ nTabRef; } ;
typedef  TYPE_2__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  deleteTable (TYPE_1__*,TYPE_2__*) ; 

void sqlite3DeleteTable(sqlite3 *db, Table *pTable){
  /* Do not delete the table until the reference count reaches zero. */
  if( !pTable ) return;
  if( ((!db || db->pnBytesFreed==0) && (--pTable->nTabRef)>0) ) return;
  deleteTable(db, pTable);
}