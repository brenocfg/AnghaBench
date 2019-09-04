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
 int _FPCLASS_ND ; 
 int _FPCLASS_NINF ; 
 int _FPCLASS_NN ; 
 int _FPCLASS_NZ ; 
 int _FPCLASS_PD ; 
 int _FPCLASS_PINF ; 
 int _FPCLASS_PN ; 
 int _FPCLASS_PZ ; 
 int _FPCLASS_QNAN ; 
 int _fpclass (double) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

void test_fpclass(void)
{
    int class;
    ieee_double tested;

    tested.l = 0xFFFFFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0xFFF8000000000001LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0xFFF8000000000000LL;
    class = _fpclass(tested.d);
    /* Normally it has no class, but w2k3 defines it
     * like that
     */
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0xFFF7FFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    /* According to IEEE, it should be Signaling NaN, but
     * on w2k3, it's Quiet NAN
     * ok(class == _FPCLASS_SNAN, "class = %d\n", class);
     */
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0xFFF0000000000001LL;
    class = _fpclass(tested.d);
    /* According to IEEE, it should be Signaling NaN, but
     * on w2k3, it's Quiet NAN
     * ok(class == _FPCLASS_SNAN, "class = %d\n", class);
     */
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0xFFF0000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_NINF, "class = %d\n", class);
    tested.l = 0xFFEFFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_NN, "class = %d\n", class);
    tested.l = 0x8010000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_NN, "class = %d\n", class);
    tested.l = 0x800FFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_ND, "class = %d\n", class);
    tested.l = 0x8000000000000001LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_ND, "class = %d\n", class);
    tested.l = 0x8000000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_NZ, "class = %d\n", class);
    tested.l = 0x0000000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PZ, "class = %d\n", class);
    tested.l = 0x0000000000000001LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PD, "class = %d\n", class);
    tested.l = 0x000FFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PD, "class = %d\n", class);
    tested.l = 0x0010000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PN, "class = %d\n", class);
    tested.l = 0x7FEFFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PN, "class = %d\n", class);
    tested.l = 0x7FF0000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_PINF, "class = %d\n", class);
    tested.l = 0x7FF0000000000001LL;
    class = _fpclass(tested.d);
    /* According to IEEE, it should be Signaling NaN, but
     * on w2k3, it's Quiet NAN
     * ok(class == _FPCLASS_SNAN, "class = %d\n", class);
     */
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0x7FF7FFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    /* According to IEEE, it should be Signaling NaN, but
     * on w2k3, it's Quiet NAN
     * ok(class == _FPCLASS_SNAN, "class = %d\n", class);
     */
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0x7FF8000000000000LL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);
    tested.l = 0x7FFFFFFFFFFFFFFFLL;
    class = _fpclass(tested.d);
    ok(class == _FPCLASS_QNAN, "class = %d\n", class);

    /* MSDN example */
    class = _fpclass(2.387000);
    ok(class == _FPCLASS_PN, "class = %d\n", class);
}