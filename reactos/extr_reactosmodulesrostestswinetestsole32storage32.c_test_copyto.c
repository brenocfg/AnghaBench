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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IStorage_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STG_E_INVALIDPOINTER ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ create_test_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file1_name ; 
 int /*<<< orphan*/  file1_nameA ; 
 int /*<<< orphan*/  file2_name ; 
 int /*<<< orphan*/  file2_nameA ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  stgA_name ; 
 int /*<<< orphan*/  stgB_name ; 
 scalar_t__ strcmp_ww (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strmA_name ; 
 int /*<<< orphan*/ * strmB_name ; 
 int /*<<< orphan*/ * strmC_name ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_copyto(void)
{
    IStorage *file1 = NULL, *file2 = NULL, *stg_tmp;
    IStream *strm_tmp;
    WCHAR buf[64];
    HRESULT hr;

    /* create & populate file1 */
    hr = StgCreateDocfile(file1_name, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &file1);
    ok(hr == S_OK, "StgCreateDocfile failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    hr = create_test_file(file1);
    if(FAILED(hr))
        goto cleanup;

    /* create file2 */
    hr = StgCreateDocfile(file2_name, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &file2);
    ok(hr == S_OK, "StgCreateDocfile failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    /* copy file1 into file2 */
    hr = IStorage_CopyTo(file1, 0, NULL, NULL, NULL);
    ok(hr == STG_E_INVALIDPOINTER, "CopyTo should give STG_E_INVALIDPONITER, gave: 0x%08x\n", hr);

    hr = IStorage_CopyTo(file1, 0, NULL, NULL, file2);
    ok(hr == S_OK, "CopyTo failed: 0x%08x\n", hr);
    if(FAILED(hr))
        goto cleanup;

    /* verify that all of file1 was copied */
    hr = IStorage_OpenStorage(file2, stgA_name, NULL,
            STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &stg_tmp);
    ok(hr == S_OK, "OpenStorage failed: 0x%08x\n", hr);

    if(SUCCEEDED(hr)){
        hr = IStorage_OpenStream(stg_tmp, strmA_name, NULL,
                STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &strm_tmp);
        ok(hr == S_OK, "OpenStream failed: 0x%08x\n", hr);

        if(SUCCEEDED(hr)){
            memset(buf, 0, sizeof(buf));
            hr = IStream_Read(strm_tmp, buf, sizeof(buf), NULL);
            ok(hr == S_OK, "Read failed: 0x%08x\n", hr);
            if(SUCCEEDED(hr))
                ok(strcmp_ww(buf, strmA_name) == 0,
                        "Expected %s to be read, got %s\n", wine_dbgstr_w(strmA_name), wine_dbgstr_w(buf));

            IStream_Release(strm_tmp);
        }

        IStorage_Release(stg_tmp);
    }

    hr = IStorage_OpenStorage(file2, stgB_name, NULL,
            STGM_READWRITE | STGM_SHARE_EXCLUSIVE, NULL, 0, &stg_tmp);
    ok(hr == S_OK, "OpenStorage failed: 0x%08x\n", hr);

    if(SUCCEEDED(hr)){
        hr = IStorage_OpenStream(stg_tmp, strmB_name, NULL,
                STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &strm_tmp);
        ok(hr == S_OK, "OpenStream failed: 0x%08x\n", hr);

        if(SUCCEEDED(hr)){
            memset(buf, 0, sizeof(buf));
            hr = IStream_Read(strm_tmp, buf, sizeof(buf), NULL);
            ok(hr == S_OK, "Read failed: 0x%08x\n", hr);
            if(SUCCEEDED(hr))
                ok(strcmp_ww(buf, strmB_name) == 0,
                        "Expected %s to be read, got %s\n", wine_dbgstr_w(strmB_name), wine_dbgstr_w(buf));

            IStream_Release(strm_tmp);
        }

        IStorage_Release(stg_tmp);
    }

    hr = IStorage_OpenStream(file2, strmC_name, NULL,
            STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, &strm_tmp);
    ok(hr == S_OK, "OpenStream failed: 0x%08x\n", hr);

    if(SUCCEEDED(hr)){
        memset(buf, 0, sizeof(buf));
        hr = IStream_Read(strm_tmp, buf, sizeof(buf), NULL);
        ok(hr == S_OK, "Read failed: 0x%08x\n", hr);
        if(SUCCEEDED(hr))
            ok(strcmp_ww(buf, strmC_name) == 0,
                    "Expected %s to be read, got %s\n", wine_dbgstr_w(strmC_name), wine_dbgstr_w(buf));

        IStream_Release(strm_tmp);
    }

cleanup:
    if(file1)
        IStorage_Release(file1);
    if(file2)
        IStorage_Release(file2);

    DeleteFileA(file1_nameA);
    DeleteFileA(file2_nameA);
}