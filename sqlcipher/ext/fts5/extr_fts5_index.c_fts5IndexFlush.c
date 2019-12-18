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
struct TYPE_4__ {scalar_t__ nPendingData; int /*<<< orphan*/  pHash; } ;
typedef  TYPE_1__ Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5FlushOneHash (TYPE_1__*) ; 

__attribute__((used)) static void fts5IndexFlush(Fts5Index *p){
  /* Unless it is empty, flush the hash table to disk */
  if( p->nPendingData ){
    assert( p->pHash );
    p->nPendingData = 0;
    fts5FlushOneHash(p);
  }
}