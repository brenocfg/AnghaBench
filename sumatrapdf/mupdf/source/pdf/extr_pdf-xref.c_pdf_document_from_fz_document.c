#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_document ;
struct TYPE_3__ {scalar_t__ count_pages; } ;
typedef  TYPE_1__ fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ pdf_count_pages_imp ; 

pdf_document *pdf_document_from_fz_document(fz_context *ctx, fz_document *ptr)
{
	return (pdf_document *)((ptr && ptr->count_pages == pdf_count_pages_imp) ? ptr : NULL);
}