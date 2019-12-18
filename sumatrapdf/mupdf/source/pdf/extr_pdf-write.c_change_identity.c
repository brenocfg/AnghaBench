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
 int /*<<< orphan*/  fz_memrnd (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_array_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_new_string (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
change_identity(fz_context *ctx, pdf_document *doc, pdf_obj *id)
{
	unsigned char rnd[16];
	if (pdf_array_len(ctx, id) >= 2)
	{
		/* Update second half of ID array with new random data. */
		fz_memrnd(ctx, rnd, 16);
		pdf_array_put_drop(ctx, id, 1, pdf_new_string(ctx, (char *)rnd, 16));
	}
}