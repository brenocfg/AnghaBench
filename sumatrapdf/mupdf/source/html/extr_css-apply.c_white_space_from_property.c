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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_css_value ;
typedef  int /*<<< orphan*/  fz_css_match ;

/* Variables and functions */
 int WS_NORMAL ; 
 int WS_NOWRAP ; 
 int WS_PRE ; 
 int WS_PRE_LINE ; 
 int WS_PRE_WRAP ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* value_from_property (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
white_space_from_property(fz_css_match *match)
{
	fz_css_value *value = value_from_property(match, "white-space");
	if (value)
	{
		if (!strcmp(value->data, "normal")) return WS_NORMAL;
		else if (!strcmp(value->data, "pre")) return WS_PRE;
		else if (!strcmp(value->data, "nowrap")) return WS_NOWRAP;
		else if (!strcmp(value->data, "pre-wrap")) return WS_PRE_WRAP;
		else if (!strcmp(value->data, "pre-line")) return WS_PRE_LINE;
	}
	return WS_NORMAL;
}