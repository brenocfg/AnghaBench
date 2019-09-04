#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int version; int flags; int link_update_opt; int res; int moniker_size; } ;
typedef  TYPE_2__ ole_stream_header_t ;
typedef  int /*<<< orphan*/  header ;
typedef  int WCHAR ;
typedef  int ULONG ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_8__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IPersistStorage ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IID_IPersistStorage ; 
 scalar_t__ IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStorage_InitNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ OleCreateDefaultHandler (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STG_E_FILENOTFOUND ; 
 scalar_t__ S_OK ; 
 scalar_t__ create_storage (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_olestream(void)
{
    HRESULT hr;
    const CLSID non_existent_class = {0xa5f1772f, 0x3772, 0x490f, {0x9e, 0xc6, 0x77, 0x13, 0xe8, 0xb3, 0x4b, 0x5d}};
    IOleObject *ole_obj;
    IPersistStorage *persist;
    IStorage *stg;
    IStream *stm;
    static const WCHAR olestream[] = {1,'O','l','e',0};
    ULONG read;
    ole_stream_header_t header;

    hr = create_storage(&stg);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IStorage_OpenStream(stg, olestream, NULL, STGM_SHARE_EXCLUSIVE | STGM_READ, 0, &stm);
    ok(hr == STG_E_FILENOTFOUND, "got %08x\n", hr);

    hr = OleCreateDefaultHandler(&non_existent_class, 0, &IID_IOleObject, (void**)&ole_obj);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IOleObject_QueryInterface(ole_obj, &IID_IPersistStorage, (void**)&persist);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_InitNew(persist, stg);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IStorage_OpenStream(stg, olestream, NULL, STGM_SHARE_EXCLUSIVE | STGM_READ, 0, &stm);
    ok(hr == S_OK, "got %08x\n", hr);
    hr = IStream_Read(stm, &header, sizeof(header), &read);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(read == sizeof(header), "read %d\n", read);
    ok(header.version == 0x02000001, "got version %08x\n", header.version);
    ok(header.flags == 0x0, "got flags %08x\n", header.flags);
    ok(header.link_update_opt == 0x0, "got link update option %08x\n", header.link_update_opt);
    ok(header.res == 0x0, "got reserved %08x\n", header.res);
    ok(header.moniker_size == 0x0, "got moniker size %08x\n", header.moniker_size);

    IStream_Release(stm);

    IPersistStorage_Release(persist);
    IOleObject_Release(ole_obj);

    IStorage_Release(stg);
}