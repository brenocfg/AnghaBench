#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ doc; scalar_t__ chapter_num; } ;
typedef  TYPE_1__ fz_html_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static int
fz_cmp_html_key(fz_context *ctx, void *k0_, void *k1_)
{
	fz_html_key *k0 = (fz_html_key *)k0_;
	fz_html_key *k1 = (fz_html_key *)k1_;
	return k0->doc == k1->doc && k0->chapter_num == k1->chapter_num;
}