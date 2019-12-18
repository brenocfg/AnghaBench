#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aftd ;
struct TYPE_3__ {int cbStruct; int cbFormatSize; int /*<<< orphan*/  dwFormatTag; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  MPEGLAYER3WAVEFORMAT ;
typedef  scalar_t__ MMRESULT ;
typedef  TYPE_1__ ACMFORMATTAGDETAILSW ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_FORMATTAGDETAILSF_FORMATTAG ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  WAVE_FORMAT_MPEGLAYER3 ; 
 scalar_t__ acmFormatTagDetailsW (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_acmFormatTagDetails(void)
{
    ACMFORMATTAGDETAILSW aftd = {0};
    MMRESULT rc;

    aftd.cbStruct = sizeof(aftd);
    aftd.dwFormatTag = WAVE_FORMAT_MPEGLAYER3;
    rc = acmFormatTagDetailsW(NULL, &aftd, ACM_FORMATTAGDETAILSF_FORMATTAG);
    if (rc == MMSYSERR_NOERROR)
        ok(aftd.cbFormatSize == sizeof(MPEGLAYER3WAVEFORMAT), "got %d\n", aftd.cbFormatSize);
}