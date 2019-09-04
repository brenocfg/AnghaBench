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
typedef  int /*<<< orphan*/  clsid2 ;
typedef  int /*<<< orphan*/  clsid ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_NULL ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ReadClassStm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ STG_E_READFAULT ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WriteClassStm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,char*) ; 
 int /*<<< orphan*/  test_stg_cls ; 

__attribute__((used)) static void test_ReadClassStm(void)
{
    CLSID clsid, clsid2;
    HRESULT hr;
    IStream *pStream;
    static const LARGE_INTEGER llZero;

    hr = ReadClassStm(NULL, &clsid);
    ok(hr == E_INVALIDARG, "ReadClassStm should have returned E_INVALIDARG instead of 0x%08x\n", hr);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
    ok_ole_success(hr, "CreateStreamOnHGlobal");
    hr = WriteClassStm(pStream, &test_stg_cls);
    ok_ole_success(hr, "WriteClassStm");

    hr = ReadClassStm(pStream, NULL);
    ok(hr == E_INVALIDARG, "ReadClassStm should have returned E_INVALIDARG instead of 0x%08x\n", hr);

    memset(&clsid, 0xcc, sizeof(clsid));
    memset(&clsid2, 0xcc, sizeof(clsid2));
    hr = ReadClassStm(NULL, &clsid);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &clsid2), "got wrong clsid\n");

    /* test not rewound stream */
    hr = ReadClassStm(pStream, &clsid);
    ok(hr == STG_E_READFAULT, "ReadClassStm should have returned STG_E_READFAULT instead of 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_NULL), "clsid should have been zeroed\n");

    hr = IStream_Seek(pStream, llZero, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, "IStream_Seek");
    hr = ReadClassStm(pStream, &clsid);
    ok_ole_success(hr, "ReadClassStm");
    ok(IsEqualCLSID(&clsid, &test_stg_cls), "clsid should have been set to CLSID_WineTest\n");

    IStream_Release(pStream);
}