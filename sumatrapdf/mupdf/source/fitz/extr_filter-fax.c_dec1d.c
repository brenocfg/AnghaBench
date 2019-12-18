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
struct TYPE_4__ {int a; int c; int columns; int /*<<< orphan*/  stage; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ fz_faxd ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  STATE_MAKEUP ; 
 int /*<<< orphan*/  STATE_NORMAL ; 
 int UNCOMPRESSED ; 
 int /*<<< orphan*/  cf_black_decode ; 
 int /*<<< orphan*/  cf_white_decode ; 
 int /*<<< orphan*/  cfd_black_initial_bits ; 
 int /*<<< orphan*/  cfd_white_initial_bits ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int get_code (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbits (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
dec1d(fz_context *ctx, fz_faxd *fax)
{
	int code;

	if (fax->a == -1)
		fax->a = 0;

	if (fax->c)
		code = get_code(ctx, fax, cf_black_decode, cfd_black_initial_bits);
	else
		code = get_code(ctx, fax, cf_white_decode, cfd_white_initial_bits);

	if (code == UNCOMPRESSED)
		fz_throw(ctx, FZ_ERROR_GENERIC, "uncompressed data in faxd");

	if (code < 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "negative code in 1d faxd");

	if (fax->a + code > fax->columns)
		fz_throw(ctx, FZ_ERROR_GENERIC, "overflow in 1d faxd");

	if (fax->c)
		setbits(fax->dst, fax->a, fax->a + code);

	fax->a += code;

	if (code < 64)
	{
		fax->c = !fax->c;
		fax->stage = STATE_NORMAL;
	}
	else
		fax->stage = STATE_MAKEUP;
}