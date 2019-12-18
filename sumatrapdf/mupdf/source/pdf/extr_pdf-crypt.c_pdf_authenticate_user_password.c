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
struct TYPE_4__ {int r; int /*<<< orphan*/  u; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_compute_user_password (int /*<<< orphan*/ *,TYPE_1__*,unsigned char*,size_t,unsigned char*) ; 

__attribute__((used)) static int
pdf_authenticate_user_password(fz_context *ctx, pdf_crypt *crypt, unsigned char *password, size_t pwlen)
{
	unsigned char output[32];
	pdf_compute_user_password(ctx, crypt, password, pwlen, output);
	if (crypt->r == 2 || crypt->r == 5 || crypt->r == 6)
		return memcmp(output, crypt->u, 32) == 0;
	if (crypt->r == 3 || crypt->r == 4)
		return memcmp(output, crypt->u, 16) == 0;
	return 0;
}