#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dev; } ;
typedef  TYPE_3__ pdf_run_processor ;
typedef  int /*<<< orphan*/  pdf_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {void* y1; void* x1; void* y0; void* x0; } ;
struct TYPE_5__ {int flags; TYPE_1__ d1_rect; } ;

/* Variables and functions */
 int FZ_DEVFLAG_BBOX_DEFINED ; 
 int FZ_DEVFLAG_DASHCAP_UNDEFINED ; 
 int FZ_DEVFLAG_ENDCAP_UNDEFINED ; 
 int FZ_DEVFLAG_FILLCOLOR_UNDEFINED ; 
 int FZ_DEVFLAG_LINEJOIN_UNDEFINED ; 
 int FZ_DEVFLAG_LINEWIDTH_UNDEFINED ; 
 int FZ_DEVFLAG_MASK ; 
 int FZ_DEVFLAG_MITERLIMIT_UNDEFINED ; 
 int FZ_DEVFLAG_STARTCAP_UNDEFINED ; 
 int FZ_DEVFLAG_STROKECOLOR_UNDEFINED ; 
 void* fz_max (float,float) ; 
 void* fz_min (float,float) ; 

__attribute__((used)) static void pdf_run_d1(fz_context *ctx, pdf_processor *proc, float wx, float wy, float llx, float lly, float urx, float ury)
{
	pdf_run_processor *pr = (pdf_run_processor *)proc;
	pr->dev->flags |= FZ_DEVFLAG_MASK | FZ_DEVFLAG_BBOX_DEFINED;
	pr->dev->flags &= ~(FZ_DEVFLAG_FILLCOLOR_UNDEFINED |
				FZ_DEVFLAG_STROKECOLOR_UNDEFINED |
				FZ_DEVFLAG_STARTCAP_UNDEFINED |
				FZ_DEVFLAG_DASHCAP_UNDEFINED |
				FZ_DEVFLAG_ENDCAP_UNDEFINED |
				FZ_DEVFLAG_LINEJOIN_UNDEFINED |
				FZ_DEVFLAG_MITERLIMIT_UNDEFINED |
				FZ_DEVFLAG_LINEWIDTH_UNDEFINED);
	pr->dev->d1_rect.x0 = fz_min(llx, urx);
	pr->dev->d1_rect.y0 = fz_min(lly, ury);
	pr->dev->d1_rect.x1 = fz_max(llx, urx);
	pr->dev->d1_rect.y1 = fz_max(lly, ury);
}