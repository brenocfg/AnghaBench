#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ eDy; scalar_t__ eDx; scalar_t__ eM22; scalar_t__ eM21; scalar_t__ eM12; scalar_t__ eM11; } ;
typedef  TYPE_1__ XFORM ;

/* Variables and functions */
 double fabs (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void xform_near_match(int line, XFORM *got, XFORM *expect)
{
    ok(fabs(got->eM11 - expect->eM11) < 0.001, "%d: got %f expect %f\n", line, got->eM11, expect->eM11);
    ok(fabs(got->eM12 - expect->eM12) < 0.001, "%d: got %f expect %f\n", line, got->eM12, expect->eM12);
    ok(fabs(got->eM21 - expect->eM21) < 0.001, "%d: got %f expect %f\n", line, got->eM21, expect->eM21);
    ok(fabs(got->eM22 - expect->eM22) < 0.001, "%d: got %f expect %f\n", line, got->eM22, expect->eM22);
    ok(fabs(got->eDx - expect->eDx) < 0.001, "%d: got %f expect %f\n", line, got->eDx, expect->eDx);
    ok(fabs(got->eDy - expect->eDy) < 0.001, "%d: got %f expect %f\n", line, got->eDy, expect->eDy);
}