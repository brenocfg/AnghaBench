#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* crypt; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int p; } ;

/* Variables and functions */

int
pdf_document_permissions(fz_context *ctx, pdf_document *doc)
{
	if (doc->crypt)
		return doc->crypt->p;
	/* all permissions granted, reserved bits set appropriately */
	return (int)0xFFFFFFFC;
}