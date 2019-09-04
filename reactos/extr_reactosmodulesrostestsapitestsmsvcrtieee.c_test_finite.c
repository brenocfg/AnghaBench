#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int l; double d; } ;
typedef  TYPE_1__ ieee_double ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ _finite (double) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void test_finite(void)
{
    ieee_double tested;

    tested.l = 0xFFFFFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFF8000000000001LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFF8000000000000LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFF7FFFFFFFFFFFFLL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFF0000000000001LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFF0000000000000LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0xFFEFFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x8010000000000000LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x800FFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x8000000000000001LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x8000000000000000LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x0000000000000000LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x0000000000000001LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x000FFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x0010000000000000LL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x7FEFFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == TRUE, "_finite = FALSE\n");
    tested.l = 0x7FF0000000000000LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0x7FF0000000000001LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0x7FF7FFFFFFFFFFFFLL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0x7FF8000000000000LL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");
    tested.l = 0x7FFFFFFFFFFFFFFFLL;
    ok(_finite(tested.d) == FALSE, "_finite = TRUE\n");

    /* MSDN example */
    ok(_finite(2.387000) == TRUE, "_finite = FALSE\n");
}