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
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ fz_html ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_pool_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
fz_html_size(fz_context *ctx, fz_html *html)
{
	return html ? fz_pool_size(ctx, html->pool) : 0;
}