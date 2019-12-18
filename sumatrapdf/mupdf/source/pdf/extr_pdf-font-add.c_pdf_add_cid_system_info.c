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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  CIDSystemInfo ; 
 int /*<<< orphan*/  Ordering ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Registry ; 
 int /*<<< orphan*/  Supplement ; 
 int /*<<< orphan*/ * pdf_dict_put_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_dict_put_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
pdf_add_cid_system_info(fz_context *ctx, pdf_document *doc, pdf_obj *fobj, const char *reg, const char *ord, int supp)
{
	pdf_obj *csi = pdf_dict_put_dict(ctx, fobj, PDF_NAME(CIDSystemInfo), 3);
	pdf_dict_put_string(ctx, csi, PDF_NAME(Registry), reg, strlen(reg));
	pdf_dict_put_string(ctx, csi, PDF_NAME(Ordering), ord, strlen(ord));
	pdf_dict_put_int(ctx, csi, PDF_NAME(Supplement), supp);
}