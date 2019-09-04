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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAVIStream ;
typedef  int /*<<< orphan*/  IAVIEditStream ;
typedef  int HRESULT ;

/* Variables and functions */
 int CreateEditableStream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IAVIEditStream_AddRef (int /*<<< orphan*/ *) ; 
 int IAVIEditStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IAVIEditStream_Release (int /*<<< orphan*/ *) ; 
 int IAVIStream_AddRef (int /*<<< orphan*/ *) ; 
 int IAVIStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IAVIEditStream ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_COM_editstream(void)
{
    IAVIEditStream *edit;
    IAVIStream *stream;
    IUnknown *unk;
    ULONG refcount;
    HRESULT hr;

    /* Same refcount for all AVIEditStream interfaces */
    hr = CreateEditableStream(&stream, NULL);
    ok(hr == S_OK, "AVIEditStream create failed: %08x, expected S_OK\n", hr);
    refcount = IAVIStream_AddRef(stream);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);

    hr = IAVIStream_QueryInterface(stream, &IID_IAVIEditStream, (void**)&edit);
    ok(hr == S_OK, "QueryInterface for IID_IAVIEditStream failed: %08x\n", hr);
    refcount = IAVIEditStream_AddRef(edit);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    refcount = IAVIEditStream_Release(edit);

    hr = IAVIEditStream_QueryInterface(edit, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    refcount = IUnknown_AddRef(unk);
    ok(refcount == 5, "refcount == %u, expected 5\n", refcount);
    IUnknown_Release(unk);

    while (IAVIEditStream_Release(edit));
}