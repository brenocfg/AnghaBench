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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_DestroyElement (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ STG_E_ACCESSDENIED ; 
 scalar_t__ STG_E_FILEALREADYEXISTS ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ StgOpenStorage (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_readonly(void)
{
    IStorage *stg, *stg2, *stg3;
    IStream *stream;
    HRESULT hr;
    static const WCHAR fileW[] = {'w','i','n','e','t','e','s','t',0};
    static const WCHAR storageW[] = {'s','t','o','r','a','g','e',0};
    static const WCHAR streamW[] = {'s','t','r','e','a','m',0};

    hr = StgCreateDocfile( fileW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stg);
    ok(hr == S_OK, "should succeed, res=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        hr = IStorage_CreateStorage( stg, storageW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stg2 );
        ok(hr == S_OK, "should succeed, res=%x\n", hr);
        if (SUCCEEDED(hr))
        {
            hr = IStorage_CreateStream( stg2, streamW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, 0, &stream );
            ok(hr == S_OK, "should succeed, res=%x\n", hr);
            if (SUCCEEDED(hr))
                IStream_Release(stream);
            IStorage_Release(stg2);
        }
        IStorage_Release(stg);
    }

    /* re-open read only */
    hr = StgOpenStorage( fileW, NULL, STGM_TRANSACTED | STGM_SHARE_DENY_NONE | STGM_READ, NULL, 0, &stg);
    ok(hr == S_OK, "should succeed, res=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        hr = IStorage_OpenStorage( stg, storageW, NULL, STGM_SHARE_EXCLUSIVE | STGM_READ, NULL, 0, &stg2 );
        ok(hr == S_OK, "should succeed, res=%x\n", hr);
        if (SUCCEEDED(hr))
        {
            /* CreateStream on read-only storage, name exists */
            hr = IStorage_CreateStream( stg2, streamW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READ, 0, 0, &stream );
            ok(hr == STG_E_ACCESSDENIED, "should fail, res=%x\n", hr);
            if (SUCCEEDED(hr))
                IStream_Release(stream);

            /* CreateStream on read-only storage, name does not exist */
            hr = IStorage_CreateStream( stg2, storageW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READ, 0, 0, &stream );
            ok(hr == STG_E_ACCESSDENIED, "should fail, res=%x\n", hr);
            if (SUCCEEDED(hr))
                IStream_Release(stream);

            /* CreateStorage on read-only storage, name exists */
            hr = IStorage_CreateStorage( stg2, streamW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READ, 0, 0, &stg3 );
            ok(hr == STG_E_FILEALREADYEXISTS, "should fail, res=%x\n", hr);
            if (SUCCEEDED(hr))
                IStorage_Release(stg3);

            /* CreateStorage on read-only storage, name does not exist */
            hr = IStorage_CreateStorage( stg2, storageW, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READ, 0, 0, &stg3 );
            ok(hr == STG_E_ACCESSDENIED, "should fail, res=%x\n", hr);
            if (SUCCEEDED(hr))
                IStorage_Release(stg3);

            /* DestroyElement on read-only storage, name exists */
            hr = IStorage_DestroyElement( stg2, streamW );
            ok(hr == STG_E_ACCESSDENIED, "should fail, res=%x\n", hr);

            /* DestroyElement on read-only storage, name does not exist */
            hr = IStorage_DestroyElement( stg2, storageW );
            ok(hr == STG_E_ACCESSDENIED, "should fail, res=%x\n", hr);

            IStorage_Release(stg2);
        }

        IStorage_Release(stg);
    }

    DeleteFileA("winetest");
}