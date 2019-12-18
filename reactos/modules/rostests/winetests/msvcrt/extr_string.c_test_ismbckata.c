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
typedef  int /*<<< orphan*/  UINT ;
typedef  int BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct katakana_pair const*) ; 
#define  FALSE 129 
#define  TRUE 128 
 unsigned int _MB_CP_SBCS ; 
 unsigned int _getmbcp () ; 
 int _ismbckata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmbcp (unsigned int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 

__attribute__((used)) static void test_ismbckata(void) {
    struct katakana_pair {
        UINT c;
        BOOL exp;
    };
    static const struct katakana_pair tests[] = {
        {0x8152, FALSE}, {0x8153, FALSE}, {0x8154, FALSE}, {0x8155, FALSE},
        {0x82a0, FALSE}, {0x833f, FALSE}, {0x8340, TRUE }, {0x837e, TRUE },
        {0x837f, FALSE}, {0x8380, TRUE }, {0x8396, TRUE }, {0x8397, FALSE},
        {0xa5, FALSE}, {0xb0, FALSE}, {0xdd, FALSE}
    };
    unsigned int prev_cp = _getmbcp();
    int ret;
    unsigned int i;

    _setmbcp(_MB_CP_SBCS);
    for (i = 0; i < ARRAY_SIZE(tests); i++) {
        ret = _ismbckata(tests[i].c);
        ok(!ret, "expected 0, got %d for %04x\n", ret, tests[i].c);
    }

    _setmbcp(932);
    for (i = 0; i < ARRAY_SIZE(tests); i++) {
        ret = _ismbckata(tests[i].c);
        ok(!!ret == tests[i].exp, "expected %d, got %d for %04x\n",
           tests[i].exp, !!ret, tests[i].c);
    }

    _setmbcp(prev_cp);
}