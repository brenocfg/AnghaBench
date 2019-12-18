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
struct TYPE_13__ {int v; } ;
typedef  TYPE_2__ synctex_point_t ;
typedef  TYPE_3__* synctex_node_t ;
typedef  int /*<<< orphan*/  synctex_bool_t ;
struct TYPE_14__ {TYPE_1__* class; } ;
struct TYPE_12__ {int type; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SYNCTEX_ABS_DEPTH (TYPE_3__*) ; 
 int /*<<< orphan*/  SYNCTEX_ABS_DEPTH_V (TYPE_3__*) ; 
 int SYNCTEX_ABS_HEIGHT (TYPE_3__*) ; 
 int SYNCTEX_ABS_HEIGHT_V (TYPE_3__*) ; 
 int SYNCTEX_VERT (TYPE_3__*) ; 
 int SYNCTEX_VERT_V (TYPE_3__*) ; 
#define  synctex_node_type_glue 134 
#define  synctex_node_type_hbox 133 
#define  synctex_node_type_kern 132 
#define  synctex_node_type_math 131 
#define  synctex_node_type_vbox 130 
#define  synctex_node_type_void_hbox 129 
#define  synctex_node_type_void_vbox 128 

int _synctex_point_v_distance(synctex_point_t hitPoint, synctex_node_t node,synctex_bool_t visible) {
#	ifdef __DARWIN_UNIX03
#       pragma unused(visible)
#   endif
	if (node) {
		int min,max;
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
			 */
			case synctex_node_type_hbox:
				/*  getting the box bounds, taking into account negative width, height and depth. */
				min = SYNCTEX_VERT_V(node);
				max = min + SYNCTEX_ABS_DEPTH_V(node);
				min -= SYNCTEX_ABS_HEIGHT_V(node);
				/*  We allways have min <= max */
				if (hitPoint.v<min) {
					return min - hitPoint.v; /*  regions 1+2+3, result is > 0 */
				} else if (hitPoint.v>max) {
					return max - hitPoint.v; /*  regions 7+8+9, result is < 0 */
				} else {
					return 0; /*  regions 4.5.6, inside the box, except for horizontal coordinates */
				}
				break;
			case synctex_node_type_vbox:
			case synctex_node_type_void_vbox:
			case synctex_node_type_void_hbox:
				/*  getting the box bounds, taking into account negative width, height and depth. */
				min = SYNCTEX_VERT(node);
				max = min + SYNCTEX_ABS_DEPTH(node);
				min -= SYNCTEX_ABS_HEIGHT(node);
				/*  We allways have min <= max */
				if (hitPoint.v<min) {
					return min - hitPoint.v; /*  regions 1+2+3, result is > 0 */
				} else if (hitPoint.v>max) {
					return max - hitPoint.v; /*  regions 7+8+9, result is < 0 */
				} else {
					return 0; /*  regions 4.5.6, inside the box, except for horizontal coordinates */
				}
				break;
			case synctex_node_type_kern:
			case synctex_node_type_glue:
			case synctex_node_type_math:
				return SYNCTEX_VERT(node) - hitPoint.v;
		}
	}
	return INT_MAX;/*  We always assume that the node is faraway to the top*/
}