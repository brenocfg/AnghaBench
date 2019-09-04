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
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  int /*<<< orphan*/ * LPAVICOMPRESSOPTIONS ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  AVICOMPRESSOPTIONS ;

/* Variables and functions */
 scalar_t__ AVIERR_OK ; 
 scalar_t__ AVISaveOptions (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ AVISaveOptionsFree (int,int /*<<< orphan*/ **) ; 
 scalar_t__ AVIStreamRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateEditableStream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ EditStreamSetNameA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int ICMF_CHOOSE_ALLCOMPRESSORS ; 
 int ICMF_CHOOSE_DATARATE ; 
 int ICMF_CHOOSE_KEYFRAME ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winetest0 ; 
 int /*<<< orphan*/  winetest1 ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_AVISaveOptions(void)
{
    AVICOMPRESSOPTIONS options[2];
    LPAVICOMPRESSOPTIONS poptions[2];
    PAVISTREAM streams[2] = {NULL, NULL};
    HRESULT hres;
    DWORD   res;
    LONG    lres;

    poptions[0] = &options[0];
    poptions[1] = &options[1];
    ZeroMemory(options, sizeof(options));

    SetLastError(0xdeadbeef);
    hres = CreateEditableStream(&streams[0], NULL);
    ok(hres == AVIERR_OK, "0: got 0x%x and %p (expected AVIERR_OK)\n", hres, streams[0]);

    SetLastError(0xdeadbeef);
    hres = CreateEditableStream(&streams[1], NULL);
    ok(hres == AVIERR_OK, "1: got 0x%x and %p (expected AVIERR_OK)\n", hres, streams[1]);

    SetLastError(0xdeadbeef);
    hres = EditStreamSetNameA(streams[0], winetest0);
    ok(hres == AVIERR_OK, "0: got 0x%x (expected AVIERR_OK)\n", hres);

    SetLastError(0xdeadbeef);
    hres = EditStreamSetNameA(streams[1], winetest1);
    ok(hres == AVIERR_OK, "1: got 0x%x (expected AVIERR_OK)\n", hres);

    if (winetest_interactive) {
        SetLastError(0xdeadbeef);
        res = AVISaveOptions(0, ICMF_CHOOSE_DATARATE |ICMF_CHOOSE_KEYFRAME | ICMF_CHOOSE_ALLCOMPRESSORS,
                             2, streams, poptions);
        trace("got %u with 0x%x/%u\n", res, GetLastError(), GetLastError());
    }

    SetLastError(0xdeadbeef);
    lres = AVISaveOptionsFree(2, poptions);
    ok(lres == AVIERR_OK, "got 0x%x with 0x%x/%u\n", lres, GetLastError(), GetLastError());

    SetLastError(0xdeadbeef);
    res = AVIStreamRelease(streams[0]);
    ok(res == 0, "0: got refcount %u (expected 0)\n", res);

    SetLastError(0xdeadbeef);
    res = AVIStreamRelease(streams[1]);
    ok(res == 0, "1: got refcount %u (expected 0)\n", res);

}