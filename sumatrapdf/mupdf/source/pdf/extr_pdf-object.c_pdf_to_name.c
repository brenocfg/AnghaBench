#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {char const* n; } ;

/* Variables and functions */
 TYPE_5__* NAME (TYPE_1__*) ; 
 TYPE_1__* PDF_LIMIT ; 
 scalar_t__ PDF_NAME ; 
 char const** PDF_NAME_LIST ; 
 int /*<<< orphan*/  RESOLVE (TYPE_1__*) ; 

const char *pdf_to_name(fz_context *ctx, pdf_obj *obj)
{
	RESOLVE(obj);
	if (obj < PDF_LIMIT)
		return PDF_NAME_LIST[((intptr_t)obj)];
	if (obj->kind == PDF_NAME)
		return NAME(obj)->n;
	return "";
}