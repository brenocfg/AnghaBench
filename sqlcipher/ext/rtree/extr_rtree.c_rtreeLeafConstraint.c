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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  rValue; } ;
struct TYPE_5__ {int op; int iCoord; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  RtreeDValue ;
typedef  TYPE_2__ RtreeConstraint ;

/* Variables and functions */
 int NOT_WITHIN ; 
 int /*<<< orphan*/  RTREE_DECODE_COORD (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RTREE_EQ ; 
#define  RTREE_GE 131 
#define  RTREE_GT 130 
#define  RTREE_LE 129 
#define  RTREE_LT 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void rtreeLeafConstraint(
  RtreeConstraint *p,        /* The constraint to test */
  int eInt,                  /* True if RTree holds integer coordinates */
  u8 *pCellData,             /* Raw cell content as appears on disk */
  int *peWithin              /* Adjust downward, as appropriate */
){
  RtreeDValue xN;      /* Coordinate value converted to a double */

  assert(p->op==RTREE_LE || p->op==RTREE_LT || p->op==RTREE_GE 
      || p->op==RTREE_GT || p->op==RTREE_EQ );
  pCellData += 8 + p->iCoord*4;
  assert( ((((char*)pCellData) - (char*)0)&3)==0 );  /* 4-byte aligned */
  RTREE_DECODE_COORD(eInt, pCellData, xN);
  switch( p->op ){
    case RTREE_LE: if( xN <= p->u.rValue ) return;  break;
    case RTREE_LT: if( xN <  p->u.rValue ) return;  break;
    case RTREE_GE: if( xN >= p->u.rValue ) return;  break;
    case RTREE_GT: if( xN >  p->u.rValue ) return;  break;
    default:       if( xN == p->u.rValue ) return;  break;
  }
  *peWithin = NOT_WITHIN;
}