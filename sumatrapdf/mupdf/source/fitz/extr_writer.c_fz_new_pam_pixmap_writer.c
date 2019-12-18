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
typedef  int /*<<< orphan*/  fz_document_writer ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_pixmap_writer (int /*<<< orphan*/ *,char const*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_save_pixmap_as_pam ; 

fz_document_writer *fz_new_pam_pixmap_writer(fz_context *ctx, const char *path, const char *options)
{
	return fz_new_pixmap_writer(ctx, path, options, "out-%04d.pam", 0, fz_save_pixmap_as_pam);
}