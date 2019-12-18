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
typedef  int icTagTypeSignature ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_byte_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_append_int16_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  fz_append_int32_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_gammadata(fz_context *ctx, fz_buffer *buf, unsigned short gamma, icTagTypeSignature curveType)
{
	fz_append_int32_be(ctx, buf, curveType);
	fz_append_byte_n(ctx, buf, 0, 4);

	/* one entry for gamma */
	fz_append_int32_be(ctx, buf, 1);

	/* The encode (8frac8) gamma, with padding */
	fz_append_int16_be(ctx, buf, gamma);

	/* pad two bytes */
	fz_append_byte_n(ctx, buf, 0, 2);
}