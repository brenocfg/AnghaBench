#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int v; int h; } ;
typedef  TYPE_2__ synctex_point_t ;
typedef  TYPE_3__* synctex_node_t ;
typedef  int /*<<< orphan*/  synctex_bool_t ;
struct TYPE_14__ {TYPE_1__* class; } ;
struct TYPE_12__ {int type; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SYNCTEX_ABS_DEPTH (TYPE_3__*) ; 
 int SYNCTEX_ABS_HEIGHT (TYPE_3__*) ; 
 int /*<<< orphan*/  SYNCTEX_ABS_WIDTH (TYPE_3__*) ; 
 int SYNCTEX_HORIZ (TYPE_3__*) ; 
 int SYNCTEX_VERT (TYPE_3__*) ; 
 int SYNCTEX_WIDTH (TYPE_3__*) ; 
#define  synctex_node_type_glue 134 
#define  synctex_node_type_hbox 133 
#define  synctex_node_type_kern 132 
#define  synctex_node_type_math 131 
#define  synctex_node_type_vbox 130 
#define  synctex_node_type_void_hbox 129 
#define  synctex_node_type_void_vbox 128 

int _synctex_node_distance_to_point(synctex_point_t hitPoint, synctex_node_t node, synctex_bool_t visible) {
#	ifdef __DARWIN_UNIX03
#       pragma unused(visible)
#   endif
	int result = INT_MAX; /*  when the distance is meaning less (sheet, input...)  */
	if (node) {
		int minH,maxH,minV,maxV;
		switch(node->class->type) {
			/*  The distance between a point and a box is special.
			 *  It is not the euclidian distance, nor something similar.
			 *  We have to take into account the particular layout,
			 *  and the box hierarchy.
			 *  Given a box, there are 9 regions delimited by the lines of the edges of the box.
			 *  The origin being at the top left corner of the page,
			 *  we also give names to the vertices of the box.
			 *
			 *   1 | 2 | 3
			 *  ---A---B--->
			 *   4 | 5 | 6
			 *  ---C---D--->
			 *   7 | 8 | 9
			 *     v   v
			 *  In each region, there is a different formula.
			 *  In the end we have a continuous distance which may not be a mathematical distance but who cares. */
			case synctex_node_type_vbox:
			case synctex_node_type_void_vbox:
			case synctex_node_type_hbox:
			case synctex_node_type_void_hbox:
				/*  getting the box bounds, taking into account negative widths. */
				minH = SYNCTEX_HORIZ(node);
				maxH = minH + SYNCTEX_ABS_WIDTH(node);
				minV = SYNCTEX_VERT(node);
				maxV = minV + SYNCTEX_ABS_DEPTH(node);
				minV -= SYNCTEX_ABS_HEIGHT(node);
				/*  In what region is the point hitPoint=(H,V) ? */
				if (hitPoint.v<minV) {
					if (hitPoint.h<minH) {
						/*  This is region 1. The distance to the box is the L1 distance PA. */
						result = minV - hitPoint.v + minH - hitPoint.h;/*  Integer overflow? probability epsilon */
					} else if (hitPoint.h<=maxH) {
						/*  This is region 2. The distance to the box is the geometrical distance to the top edge.  */
						result = minV - hitPoint.v;
					} else {
						/*  This is region 3. The distance to the box is the L1 distance PB. */
						result = minV - hitPoint.v + hitPoint.h - maxH;
					}
				} else if (hitPoint.v<=maxV) {
					if (hitPoint.h<minH) {
						/*  This is region 4. The distance to the box is the geometrical distance to the left edge.  */
						result = minH - hitPoint.h;
					} else if (hitPoint.h<=maxH) {
						/*  This is region 4. We are inside the box.  */
						result = 0;
					} else {
						/*  This is region 6. The distance to the box is the geometrical distance to the right edge.  */
						result = hitPoint.h - maxH;
					}
				} else {
					if (hitPoint.h<minH) {
						/*  This is region 7. The distance to the box is the L1 distance PC. */
						result = hitPoint.v - maxV + minH - hitPoint.h;
					} else if (hitPoint.h<=maxH) {
						/*  This is region 8. The distance to the box is the geometrical distance to the top edge.  */
						result = hitPoint.v - maxV;
					} else {
						/*  This is region 9. The distance to the box is the L1 distance PD. */
						result = hitPoint.v - maxV + hitPoint.h - maxH;
					}
				}
				break;
			case synctex_node_type_kern:
				maxH = SYNCTEX_WIDTH(node);
				if (maxH<0) {
					minH = SYNCTEX_HORIZ(node);
					maxH = minH - maxH;
				} else {
					minH = -maxH;
					maxH = SYNCTEX_HORIZ(node);
					minH += maxH;
				}
				minV = SYNCTEX_VERT(node);
				if (hitPoint.h<minH) {
					if (hitPoint.v>minV) {
						result = hitPoint.v - minV + minH - hitPoint.h;
					} else {
						result = minV - hitPoint.v + minH - hitPoint.h;
					}
				} else if (hitPoint.h>maxH) {
					if (hitPoint.v>minV) {
						result = hitPoint.v - minV + hitPoint.h - maxH;
					} else {
						result = minV - hitPoint.v + hitPoint.h - maxH;
					}
				} else if (hitPoint.v>minV) {
					result = hitPoint.v - minV;
				} else {
					result = minV - hitPoint.v;
				}
				break;
			case synctex_node_type_glue:
			case synctex_node_type_math:
				minH = SYNCTEX_HORIZ(node);
				minV = SYNCTEX_VERT(node);
				if (hitPoint.h<minH) {
					if (hitPoint.v>minV) {
						result = hitPoint.v - minV + minH - hitPoint.h;
					} else {
						result = minV - hitPoint.v + minH - hitPoint.h;
					}
				} else if (hitPoint.v>minV) {
					result = hitPoint.v - minV + hitPoint.h - minH;
				} else {
					result = minV - hitPoint.v + hitPoint.h - minH;
				}
				break;
		}
	}
	return result;
}