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
 unsigned int ARRAY_SIZE (unsigned int const**) ; 
 unsigned int _MB_CP_SBCS ; 
 unsigned int _getmbcp () ; 
 void* _mbctohira (unsigned int const) ; 
 int /*<<< orphan*/  _setmbcp (unsigned int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void test_mbctohira(void)
{
    static const unsigned int mbchira_932[][2] = {
        {0x8152, 0x8152}, {0x8153, 0x8153}, {0x8154, 0x8154}, {0x8155, 0x8155},
        {0x82a0, 0x82a0}, {0x833f, 0x833f}, {0x8340, 0x829f}, {0x837e, 0x82dd},
        {0x837f, 0x837f}, {0x8380, 0x82de}, {0x8393, 0x82f1}, {0x8394, 0x8394},
        {0x8396, 0x8396}, {0x8397, 0x8397},
        {0xa5, 0xa5}, {0xb0, 0xb0}, {0xdd, 0xdd} };
    unsigned int i;
    unsigned int prev_cp = _getmbcp();

    _setmbcp(_MB_CP_SBCS);
    for (i = 0; i < ARRAY_SIZE(mbchira_932); i++)
    {
        int ret, exp = mbchira_932[i][0];
        ret = _mbctohira(mbchira_932[i][0]);
        ok(ret == exp, "Expected 0x%x, got 0x%x\n", exp, ret);
    }

    _setmbcp(932);
    for (i = 0; i < ARRAY_SIZE(mbchira_932); i++)
    {
        unsigned int ret, exp;
        ret = _mbctohira(mbchira_932[i][0]);
        exp = mbchira_932[i][1];
        ok(ret == exp, "Expected 0x%x, got 0x%x\n", exp, ret);
    }
    _setmbcp(prev_cp);
}