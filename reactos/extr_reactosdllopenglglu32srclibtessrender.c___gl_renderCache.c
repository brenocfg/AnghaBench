#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int cacheCount; scalar_t__* normal; int windingRule; scalar_t__ boundaryOnly; TYPE_2__* cache; } ;
typedef  scalar_t__ GLdouble ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ CachedVertex ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_BEGIN_OR_BEGIN_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALL_END_OR_END_DATA () ; 
 int /*<<< orphan*/  CALL_VERTEX_OR_VERTEX_DATA (int /*<<< orphan*/ ) ; 
 int ComputeNormal (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
#define  GLU_TESS_WINDING_ABS_GEQ_TWO 132 
#define  GLU_TESS_WINDING_NEGATIVE 131 
#define  GLU_TESS_WINDING_NONZERO 130 
#define  GLU_TESS_WINDING_ODD 129 
#define  GLU_TESS_WINDING_POSITIVE 128 
 int /*<<< orphan*/  GL_LINE_LOOP ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 int SIGN_INCONSISTENT ; 
 int /*<<< orphan*/  TRUE ; 

GLboolean __gl_renderCache( GLUtesselator *tess )
{
  CachedVertex *v0 = tess->cache;
  CachedVertex *vn = v0 + tess->cacheCount;
  CachedVertex *vc;
  GLdouble norm[3];
  int sign;

  if( tess->cacheCount < 3 ) {
    /* Degenerate contour -- no output */
    return TRUE;
  }

  norm[0] = tess->normal[0];
  norm[1] = tess->normal[1];
  norm[2] = tess->normal[2];
  if( norm[0] == 0 && norm[1] == 0 && norm[2] == 0 ) {
    ComputeNormal( tess, norm, FALSE );
  }

  sign = ComputeNormal( tess, norm, TRUE );
  if( sign == SIGN_INCONSISTENT ) {
    /* Fan triangles did not have a consistent orientation */
    return FALSE;
  }
  if( sign == 0 ) {
    /* All triangles were degenerate */
    return TRUE;
  }

  /* Make sure we do the right thing for each winding rule */
  switch( tess->windingRule ) {
  case GLU_TESS_WINDING_ODD:
  case GLU_TESS_WINDING_NONZERO:
    break;
  case GLU_TESS_WINDING_POSITIVE:
    if( sign < 0 ) return TRUE;
    break;
  case GLU_TESS_WINDING_NEGATIVE:
    if( sign > 0 ) return TRUE;
    break;
  case GLU_TESS_WINDING_ABS_GEQ_TWO:
    return TRUE;
  }

  CALL_BEGIN_OR_BEGIN_DATA( tess->boundaryOnly ? GL_LINE_LOOP
			  : (tess->cacheCount > 3) ? GL_TRIANGLE_FAN
			  : GL_TRIANGLES );

  CALL_VERTEX_OR_VERTEX_DATA( v0->data ); 
  if( sign > 0 ) {
    for( vc = v0+1; vc < vn; ++vc ) {
      CALL_VERTEX_OR_VERTEX_DATA( vc->data ); 
    }
  } else {
    for( vc = vn-1; vc > v0; --vc ) {
      CALL_VERTEX_OR_VERTEX_DATA( vc->data ); 
    }
  }
  CALL_END_OR_END_DATA();
  return TRUE;
}