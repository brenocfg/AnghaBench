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
typedef  enum pdf_signature_error { ____Placeholder_pdf_signature_error } pdf_signature_error ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

enum pdf_signature_error pdf_check_certificate(fz_context *ctx, pdf_document *doc, pdf_obj *signature)
{
	fz_throw(ctx, FZ_ERROR_GENERIC, "No OpenSSL support.");
	return 0;
}