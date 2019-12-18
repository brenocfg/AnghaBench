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
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ BG_FILE_INFO ;

/* Variables and functions */
 scalar_t__ IBackgroundCopyJob_AddFileSet (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_job ; 
 int /*<<< orphan*/  test_localPathA ; 
 int /*<<< orphan*/  test_localPathB ; 
 int /*<<< orphan*/  test_remotePathA ; 
 int /*<<< orphan*/  test_remotePathB ; 

__attribute__((used)) static void test_AddFileSet(void)
{
    HRESULT hres;
    BG_FILE_INFO files[2] =
        {
            {test_remotePathA, test_localPathA},
            {test_remotePathB, test_localPathB}
        };
    hres = IBackgroundCopyJob_AddFileSet(test_job, 2, files);
    ok(hres == S_OK, "AddFileSet failed: 0x%08x\n", hres);
}