#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* text; } ;
struct TYPE_8__ {int type; double y; double x; double w; double h; struct TYPE_8__* next; scalar_t__ breaks_line; TYPE_2__ content; TYPE_4__* box; } ;
typedef  TYPE_3__ fz_html_flow ;
struct TYPE_9__ {double em; TYPE_1__* style; } ;
typedef  TYPE_4__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {scalar_t__ small_caps; int /*<<< orphan*/  font; } ;

/* Variables and functions */
#define  FLOW_ANCHOR 134 
#define  FLOW_BREAK 133 
#define  FLOW_IMAGE 132 
#define  FLOW_SBREAK 131 
#define  FLOW_SHYPHEN 130 
#define  FLOW_SPACE 129 
#define  FLOW_WORD 128 
 scalar_t__ fz_font_is_bold (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_font_is_italic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_font_is_monospaced (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_font_is_serif (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fz_font_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indent (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
fz_debug_html_flow(fz_context *ctx, fz_html_flow *flow, int level)
{
	fz_html_box *sbox = NULL;
	while (flow)
	{
		if (flow->box != sbox) {
			if (sbox) {
				indent(level);
				printf("}\n");
			}
			sbox = flow->box;
			indent(level);
			printf("span em=%g font='%s'", sbox->em, fz_font_name(ctx, sbox->style->font));
			if (fz_font_is_serif(ctx, sbox->style->font))
				printf(" serif");
			else
				printf(" sans");
			if (fz_font_is_monospaced(ctx, sbox->style->font))
				printf(" monospaced");
			if (fz_font_is_bold(ctx, sbox->style->font))
				printf(" bold");
			if (fz_font_is_italic(ctx, sbox->style->font))
				printf(" italic");
			if (sbox->style->small_caps)
				printf(" small-caps");
			printf("\n");
			indent(level);
			printf("{\n");
		}

		indent(level+1);
		switch (flow->type) {
		case FLOW_WORD: printf("word "); break;
		case FLOW_SPACE: printf("space"); break;
		case FLOW_SBREAK: printf("sbrk "); break;
		case FLOW_SHYPHEN: printf("shy  "); break;
		case FLOW_BREAK: printf("break"); break;
		case FLOW_IMAGE: printf("image"); break;
		case FLOW_ANCHOR: printf("anchor"); break;
		}
		printf(" y=%g x=%g w=%g", flow->y, flow->x, flow->w);
		if (flow->type == FLOW_IMAGE)
			printf(" h=%g", flow->h);
		if (flow->type == FLOW_WORD)
			printf(" text='%s'", flow->content.text);
		printf("\n");
		if (flow->breaks_line) {
			indent(level+1);
			printf("*\n");
		}

		flow = flow->next;
	}
	indent(level);
	printf("}\n");
}