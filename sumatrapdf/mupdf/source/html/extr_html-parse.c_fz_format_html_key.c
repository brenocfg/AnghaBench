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
struct TYPE_2__ {int /*<<< orphan*/  chapter_num; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ fz_html_key ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_format_html_key(fz_context *ctx, char *s, int n, void *key_)
{
	fz_html_key *key = (fz_html_key *)key_;
	fz_snprintf(s, n, "(html doc=%p, ch=%d)", key->doc, key->chapter_num);
}