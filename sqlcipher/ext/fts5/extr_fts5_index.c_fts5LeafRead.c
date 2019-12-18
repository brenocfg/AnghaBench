#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_9__ {scalar_t__ szLeaf; scalar_t__ nn; } ;
struct TYPE_8__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5Data ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_CORRUPT ; 
 TYPE_2__* fts5DataRead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DataRelease (TYPE_2__*) ; 

__attribute__((used)) static Fts5Data *fts5LeafRead(Fts5Index *p, i64 iRowid){
  Fts5Data *pRet = fts5DataRead(p, iRowid);
  if( pRet ){
    if( pRet->szLeaf>pRet->nn ){
      p->rc = FTS5_CORRUPT;
      fts5DataRelease(pRet);
      pRet = 0;
    }
  }
  return pRet;
}