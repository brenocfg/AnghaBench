#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* synctex_scanner_t ;
struct TYPE_14__ {float h; float v; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ synctex_point_t ;
typedef  int /*<<< orphan*/ * synctex_node_t ;
struct TYPE_15__ {int /*<<< orphan*/ * left; int /*<<< orphan*/ * right; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ synctex_node_set_t ;
struct TYPE_16__ {scalar_t__ left; scalar_t__ right; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ synctex_distances_t ;
struct TYPE_13__ {float unit; float x_offset; float y_offset; int /*<<< orphan*/ * sheet; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/ * SYNCTEX_CHILD (int /*<<< orphan*/ *) ; 
 scalar_t__ SYNCTEX_COLUMN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SYNCTEX_CUR ; 
 scalar_t__ SYNCTEX_END ; 
 scalar_t__ SYNCTEX_LINE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SYNCTEX_NEXT_HORIZ_BOX (int /*<<< orphan*/ *) ; 
 int SYNCTEX_PAGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SYNCTEX_SIBLING (int /*<<< orphan*/ *) ; 
 scalar_t__ SYNCTEX_START ; 
 int SYNCTEX_STATUS_ERROR ; 
 scalar_t__ SYNCTEX_TAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _synctex_eq_deepest_container (TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _synctex_eq_get_closest_children_in_box (TYPE_2__,int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _synctex_point_in_box (TYPE_2__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _synctex_smallest_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  synctex_YES ; 
 TYPE_1__* synctex_scanner_parse (TYPE_1__*) ; 

int synctex_edit_query(synctex_scanner_t scanner,int page,float h,float v) {
	synctex_node_t sheet = NULL;
	synctex_node_t node = NULL; /*  placeholder */
	synctex_node_t other_node = NULL; /*  placeholder */
	synctex_point_t hitPoint = {0,0}; /*  placeholder */
	synctex_node_set_t bestNodes = {NULL,NULL}; /*  holds the best node */
	synctex_distances_t bestDistances = {INT_MAX,INT_MAX}; /*  holds the best distances for the best node */
	synctex_node_t bestContainer = NULL; /*  placeholder */
	if (NULL == (scanner = synctex_scanner_parse(scanner)) || 0 >= scanner->unit) {/*  scanner->unit must be >0 */
		return 0;
	}
	/*  Convert the given point to scanner integer coordinates */
	hitPoint.h = (h-scanner->x_offset)/scanner->unit;
	hitPoint.v = (v-scanner->y_offset)/scanner->unit;
	/*  We will store in the scanner's buffer the result of the query. */
	free(SYNCTEX_START);
	SYNCTEX_START = SYNCTEX_END = SYNCTEX_CUR = NULL;
	/*  Find the proper sheet */
	sheet = scanner->sheet;
	while((sheet) && SYNCTEX_PAGE(sheet) != page) {
		sheet = SYNCTEX_SIBLING(sheet);
	}
	if (NULL == sheet) {
		return -1;
	}
	/*  Now sheet points to the sheet node with proper page number */
	/*  Here is how we work:
	 *  At first we do not consider the visible box dimensions. This will cover the most frequent cases.
	 *  Then we try with the visible box dimensions.
	 *  We try to find a non void box containing the hit point.
	 *  We browse all the horizontal boxes until we find one containing the hit point. */
	if ((node = SYNCTEX_NEXT_HORIZ_BOX(sheet))) {
		do {
			if (_synctex_point_in_box(hitPoint,node,synctex_YES)) {
				/*  Maybe the hitPoint belongs to a contained vertical box. */
end:
				/*  This trick is for catching overlapping boxes */
				if ((other_node = SYNCTEX_NEXT_HORIZ_BOX(node))) {
					do {
						if (_synctex_point_in_box(hitPoint,other_node,synctex_YES)) {
							node = _synctex_smallest_container(other_node,node); 
						}
					} while((other_node = SYNCTEX_NEXT_HORIZ_BOX(other_node)));
				}
                /*  node is the smallest horizontal box that contains hitPoint. */
				if ((bestContainer = _synctex_eq_deepest_container(hitPoint,node,synctex_YES))) {
					node = bestContainer;
				}
				_synctex_eq_get_closest_children_in_box(hitPoint,node,&bestNodes,&bestDistances,synctex_YES);
				if (bestNodes.right && bestNodes.left) {
					if ((SYNCTEX_TAG(bestNodes.right)!=SYNCTEX_TAG(bestNodes.left))
							|| (SYNCTEX_LINE(bestNodes.right)!=SYNCTEX_LINE(bestNodes.left))
								|| (SYNCTEX_COLUMN(bestNodes.right)!=SYNCTEX_COLUMN(bestNodes.left))) {
						if ((SYNCTEX_START = malloc(2*sizeof(synctex_node_t)))) {
							if (bestDistances.left>bestDistances.right) {
								((synctex_node_t *)SYNCTEX_START)[0] = bestNodes.right;
								((synctex_node_t *)SYNCTEX_START)[1] = bestNodes.left;
							} else {
								((synctex_node_t *)SYNCTEX_START)[0] = bestNodes.left;
								((synctex_node_t *)SYNCTEX_START)[1] = bestNodes.right;
							}
							SYNCTEX_END = SYNCTEX_START + 2*sizeof(synctex_node_t);
							SYNCTEX_CUR = NULL;
							return (SYNCTEX_END-SYNCTEX_START)/sizeof(synctex_node_t);
						}
						return SYNCTEX_STATUS_ERROR;
					}
					/*  both nodes have the same input coordinates
					 *  We choose the one closest to the hit point  */
					if (bestDistances.left>bestDistances.right) {
						bestNodes.left = bestNodes.right;
					}
					bestNodes.right = NULL;
				} else if (bestNodes.right) {
					bestNodes.left = bestNodes.right;
				} else if (!bestNodes.left){
					bestNodes.left = node;
				}
				if ((SYNCTEX_START = malloc(sizeof(synctex_node_t)))) {
					* (synctex_node_t *)SYNCTEX_START = bestNodes.left;
					SYNCTEX_END = SYNCTEX_START + sizeof(synctex_node_t);
					SYNCTEX_CUR = NULL;
					return (SYNCTEX_END-SYNCTEX_START)/sizeof(synctex_node_t);
				}
				return SYNCTEX_STATUS_ERROR;
			}
		} while ((node = SYNCTEX_NEXT_HORIZ_BOX(node)));
		/*  All the horizontal boxes have been tested,
		 *  None of them contains the hit point.
		 */
	}
	/*  We are not lucky */
	if ((node = SYNCTEX_CHILD(sheet))) {
		goto end;
	}
	return 0;
}