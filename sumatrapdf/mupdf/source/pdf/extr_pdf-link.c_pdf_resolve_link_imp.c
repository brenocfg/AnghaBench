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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_location ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_make_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_resolve_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,float*,float*) ; 

fz_location
pdf_resolve_link_imp(fz_context *ctx, fz_document *doc_, const char *uri, float *xp, float *yp)
{
	pdf_document *doc = (pdf_document*)doc_;
	return fz_make_location(0, pdf_resolve_link(ctx, doc, uri, xp, yp));
}