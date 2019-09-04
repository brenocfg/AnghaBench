#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct layout_cell {int type; int /*<<< orphan*/  cells; void* yoff; void* xoff; void* sy; void* sx; } ;

/* Variables and functions */
#define  LAYOUT_LEFTRIGHT 129 
#define  LAYOUT_TOPBOTTOM 128 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct layout_cell*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 struct layout_cell* layout_create_cell (struct layout_cell*) ; 
 int /*<<< orphan*/  layout_free_cell (struct layout_cell*) ; 
 int sscanf (char const*,char*,void**,void**,void**,void**) ; 

__attribute__((used)) static struct layout_cell *
layout_construct(struct layout_cell *lcparent, const char **layout)
{
	struct layout_cell     *lc, *lcchild;
	u_int			sx, sy, xoff, yoff;
	const char	       *saved;

	if (!isdigit((u_char) **layout))
		return (NULL);
	if (sscanf(*layout, "%ux%u,%u,%u", &sx, &sy, &xoff, &yoff) != 4)
		return (NULL);

	while (isdigit((u_char) **layout))
		(*layout)++;
	if (**layout != 'x')
		return (NULL);
	(*layout)++;
	while (isdigit((u_char) **layout))
		(*layout)++;
	if (**layout != ',')
		return (NULL);
	(*layout)++;
	while (isdigit((u_char) **layout))
		(*layout)++;
	if (**layout != ',')
		return (NULL);
	(*layout)++;
	while (isdigit((u_char) **layout))
		(*layout)++;
	if (**layout == ',') {
		saved = *layout;
		(*layout)++;
		while (isdigit((u_char) **layout))
			(*layout)++;
		if (**layout == 'x')
			*layout = saved;
	}

	lc = layout_create_cell(lcparent);
	lc->sx = sx;
	lc->sy = sy;
	lc->xoff = xoff;
	lc->yoff = yoff;

	switch (**layout) {
	case ',':
	case '}':
	case ']':
	case '\0':
		return (lc);
	case '{':
		lc->type = LAYOUT_LEFTRIGHT;
		break;
	case '[':
		lc->type = LAYOUT_TOPBOTTOM;
		break;
	default:
		goto fail;
	}

	do {
		(*layout)++;
		lcchild = layout_construct(lc, layout);
		if (lcchild == NULL)
			goto fail;
		TAILQ_INSERT_TAIL(&lc->cells, lcchild, entry);
	} while (**layout == ',');

	switch (lc->type) {
	case LAYOUT_LEFTRIGHT:
		if (**layout != '}')
			goto fail;
		break;
	case LAYOUT_TOPBOTTOM:
		if (**layout != ']')
			goto fail;
		break;
	default:
		goto fail;
	}
	(*layout)++;

	return (lc);

fail:
	layout_free_cell(lc);
	return (NULL);
}