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
struct TYPE_6__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int sqlite3FindDbName (TYPE_2__*,char const*) ; 

Btree *sqlite3DbNameToBtree(sqlite3 *db, const char *zDbName){
  int iDb = zDbName ? sqlite3FindDbName(db, zDbName) : 0;
  return iDb<0 ? 0 : db->aDb[iDb].pBt;
}