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
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  HMIXER ;

/* Variables and functions */
 scalar_t__ MMSYSERR_INVALHANDLE ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ mixerClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmsys_error (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mixerClose(HMIXER mix)
{
    MMRESULT rc;

    rc = mixerClose(mix);
    ok(rc == MMSYSERR_NOERROR || rc == MMSYSERR_INVALHANDLE,
       "mixerClose: MMSYSERR_NOERROR or MMSYSERR_INVALHANDLE expected, got %s\n",
       mmsys_error(rc));
}