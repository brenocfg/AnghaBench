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
struct TYPE_5__ {int nDb; TYPE_1__* aDb; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * pSchema; } ;
typedef  int /*<<< orphan*/  Schema ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3SchemaToIndex(sqlite3 *db, Schema *pSchema){
  int i = -1000000;

  /* If pSchema is NULL, then return -1000000. This happens when code in 
  ** expr.c is trying to resolve a reference to a transient table (i.e. one
  ** created by a sub-select). In this case the return value of this 
  ** function should never be used.
  **
  ** We return -1000000 instead of the more usual -1 simply because using
  ** -1000000 as the incorrect index into db->aDb[] is much 
  ** more likely to cause a segfault than -1 (of course there are assert()
  ** statements too, but it never hurts to play the odds).
  */
  assert( sqlite3_mutex_held(db->mutex) );
  if( pSchema ){
    for(i=0; 1; i++){
      assert( i<db->nDb );
      if( db->aDb[i].pSchema==pSchema ){
        break;
      }
    }
    assert( i>=0 && i<db->nDb );
  }
  return i;
}