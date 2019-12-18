#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ kind; } ;
typedef  TYPE_2__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {scalar_t__ f; scalar_t__ i; } ;
struct TYPE_10__ {TYPE_1__ u; } ;

/* Variables and functions */
 TYPE_6__* NUM (TYPE_2__*) ; 
 scalar_t__ PDF_INT ; 
 TYPE_2__* PDF_LIMIT ; 
 scalar_t__ PDF_REAL ; 
 int /*<<< orphan*/  RESOLVE (TYPE_2__*) ; 

int pdf_to_int(fz_context *ctx, pdf_obj *obj)
{
	RESOLVE(obj);
	if (obj < PDF_LIMIT)
		return 0;
	if (obj->kind == PDF_INT)
		return (int)NUM(obj)->u.i;
	if (obj->kind == PDF_REAL)
		return (int)(NUM(obj)->u.f + 0.5f); /* No roundf in MSVC */
	return 0;
}