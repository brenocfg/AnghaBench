#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {int /*<<< orphan*/  strf; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int pdf_compute_object_key (TYPE_1__*,int /*<<< orphan*/ *,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  pdf_crypt_obj_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned char*,int) ; 

void
pdf_crypt_obj(fz_context *ctx, pdf_crypt *crypt, pdf_obj *obj, int num, int gen)
{
	unsigned char key[32];
	int len;

	len = pdf_compute_object_key(crypt, &crypt->strf, num, gen, key, 32);

	pdf_crypt_obj_imp(ctx, crypt, obj, key, len);
}