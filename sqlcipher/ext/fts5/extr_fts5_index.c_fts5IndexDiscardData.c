#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nPendingData; scalar_t__ pHash; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5HashClear (scalar_t__) ; 

__attribute__((used)) static void fts5IndexDiscardData(Fts5Index *p){
  assert( p->pHash || p->nPendingData==0 );
  if( p->pHash ){
    sqlite3Fts5HashClear(p->pHash);
    p->nPendingData = 0;
  }
}