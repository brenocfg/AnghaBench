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
struct TYPE_4__ {int /*<<< orphan*/  crypt; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ pdf_authenticate_password (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 

int
pdf_needs_password(fz_context *ctx, pdf_document *doc)
{
	if (!doc->crypt)
		return 0;
	if (pdf_authenticate_password(ctx, doc, ""))
		return 0;
	return 1;
}