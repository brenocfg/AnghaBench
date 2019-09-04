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
struct FaceCount {long size; TYPE_1__* eStart; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {struct TYPE_3__* Onext; struct TYPE_3__* Sym; int /*<<< orphan*/  Rface; struct TYPE_3__* Oprev; struct TYPE_3__* Dnext; int /*<<< orphan*/  Lface; struct TYPE_3__* Dprev; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  int /*<<< orphan*/  GLUface ;

/* Variables and functions */
 int /*<<< orphan*/  AddToTrail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeTrail (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEven (long) ; 
 scalar_t__ Marked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RenderStrip ; 

__attribute__((used)) static struct FaceCount MaximumStrip( GLUhalfEdge *eOrig )
{
  /* Here we are looking for a maximal strip that contains the vertices
   * eOrig->Org, eOrig->Dst, eOrig->Lnext->Dst (in that order or the
   * reverse, such that all triangles are oriented CCW).
   *
   * Again we walk forward and backward as far as possible.  However for
   * strips there is a twist: to get CCW orientations, there must be
   * an *even* number of triangles in the strip on one side of eOrig.
   * We walk the strip starting on a side with an even number of triangles;
   * if both side have an odd number, we are forced to shorten one side.
   */
  struct FaceCount newFace = { 0, NULL, &RenderStrip };
  long headSize = 0, tailSize = 0;
  GLUface *trail = NULL;
  GLUhalfEdge *e, *eTail, *eHead;

  for( e = eOrig; ! Marked( e->Lface ); ++tailSize, e = e->Onext ) {
    AddToTrail( e->Lface, trail );
    ++tailSize;
    e = e->Dprev;
    if( Marked( e->Lface )) break;
    AddToTrail( e->Lface, trail );
  }
  eTail = e;

  for( e = eOrig; ! Marked( e->Rface ); ++headSize, e = e->Dnext ) {
    AddToTrail( e->Rface, trail );
    ++headSize;
    e = e->Oprev;
    if( Marked( e->Rface )) break;
    AddToTrail( e->Rface, trail );
  }
  eHead = e;

  newFace.size = tailSize + headSize;
  if( IsEven( tailSize )) {
    newFace.eStart = eTail->Sym;
  } else if( IsEven( headSize )) {
    newFace.eStart = eHead;
  } else {
    /* Both sides have odd length, we must shorten one of them.  In fact,
     * we must start from eHead to guarantee inclusion of eOrig->Lface.
     */
    --newFace.size;
    newFace.eStart = eHead->Onext;
  }
  /*LINTED*/
  FreeTrail( trail );
  return newFace;
}