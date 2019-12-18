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
struct TYPE_4__ {void* eDy; void* eDx; void* eM22; void* eM21; void* eM12; void* eM11; } ;
typedef  TYPE_1__ XFORML ;
typedef  int /*<<< orphan*/  XFORM ;
struct TYPE_5__ {int /*<<< orphan*/  efDy; int /*<<< orphan*/  efDx; int /*<<< orphan*/  efM22; int /*<<< orphan*/  efM21; int /*<<< orphan*/  efM12; int /*<<< orphan*/  efM11; } ;
typedef  TYPE_2__ MATRIX ;

/* Variables and functions */
 void* FOtoF (int /*<<< orphan*/ *) ; 

void
MatrixToXForm(XFORM *pxform, const MATRIX *pmx)
{
    XFORML *pxforml = (XFORML*)pxform;
    pxforml->eM11 = FOtoF(&pmx->efM11);
    pxforml->eM12 = FOtoF(&pmx->efM12);
    pxforml->eM21 = FOtoF(&pmx->efM21);
    pxforml->eM22 = FOtoF(&pmx->efM22);
    pxforml->eDx = FOtoF(&pmx->efDx);
    pxforml->eDy = FOtoF(&pmx->efDy);
}