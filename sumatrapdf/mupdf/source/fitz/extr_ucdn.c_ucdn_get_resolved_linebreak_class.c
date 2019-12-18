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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int linebreak_class; int /*<<< orphan*/  category; } ;
typedef  TYPE_1__ UCDRecord ;

/* Variables and functions */
 int /*<<< orphan*/  UCDN_GENERAL_CATEGORY_MC ; 
 int /*<<< orphan*/  UCDN_GENERAL_CATEGORY_MN ; 
#define  UCDN_LINEBREAK_CLASS_AI 134 
 int UCDN_LINEBREAK_CLASS_AL ; 
 int UCDN_LINEBREAK_CLASS_B2 ; 
 int UCDN_LINEBREAK_CLASS_BK ; 
#define  UCDN_LINEBREAK_CLASS_CB 133 
#define  UCDN_LINEBREAK_CLASS_CJ 132 
 int UCDN_LINEBREAK_CLASS_CM ; 
#define  UCDN_LINEBREAK_CLASS_NL 131 
 int UCDN_LINEBREAK_CLASS_NS ; 
#define  UCDN_LINEBREAK_CLASS_SA 130 
#define  UCDN_LINEBREAK_CLASS_SG 129 
#define  UCDN_LINEBREAK_CLASS_XX 128 
 TYPE_1__* get_ucd_record (int /*<<< orphan*/ ) ; 

int ucdn_get_resolved_linebreak_class(uint32_t code)
{
	const UCDRecord *record = get_ucd_record(code);

	switch (record->linebreak_class)
	{
	case UCDN_LINEBREAK_CLASS_AI:
	case UCDN_LINEBREAK_CLASS_SG:
	case UCDN_LINEBREAK_CLASS_XX:
		return UCDN_LINEBREAK_CLASS_AL;

	case UCDN_LINEBREAK_CLASS_SA:
		if (record->category == UCDN_GENERAL_CATEGORY_MC ||
			record->category == UCDN_GENERAL_CATEGORY_MN)
			return UCDN_LINEBREAK_CLASS_CM;
		return UCDN_LINEBREAK_CLASS_AL;

	case UCDN_LINEBREAK_CLASS_CJ:
		return UCDN_LINEBREAK_CLASS_NS;

	case UCDN_LINEBREAK_CLASS_CB:
		return UCDN_LINEBREAK_CLASS_B2;

	case UCDN_LINEBREAK_CLASS_NL:
		return UCDN_LINEBREAK_CLASS_BK;

	default:
		return record->linebreak_class;
	}
}