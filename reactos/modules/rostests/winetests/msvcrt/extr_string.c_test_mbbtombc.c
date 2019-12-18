#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int _MB_CP_SBCS ; 
 int _getmbcp () ; 
 unsigned int _mbbtombc (unsigned int const) ; 
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,unsigned int,unsigned int const,int) ; 

__attribute__((used)) static void test_mbbtombc(void)
{
    static const unsigned int mbbmbc[][2] = {
        {0x1f, 0x1f}, {0x20, 0x8140}, {0x39, 0x8258}, {0x40, 0x8197},
        {0x41, 0x8260}, {0x5e, 0x814f}, {0x7e, 0x8150}, {0x7f, 0x7f},
        {0x80, 0x80}, {0x81, 0x81}, {0xa0, 0xa0}, {0xa7, 0x8340},
        {0xb0, 0x815b}, {0xd1, 0x8380}, {0xff, 0xff}, {0,0}};
    int cp[] = { 932, 936, 939, 950, 1361, _MB_CP_SBCS };
    int i, j;
    int prev_cp = _getmbcp();

    for (i = 0; i < ARRAY_SIZE(cp); i++)
    {
        _setmbcp(cp[i]);
        for (j = 0; mbbmbc[j][0] != 0; j++)
        {
            unsigned int exp, ret;
            ret = _mbbtombc(mbbmbc[j][0]);
            exp = (cp[i] == 932) ? mbbmbc[j][1] : mbbmbc[j][0];
            ok(ret == exp, "Expected 0x%x, got 0x%x (0x%x, codepage %d)\n",
               exp, ret, mbbmbc[j][0], cp[i]);
        }
    }
    _setmbcp(prev_cp);
}