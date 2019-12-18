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
typedef  int fz_permission ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int p; } ;

/* Variables and functions */
#define  FZ_PERMISSION_ANNOTATE 131 
#define  FZ_PERMISSION_COPY 130 
#define  FZ_PERMISSION_EDIT 129 
#define  FZ_PERMISSION_PRINT 128 
 int PDF_PERM_ANNOTATE ; 
 int PDF_PERM_COPY ; 
 int PDF_PERM_MODIFY ; 
 int PDF_PERM_PRINT ; 

int
pdf_has_permission(fz_context *ctx, pdf_document *doc, fz_permission p)
{
	if (!doc->crypt)
		return 1;
	switch (p)
	{
	case FZ_PERMISSION_PRINT: return doc->crypt->p & PDF_PERM_PRINT;
	case FZ_PERMISSION_COPY: return doc->crypt->p & PDF_PERM_COPY;
	case FZ_PERMISSION_EDIT: return doc->crypt->p & PDF_PERM_MODIFY;
	case FZ_PERMISSION_ANNOTATE: return doc->crypt->p & PDF_PERM_ANNOTATE;
	}
	return 1;
}