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
typedef  int /*<<< orphan*/  fz_xml ;
struct TYPE_3__ {char combine; scalar_t__ cond; scalar_t__ name; struct TYPE_3__* right; struct TYPE_3__* left; } ;
typedef  TYPE_1__ fz_css_selector ;

/* Variables and functions */
 int /*<<< orphan*/  fz_xml_is_tag (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * fz_xml_prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_xml_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_condition (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
match_selector(fz_css_selector *sel, fz_xml *node)
{
	if (!node)
		return 0;

	if (sel->combine)
	{
		/* descendant */
		if (sel->combine == ' ')
		{
			fz_xml *parent = fz_xml_up(node);
			while (parent)
			{
				if (match_selector(sel->left, parent))
					if (match_selector(sel->right, node))
						return 1;
				parent = fz_xml_up(parent);
			}
			return 0;
		}

		/* child */
		if (sel->combine == '>')
		{
			fz_xml *parent = fz_xml_up(node);
			if (!parent)
				return 0;
			if (!match_selector(sel->left, parent))
				return 0;
			if (!match_selector(sel->right, node))
				return 0;
		}

		/* adjacent */
		if (sel->combine == '+')
		{
			fz_xml *prev = fz_xml_prev(node);
			while (prev && !fz_xml_tag(prev))
				prev = fz_xml_prev(prev);
			if (!prev)
				return 0;
			if (!fz_xml_tag(prev))
				return 0;
			if (!match_selector(sel->left, prev))
				return 0;
			if (!match_selector(sel->right, node))
				return 0;
		}
	}

	if (sel->name)
	{
		if (!fz_xml_is_tag(node, sel->name))
			return 0;
	}

	if (sel->cond)
	{
		if (!match_condition(sel->cond, node))
			return 0;
	}

	return 1;
}