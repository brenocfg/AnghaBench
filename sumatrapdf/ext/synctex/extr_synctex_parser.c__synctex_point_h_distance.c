#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int h; } ;
typedef  TYPE_2__ synctex_point_t ;
typedef  TYPE_3__* synctex_node_t ;
typedef  int /*<<< orphan*/  synctex_bool_t ;
struct TYPE_13__ {TYPE_1__* class; } ;
struct TYPE_11__ {int type; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SYNCTEX_ABS_WIDTH (TYPE_3__*) ; 
 int /*<<< orphan*/  SYNCTEX_ABS_WIDTH_V (TYPE_3__*) ; 
 int SYNCTEX_HORIZ (TYPE_3__*) ; 
 int SYNCTEX_HORIZ_V (TYPE_3__*) ; 
 int SYNCTEX_WIDTH (TYPE_3__*) ; 
#define  synctex_node_type_glue 134 
#define  synctex_node_type_hbox 133 
#define  synctex_node_type_kern 132 
#define  synctex_node_type_math 131 
#define  synctex_node_type_vbox 130 
#define  synctex_node_type_void_hbox 129 
#define  synctex_node_type_void_vbox 128 

int _synctex_point_h_distance(synctex_point_t hitPoint, synctex_node_t node, synctex_bool_t visible) {
	if (node) {
		int min,med,max;
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
				min = visible?SYNCTEX_HORIZ_V(node):SYNCTEX_HORIZ(node);
				max = min + (visible?SYNCTEX_ABS_WIDTH_V(node):SYNCTEX_ABS_WIDTH(node));
				/*  We allways have min <= max */
				if (hitPoint.h<min) {
					return min - hitPoint.h; /*  regions 1+4+7, result is > 0 */
				} else if (hitPoint.h>max) {
					return max - hitPoint.h; /*  regions 3+6+9, result is < 0 */
				} else {
					return 0; /*  regions 2+5+8, inside the box, except for vertical coordinates */
				}
				break;
			case synctex_node_type_vbox:
			case synctex_node_type_void_vbox:
			case synctex_node_type_void_hbox:
				/*  getting the box bounds, taking into account negative width, height and depth.
				 *  For these boxes, no visible dimension available */
				min = SYNCTEX_HORIZ(node);
				max = min + SYNCTEX_ABS_WIDTH(node);
				/*  We allways have min <= max */
				if (hitPoint.h<min) {
					return min - hitPoint.h; /*  regions 1+4+7, result is > 0 */
				} else if (hitPoint.h>max) {
					return max - hitPoint.h; /*  regions 3+6+9, result is < 0 */
				} else {
					return 0; /*  regions 2+5+8, inside the box, except for vertical coordinates */
				}
				break;
			case synctex_node_type_kern:
				/*  IMPORTANT NOTICE: the location of the kern is recorded AFTER the move.
				 *  The distance to the kern is very special,
				 *  in general, there is no text material in the kern,
				 *  this is why we compute the offset relative to the closest edge of the kern.*/
				max = SYNCTEX_WIDTH(node);
				if (max<0) {
					min = SYNCTEX_HORIZ(node);
					max = min - max;
				} else {
					min = -max;
					max = SYNCTEX_HORIZ(node);
					min += max;
				}
				med = (min+max)/2;
				/*  positive kern: '.' means text, '>' means kern offset
				 *      .............
				 *                   min>>>>med>>>>max
				 *                                    ...............
				 *  negative kern: '.' means text, '<' means kern offset
				 *      ............................
				 *                 min<<<<med<<<<max
				 *                 .................................
				 *  Actually, we do not take into account negative widths.
				 *  There is a problem for such situation when there is efectively overlapping text.
				 *  But this should be extremely rare. I guess that in that case, many different choices
				 *  could be made, one being in contradiction of the other.
				 *  It means that the best choice should be made according to the situation that occurs
				 *  most frequently.
				 */
				if (hitPoint.h<min) {
					return min - hitPoint.h + 1; /*  penalty to ensure other nodes are chosen first in case of overlapping ones */
				} else if (hitPoint.h>max) {
					return max - hitPoint.h - 1; /*  same kind of penalty */
				} else if (hitPoint.h>med) {
					/*  do things like if the node had 0 width and was placed at the max edge + 1*/
					return max - hitPoint.h + 1; /*  positive, the kern is to the right of the hitPoint */
				} else {
					return min - hitPoint.h - 1; /*  negative, the kern is to the left of the hitPoint */
				}
			case synctex_node_type_glue:
			case synctex_node_type_math:
				return SYNCTEX_HORIZ(node) - hitPoint.h;
		}
	}
	return INT_MAX;/*  We always assume that the node is faraway to the right*/
}