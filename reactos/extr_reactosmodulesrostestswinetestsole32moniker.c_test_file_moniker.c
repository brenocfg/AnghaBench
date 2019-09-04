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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  void IStream ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoMarshalInterface (void*,int /*<<< orphan*/ *,void**,...) ; 
 int /*<<< orphan*/  CoUnmarshalInterface (void*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CreateFileMoniker (void*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (void*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IMoniker ; 
 int /*<<< orphan*/  IMoniker_IsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (void*) ; 
 int /*<<< orphan*/  IStream_Seek (void*,int /*<<< orphan*/ *,void**,...) ; 
 int /*<<< orphan*/  IsEqual (void*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/ * TRUE ; 
 int /*<<< orphan*/  llZero ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ *,void**)) ; 

__attribute__((used)) static void test_file_moniker(WCHAR* path)
{
    IStream *stream;
    IMoniker *moniker1 = NULL, *moniker2 = NULL;
    HRESULT hr;

    hr = CreateFileMoniker(path, &moniker1);
    ok_ole_success(hr, CreateFileMoniker); 

    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok_ole_success(hr, CreateStreamOnHGlobal);

    /* Marshal */
    hr = CoMarshalInterface(stream, &IID_IMoniker, (IUnknown *)moniker1, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    ok_ole_success(hr, CoMarshalInterface);
    
    /* Rewind */
    hr = IStream_Seek(stream, llZero, STREAM_SEEK_SET, NULL);
    ok_ole_success(hr, IStream_Seek);

    /* Unmarshal */
    hr = CoUnmarshalInterface(stream, &IID_IMoniker, (void**)&moniker2);
    ok_ole_success(hr, CoUnmarshalInterface);

    hr = IMoniker_IsEqual(moniker1, moniker2);
    ok_ole_success(hr, IsEqual);

    IStream_Release(stream);
    if (moniker1) 
        IMoniker_Release(moniker1);
    if (moniker2) 
        IMoniker_Release(moniker2);
}