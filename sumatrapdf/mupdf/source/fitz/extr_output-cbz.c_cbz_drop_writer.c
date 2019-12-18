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
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  pixmap; int /*<<< orphan*/  zip; } ;
typedef  TYPE_1__ fz_cbz_writer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_zip_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbz_drop_writer(fz_context *ctx, fz_document_writer *wri_)
{
	fz_cbz_writer *wri = (fz_cbz_writer*)wri_;
	fz_drop_zip_writer(ctx, wri->zip);
	fz_drop_pixmap(ctx, wri->pixmap);
}