#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int rtfMajor; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CharAttr (TYPE_1__*) ; 
 int /*<<< orphan*/  CharSet (TYPE_1__*) ; 
 int /*<<< orphan*/  DefFont (TYPE_1__*) ; 
 int /*<<< orphan*/  Destination (TYPE_1__*) ; 
 int /*<<< orphan*/  DocAttr (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_RTFCharAttrHook (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_RTFParAttrHook (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_RTFSpecialCharHook (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_RTFTblAttrHook (TYPE_1__*) ; 
 int /*<<< orphan*/  SpecialChar (TYPE_1__*) ; 
#define  rtfCharAttr 135 
#define  rtfCharSet 134 
#define  rtfDefFont 133 
#define  rtfDestination 132 
#define  rtfDocAttr 131 
#define  rtfParAttr 130 
#define  rtfSpecialChar 129 
#define  rtfTblAttr 128 

__attribute__((used)) static void
ControlClass (RTF_Info *info)
{
	switch (info->rtfMajor)
	{
        case rtfCharAttr:
                CharAttr(info);
                ME_RTFCharAttrHook(info);
                break;
        case rtfParAttr:
                ME_RTFParAttrHook(info);
                break;
        case rtfTblAttr:
                ME_RTFTblAttrHook(info);
                break;
        case rtfCharSet:
                CharSet(info);
                break;
        case rtfDefFont:
                DefFont(info);
                break;
	case rtfDestination:
		Destination (info);
		break;
        case rtfDocAttr:
                DocAttr(info);
                break;
	case rtfSpecialChar:
                SpecialChar (info);
                ME_RTFSpecialCharHook(info);
		break;
	}
}