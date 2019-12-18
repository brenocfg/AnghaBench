#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* aSlot; } ;
typedef  TYPE_1__ Fts5Hash ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts5HashClear (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3Fts5HashFree(Fts5Hash *pHash){
  if( pHash ){
    sqlite3Fts5HashClear(pHash);
    sqlite3_free(pHash->aSlot);
    sqlite3_free(pHash);
  }
}