#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_text ;
typedef  int /*<<< orphan*/  fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_storable ;
typedef  int /*<<< orphan*/  fz_shade ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_image ;
struct TYPE_4__ {int len; int size; int cs; scalar_t__ alpha; int ctm; int cmd; struct TYPE_4__* list; scalar_t__ path; scalar_t__ stroke; scalar_t__ color; scalar_t__ rect; } ;
typedef  TYPE_1__ fz_display_node ;
typedef  TYPE_1__ fz_display_list ;
typedef  int /*<<< orphan*/  fz_default_colorspaces ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 scalar_t__ ALPHA_PRESENT ; 
#define  CS_CMYK_0 146 
#define  CS_CMYK_1 145 
#define  CS_GRAY_0 144 
#define  CS_GRAY_1 143 
#define  CS_OTHER_0 142 
#define  CS_RGB_0 141 
#define  CS_RGB_1 140 
#define  CS_UNCHANGED 139 
 int CTM_CHANGE_AD ; 
 int CTM_CHANGE_BC ; 
 int CTM_CHANGE_EF ; 
#define  FZ_CMD_BEGIN_GROUP 138 
#define  FZ_CMD_CLIP_IMAGE_MASK 137 
#define  FZ_CMD_CLIP_STROKE_TEXT 136 
#define  FZ_CMD_CLIP_TEXT 135 
#define  FZ_CMD_DEFAULT_COLORSPACES 134 
#define  FZ_CMD_FILL_IMAGE 133 
#define  FZ_CMD_FILL_IMAGE_MASK 132 
#define  FZ_CMD_FILL_SHADE 131 
#define  FZ_CMD_FILL_TEXT 130 
#define  FZ_CMD_IGNORE_TEXT 129 
#define  FZ_CMD_STROKE_TEXT 128 
 int /*<<< orphan*/  SIZE_IN_NODES (int) ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_default_colorspaces (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_shade (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_stroke_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fz_packed_path_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fz_drop_display_list_imp(fz_context *ctx, fz_storable *list_)
{
	fz_display_list *list = (fz_display_list *)list_;
	fz_display_node *node = list->list;
	fz_display_node *node_end = list->list + list->len;
	int cs_n = 1;
	fz_colorspace *cs;

	while (node != node_end)
	{
		fz_display_node n = *node;
		fz_display_node *next = node + n.size;

		node++;
		if (n.rect)
		{
			node += SIZE_IN_NODES(sizeof(fz_rect));
		}
		switch (n.cs)
		{
		default:
		case CS_UNCHANGED:
			break;
		case CS_GRAY_0:
		case CS_GRAY_1:
			cs_n = 1;
			break;
		case CS_RGB_0:
		case CS_RGB_1:
			cs_n = 3;
			break;
		case CS_CMYK_0:
		case CS_CMYK_1:
			cs_n = 4;
			break;
		case CS_OTHER_0:
			cs = *(fz_colorspace **)node;
			cs_n = fz_colorspace_n(ctx, cs);
			fz_drop_colorspace(ctx, cs);
			node += SIZE_IN_NODES(sizeof(fz_colorspace *));
			break;
		}
		if (n.color)
		{
			node += SIZE_IN_NODES(cs_n * sizeof(float));
		}
		if (n.alpha == ALPHA_PRESENT)
		{
			node += SIZE_IN_NODES(sizeof(float));
		}
		if (n.ctm & CTM_CHANGE_AD)
			node += SIZE_IN_NODES(2*sizeof(float));
		if (n.ctm & CTM_CHANGE_BC)
			node += SIZE_IN_NODES(2*sizeof(float));
		if (n.ctm & CTM_CHANGE_EF)
			node += SIZE_IN_NODES(2*sizeof(float));
		if (n.stroke)
		{
			fz_drop_stroke_state(ctx, *(fz_stroke_state **)node);
			node += SIZE_IN_NODES(sizeof(fz_stroke_state *));
		}
		if (n.path)
		{
			int path_size = fz_packed_path_size((fz_path *)node);
			fz_drop_path(ctx, (fz_path *)node);
			node += SIZE_IN_NODES(path_size);
		}
		switch(n.cmd)
		{
		case FZ_CMD_FILL_TEXT:
		case FZ_CMD_STROKE_TEXT:
		case FZ_CMD_CLIP_TEXT:
		case FZ_CMD_CLIP_STROKE_TEXT:
		case FZ_CMD_IGNORE_TEXT:
			fz_drop_text(ctx, *(fz_text **)node);
			break;
		case FZ_CMD_FILL_SHADE:
			fz_drop_shade(ctx, *(fz_shade **)node);
			break;
		case FZ_CMD_FILL_IMAGE:
		case FZ_CMD_FILL_IMAGE_MASK:
		case FZ_CMD_CLIP_IMAGE_MASK:
			fz_drop_image(ctx, *(fz_image **)node);
			break;
		case FZ_CMD_BEGIN_GROUP:
			fz_drop_colorspace(ctx, *(fz_colorspace **)node);
			break;
		case FZ_CMD_DEFAULT_COLORSPACES:
			fz_drop_default_colorspaces(ctx, *(fz_default_colorspaces **)node);
			break;
		}
		node = next;
	}
	fz_free(ctx, list->list);
	fz_free(ctx, list);
}