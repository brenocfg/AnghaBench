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
typedef  int /*<<< orphan*/  fz_outline ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  outline; } ;
typedef  TYPE_1__ epub_document ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_keep_outline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_outline *
epub_load_outline(fz_context *ctx, fz_document *doc_)
{
	epub_document *doc = (epub_document*)doc_;
	return fz_keep_outline(ctx, doc->outline);
}