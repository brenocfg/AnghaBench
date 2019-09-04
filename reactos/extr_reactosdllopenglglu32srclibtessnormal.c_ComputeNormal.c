#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mesh; } ;
struct TYPE_6__ {scalar_t__* coords; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__ vHead; } ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_2__ GLUvertex ;
typedef  TYPE_3__ GLUtesselator ;

/* Variables and functions */
 int GLU_TESS_MAX_COORD ; 
 size_t LongAxis (scalar_t__*) ; 

__attribute__((used)) static void ComputeNormal( GLUtesselator *tess, GLdouble norm[3] )
{
  GLUvertex *v, *v1, *v2;
  GLdouble c, tLen2, maxLen2;
  GLdouble maxVal[3], minVal[3], d1[3], d2[3], tNorm[3];
  GLUvertex *maxVert[3], *minVert[3];
  GLUvertex *vHead = &tess->mesh->vHead;
  int i;

  maxVal[0] = maxVal[1] = maxVal[2] = -2 * GLU_TESS_MAX_COORD;
  minVal[0] = minVal[1] = minVal[2] = 2 * GLU_TESS_MAX_COORD;

  for( v = vHead->next; v != vHead; v = v->next ) {
    for( i = 0; i < 3; ++i ) {
      c = v->coords[i];
      if( c < minVal[i] ) { minVal[i] = c; minVert[i] = v; }
      if( c > maxVal[i] ) { maxVal[i] = c; maxVert[i] = v; }
    }
  }

  /* Find two vertices separated by at least 1/sqrt(3) of the maximum
   * distance between any two vertices
   */
  i = 0;
  if( maxVal[1] - minVal[1] > maxVal[0] - minVal[0] ) { i = 1; }
  if( maxVal[2] - minVal[2] > maxVal[i] - minVal[i] ) { i = 2; }
  if( minVal[i] >= maxVal[i] ) {
    /* All vertices are the same -- normal doesn't matter */
    norm[0] = 0; norm[1] = 0; norm[2] = 1;
    return;
  }

  /* Look for a third vertex which forms the triangle with maximum area
   * (Length of normal == twice the triangle area)
   */
  maxLen2 = 0;
  v1 = minVert[i];
  v2 = maxVert[i];
  d1[0] = v1->coords[0] - v2->coords[0];
  d1[1] = v1->coords[1] - v2->coords[1];
  d1[2] = v1->coords[2] - v2->coords[2];
  for( v = vHead->next; v != vHead; v = v->next ) {
    d2[0] = v->coords[0] - v2->coords[0];
    d2[1] = v->coords[1] - v2->coords[1];
    d2[2] = v->coords[2] - v2->coords[2];
    tNorm[0] = d1[1]*d2[2] - d1[2]*d2[1];
    tNorm[1] = d1[2]*d2[0] - d1[0]*d2[2];
    tNorm[2] = d1[0]*d2[1] - d1[1]*d2[0];
    tLen2 = tNorm[0]*tNorm[0] + tNorm[1]*tNorm[1] + tNorm[2]*tNorm[2];
    if( tLen2 > maxLen2 ) {
      maxLen2 = tLen2;
      norm[0] = tNorm[0];
      norm[1] = tNorm[1];
      norm[2] = tNorm[2];
    }
  }

  if( maxLen2 <= 0 ) {
    /* All points lie on a single line -- any decent normal will do */
    norm[0] = norm[1] = norm[2] = 0;
    norm[LongAxis(d1)] = 1;
  }
}