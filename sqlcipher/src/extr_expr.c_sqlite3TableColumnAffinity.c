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
struct TYPE_5__ {int nCol; TYPE_1__* aCol; } ;
typedef  TYPE_2__ Table ;
struct TYPE_4__ {char affinity; } ;

/* Variables and functions */
 char SQLITE_AFF_INTEGER ; 
 int /*<<< orphan*/  assert (int) ; 

char sqlite3TableColumnAffinity(Table *pTab, int iCol){
  assert( iCol<pTab->nCol );
  return iCol>=0 ? pTab->aCol[iCol].affinity : SQLITE_AFF_INTEGER;
}