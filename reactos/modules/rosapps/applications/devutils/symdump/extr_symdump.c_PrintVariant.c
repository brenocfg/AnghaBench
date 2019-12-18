#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  lVal; int /*<<< orphan*/  iVal; int /*<<< orphan*/  cVal; } ;
struct TYPE_7__ {int vt; TYPE_1__ n3; } ;
struct TYPE_8__ {TYPE_2__ n2; } ;
struct TYPE_9__ {TYPE_3__ n1; } ;
typedef  TYPE_4__ VARIANT ;
typedef  int UINT ;
typedef  int INT ;

/* Variables and functions */
#define  VT_I1 135 
#define  VT_I2 134 
#define  VT_I4 133 
#define  VT_INT 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UINT 128 
 int /*<<< orphan*/  printf (char*,int) ; 

VOID
PrintVariant(VARIANT *v)
{
//      printf("<vt%d>", v->n1.n2.vt);
	switch (v->n1.n2.vt)
	{
	case VT_I1:
		printf("%d", (INT)v->n1.n2.n3.cVal);
		break;
	case VT_UI1:
		printf("0x%x", (UINT)v->n1.n2.n3.cVal);
		break;
	case VT_I2:
		printf("%d", (UINT)v->n1.n2.n3.iVal);
		break;
	case VT_UI2:
		printf("0x%x", (UINT)v->n1.n2.n3.iVal);
		break;
	case VT_INT:
	case VT_I4:
		printf("%d", (UINT)v->n1.n2.n3.lVal);
		break;
	case VT_UINT:
	case VT_UI4:
		printf("0x%x", (UINT)v->n1.n2.n3.lVal);
		break;
	}
}