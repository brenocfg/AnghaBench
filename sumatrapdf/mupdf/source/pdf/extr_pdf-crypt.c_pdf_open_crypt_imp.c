#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ method; } ;
typedef  TYPE_1__ pdf_crypt_filter ;
typedef  int /*<<< orphan*/  pdf_crypt ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_CRYPT_AESV2 ; 
 scalar_t__ PDF_CRYPT_AESV3 ; 
 scalar_t__ PDF_CRYPT_RC4 ; 
 int /*<<< orphan*/ * fz_keep_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_open_aesd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * fz_open_arc4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int pdf_compute_object_key (int /*<<< orphan*/ *,TYPE_1__*,int,int,unsigned char*,int) ; 

__attribute__((used)) static fz_stream *
pdf_open_crypt_imp(fz_context *ctx, fz_stream *chain, pdf_crypt *crypt, pdf_crypt_filter *stmf, int num, int gen)
{
	unsigned char key[32];
	int len;

	len = pdf_compute_object_key(crypt, stmf, num, gen, key, 32);

	if (stmf->method == PDF_CRYPT_RC4)
		return fz_open_arc4(ctx, chain, key, len);

	if (stmf->method == PDF_CRYPT_AESV2 || stmf->method == PDF_CRYPT_AESV3)
		return fz_open_aesd(ctx, chain, key, len);

	return fz_keep_stream(ctx, chain);
}