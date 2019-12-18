#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int kind; } ;
typedef  TYPE_1__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_13__ {int parent_num; } ;
struct TYPE_12__ {int parent_num; } ;
struct TYPE_11__ {int num; } ;

/* Variables and functions */
 TYPE_8__* ARRAY (TYPE_1__*) ; 
 TYPE_6__* DICT (TYPE_1__*) ; 
#define  PDF_ARRAY 130 
#define  PDF_DICT 129 
#define  PDF_INDIRECT 128 
 TYPE_1__* PDF_LIMIT ; 
 TYPE_3__* REF (TYPE_1__*) ; 

int pdf_obj_parent_num(fz_context *ctx, pdf_obj *obj)
{
	if (obj < PDF_LIMIT)
		return 0;

	switch (obj->kind)
	{
	case PDF_INDIRECT:
		return REF(obj)->num;
	case PDF_ARRAY:
		return ARRAY(obj)->parent_num;
	case PDF_DICT:
		return DICT(obj)->parent_num;
	default:
		return 0;
	}
}