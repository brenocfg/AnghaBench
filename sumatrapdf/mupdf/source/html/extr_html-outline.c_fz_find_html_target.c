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
struct TYPE_3__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ fz_html ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float find_box_target (int /*<<< orphan*/ ,char const*) ; 

float
fz_find_html_target(fz_context *ctx, fz_html *html, const char *id)
{
	return find_box_target(html->root, id);
}