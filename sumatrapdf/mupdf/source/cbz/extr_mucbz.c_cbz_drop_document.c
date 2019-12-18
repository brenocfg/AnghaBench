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
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {scalar_t__ page; int /*<<< orphan*/  arch; } ;
typedef  TYPE_1__ cbz_document ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static void
cbz_drop_document(fz_context *ctx, fz_document *doc_)
{
	cbz_document *doc = (cbz_document*)doc_;
	fz_drop_archive(ctx, doc->arch);
	fz_free(ctx, (char **)doc->page);
}