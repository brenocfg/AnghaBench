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
struct TYPE_4__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_1__ RECT ;
typedef  int BOOL ;

/* Variables and functions */
 int abs (scalar_t__) ; 

__attribute__((used)) static BOOL is_equal_rect(const RECT *rc1, const RECT *rc2)
{
    return abs(rc1->left - rc2->left) <= 1 &&
           abs(rc1->top - rc2->top) <= 1 &&
           abs(rc1->right - rc2->right) <= 1 &&
           abs(rc1->bottom - rc2->bottom) <= 1;
}