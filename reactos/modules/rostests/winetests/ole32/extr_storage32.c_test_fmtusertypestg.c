#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statstg ;
typedef  float WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  pwcsName; } ;
typedef  TYPE_1__ STATSTG ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IEnumSTATSTG ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ IEnumSTATSTG_Next (int /*<<< orphan*/ *,int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  IEnumSTATSTG_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_EnumElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (float const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WriteFmtUserTypeStg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ memcmp (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strcmp_ww (int /*<<< orphan*/ ,float const*) ; 

__attribute__((used)) static void test_fmtusertypestg(void)
{
    IStorage *stg;
    IEnumSTATSTG *stat;
    HRESULT hr;
    static const char fileA[]  = {'f','m','t','t','e','s','t',0};
    static const WCHAR fileW[] = {'f','m','t','t','e','s','t',0};
    static WCHAR userTypeW[] = {'S','t','g','U','s','r','T','y','p','e',0};
    static const WCHAR strmNameW[] = {1,'C','o','m','p','O','b','j',0};
    static const STATSTG statstg_null;

    hr = StgCreateDocfile( fileW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stg);
    ok(hr == S_OK, "should succeed, res=%x\n", hr);

    if (SUCCEEDED(hr))
    {
        /* try to write the stream */
        hr = WriteFmtUserTypeStg(stg, 0, userTypeW);
        ok(hr == S_OK, "should succeed, res=%x\n", hr);

        /* check that the stream was created */
        hr = IStorage_EnumElements(stg, 0, NULL, 0, &stat);
        ok(hr == S_OK, "should succeed, res=%x\n", hr);
        if (SUCCEEDED(hr))
        {
            BOOL found = FALSE;
            STATSTG statstg;
            DWORD got;
            memset(&statstg, 0xad, sizeof(statstg));
            while ((hr = IEnumSTATSTG_Next(stat, 1, &statstg, &got)) == S_OK && got == 1)
            {
                if (strcmp_ww(statstg.pwcsName, strmNameW) == 0)
                    found = TRUE;
                else
                    ok(0, "found unexpected stream or storage\n");
                CoTaskMemFree(statstg.pwcsName);
            }
            ok(memcmp(&statstg, &statstg_null, sizeof(statstg)) == 0, "statstg is not zeroed\n");
            ok(found == TRUE, "expected storage to contain stream \\0001CompObj\n");
            IEnumSTATSTG_Release(stat);
        }

        /* re-write the stream */
        hr = WriteFmtUserTypeStg(stg, 0, userTypeW);
        ok(hr == S_OK, "should succeed, res=%x\n", hr);

        /* check that the stream is still there */
        hr = IStorage_EnumElements(stg, 0, NULL, 0, &stat);
        ok(hr == S_OK, "should succeed, res=%x\n", hr);
        if (SUCCEEDED(hr))
        {
            BOOL found = FALSE;
            STATSTG statstg;
            DWORD got;
            memset(&statstg, 0xad, sizeof(statstg));
            while ((hr = IEnumSTATSTG_Next(stat, 1, &statstg, &got)) == S_OK && got == 1)
            {
                if (strcmp_ww(statstg.pwcsName, strmNameW) == 0)
                    found = TRUE;
                else
                    ok(0, "found unexpected stream or storage\n");
                CoTaskMemFree(statstg.pwcsName);
            }
            ok(memcmp(&statstg, &statstg_null, sizeof(statstg)) == 0, "statstg is not zeroed\n");
            ok(found == TRUE, "expected storage to contain stream \\0001CompObj\n");
            IEnumSTATSTG_Release(stat);
        }

        IStorage_Release(stg);
        DeleteFileA( fileA );
    }
}