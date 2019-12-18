#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int kind; } ;
typedef  TYPE_1__ pdf_obj ;

/* Variables and functions */
#define  PDF_ARRAY 134 
#define  PDF_DICT 133 
 TYPE_1__* PDF_FALSE ; 
#define  PDF_INDIRECT 132 
#define  PDF_INT 131 
 TYPE_1__* PDF_LIMIT ; 
#define  PDF_NAME 130 
 TYPE_1__* PDF_NULL ; 
#define  PDF_REAL 129 
#define  PDF_STRING 128 
 TYPE_1__* PDF_TRUE ; 

__attribute__((used)) static char *
pdf_objkindstr(pdf_obj *obj)
{
	if (obj == PDF_NULL)
		return "null";
	if (obj == PDF_TRUE || obj == PDF_FALSE)
		return "boolean";
	if (obj < PDF_LIMIT)
		return "name";
	switch (obj->kind)
	{
	case PDF_INT: return "integer";
	case PDF_REAL: return "real";
	case PDF_STRING: return "string";
	case PDF_NAME: return "name";
	case PDF_ARRAY: return "array";
	case PDF_DICT: return "dictionary";
	case PDF_INDIRECT: return "reference";
	}
	return "<unknown>";
}