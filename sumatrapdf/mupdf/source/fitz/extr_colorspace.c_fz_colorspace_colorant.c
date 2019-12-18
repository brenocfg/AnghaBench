#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {char const** colorant; } ;
struct TYPE_6__ {TYPE_1__ separation; } ;
struct TYPE_7__ {int n; int type; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_colorspace ;

/* Variables and functions */
#define  FZ_COLORSPACE_BGR 135 
#define  FZ_COLORSPACE_CMYK 134 
#define  FZ_COLORSPACE_GRAY 133 
#define  FZ_COLORSPACE_INDEXED 132 
#define  FZ_COLORSPACE_LAB 131 
#define  FZ_COLORSPACE_NONE 130 
#define  FZ_COLORSPACE_RGB 129 
#define  FZ_COLORSPACE_SEPARATION 128 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

const char *fz_colorspace_colorant(fz_context *ctx, fz_colorspace *cs, int i)
{
	if (!cs || i < 0 || i >= cs->n)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Colorant out of range");
	switch (cs->type)
	{
	case FZ_COLORSPACE_NONE:
		return "None";
	case FZ_COLORSPACE_GRAY:
		return "Gray";
	case FZ_COLORSPACE_RGB:
		if (i == 0) return "Red";
		if (i == 1) return "Green";
		if (i == 2) return "Blue";
		break;
	case FZ_COLORSPACE_BGR:
		if (i == 0) return "Blue";
		if (i == 1) return "Green";
		if (i == 2) return "Red";
		break;
	case FZ_COLORSPACE_CMYK:
		if (i == 0) return "Cyan";
		if (i == 1) return "Magenta";
		if (i == 2) return "Yellow";
		if (i == 3) return "Black";
		break;
	case FZ_COLORSPACE_LAB:
		if (i == 0) return "L*";
		if (i == 1) return "a*";
		if (i == 2) return "b*";
		break;
	case FZ_COLORSPACE_INDEXED:
		return "Index";
	case FZ_COLORSPACE_SEPARATION:
		return cs->u.separation.colorant[i];
	}
	return "None";
}