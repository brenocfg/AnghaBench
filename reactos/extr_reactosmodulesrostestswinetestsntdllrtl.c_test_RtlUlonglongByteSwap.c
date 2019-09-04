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
typedef  int ULONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pRtlUlonglongByteSwap (int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_RtlUlonglongByteSwap(void)
{
    ULONGLONG result;

    if ( !pRtlUlonglongByteSwap )
    {
        win_skip("RtlUlonglongByteSwap is not available\n");
        return;
    }

    if ( pRtlUlonglongByteSwap( 0 ) != 0 )
    {
        win_skip("Broken RtlUlonglongByteSwap in win2k\n");
        return;
    }

    result = pRtlUlonglongByteSwap( ((ULONGLONG)0x76543210 << 32) | 0x87654321 );
    ok( (((ULONGLONG)0x21436587 << 32) | 0x10325476) == result,
       "RtlUlonglongByteSwap(0x7654321087654321) returns 0x%s, expected 0x2143658710325476\n",
       wine_dbgstr_longlong(result));
}