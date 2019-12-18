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
typedef  int /*<<< orphan*/  afc ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_3__ {int cbStruct; int /*<<< orphan*/ * pwfx; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ ACMFORMATCHOOSEW ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_METRIC_MAX_SIZE_FORMAT ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MMSYSERR_INVALPARAM ; 
 scalar_t__ acmFormatChooseW (TYPE_1__*) ; 
 int /*<<< orphan*/  acmMetrics (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_acmFormatChoose(void)
{
    ACMFORMATCHOOSEW afc = {0};
    WAVEFORMATEX *pwfx;
    DWORD sizeMax;
    MMRESULT rc;

    acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &sizeMax);
    pwfx = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeMax);

    afc.cbStruct = sizeof(afc);
    afc.pwfx = pwfx;

    /* test invalid struct size */
    afc.cbStruct = sizeof(afc)-1;
    rc = acmFormatChooseW(&afc);
    ok(rc == MMSYSERR_INVALPARAM, "expected 0xb, got 0x%x\n", rc);
    afc.cbStruct = sizeof(afc);

    afc.pwfx = NULL;
    rc = acmFormatChooseW(&afc);
    ok(rc == MMSYSERR_INVALPARAM, "expected 0xb, got 0x%x\n", rc);
    afc.pwfx = pwfx;

    HeapFree(GetProcessHeap(), 0, pwfx);
}