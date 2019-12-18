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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_7__ {int nDim; scalar_t__ bInt; } ;
struct TYPE_6__ {scalar_t__ i; scalar_t__ f; } ;
typedef  TYPE_1__ RtreeCoord ;
typedef  TYPE_2__ RtreeCheck ;

/* Variables and functions */
 int /*<<< orphan*/  readCoord (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rtreeCheckAppendMsg (TYPE_2__*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtreeCheckCellCoord(
  RtreeCheck *pCheck, 
  i64 iNode,                      /* Node id to use in error messages */
  int iCell,                      /* Cell number to use in error messages */
  u8 *pCell,                      /* Pointer to cell coordinates */
  u8 *pParent                     /* Pointer to parent coordinates */
){
  RtreeCoord c1, c2;
  RtreeCoord p1, p2;
  int i;

  for(i=0; i<pCheck->nDim; i++){
    readCoord(&pCell[4*2*i], &c1);
    readCoord(&pCell[4*(2*i + 1)], &c2);

    /* printf("%e, %e\n", c1.u.f, c2.u.f); */
    if( pCheck->bInt ? c1.i>c2.i : c1.f>c2.f ){
      rtreeCheckAppendMsg(pCheck, 
          "Dimension %d of cell %d on node %lld is corrupt", i, iCell, iNode
      );
    }

    if( pParent ){
      readCoord(&pParent[4*2*i], &p1);
      readCoord(&pParent[4*(2*i + 1)], &p2);

      if( (pCheck->bInt ? c1.i<p1.i : c1.f<p1.f) 
       || (pCheck->bInt ? c2.i>p2.i : c2.f>p2.f)
      ){
        rtreeCheckAppendMsg(pCheck, 
            "Dimension %d of cell %d on node %lld is corrupt relative to parent"
            , i, iCell, iNode
        );
      }
    }
  }
}