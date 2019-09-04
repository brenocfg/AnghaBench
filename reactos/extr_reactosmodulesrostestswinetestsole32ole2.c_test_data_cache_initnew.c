#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_3; int /*<<< orphan*/  const member_4; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
struct TYPE_5__ {int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_2__ STATDATA ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  IPersistStorage ;
typedef  int /*<<< orphan*/  IOleCache2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
#define  CF_BITMAP 134 
#define  CF_DIB 133 
#define  CF_METAFILEPICT 132 
 int /*<<< orphan*/  CLSID_Picture_Dib ; 
 int /*<<< orphan*/  CLSID_Picture_Metafile ; 
 int /*<<< orphan*/  CLSID_WineTestOld ; 
 scalar_t__ CO_E_ALREADYINITIALIZED ; 
 scalar_t__ CreateDataCache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
#define  DVASPECT_CONTENT 131 
 int /*<<< orphan*/  IID_IOleCache2 ; 
 int /*<<< orphan*/  IID_IPersistStorage ; 
 int /*<<< orphan*/  IOleCache2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleCache2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStorage_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStorage_HandsOffStorage (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStorage_InitNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStorage_SetClass (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsEqualCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 scalar_t__ StgCreateDocfile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
#define  TYMED_GDI 130 
#define  TYMED_HGLOBAL 129 
#define  TYMED_MFPICT 128 
 int /*<<< orphan*/  check_enum_cache (int /*<<< orphan*/ *,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_data_cache_initnew(void)
{
    HRESULT hr;
    IOleCache2 *cache;
    IPersistStorage *persist;
    IStorage *stg_dib, *stg_mf, *stg_wine;
    CLSID clsid;
    static const STATDATA initnew_expect[] =
    {
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 1 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 1 },
    };
    static const STATDATA initnew2_expect[] =
    {
        {{ CF_METAFILEPICT, 0, DVASPECT_CONTENT, -1, TYMED_MFPICT },  0, NULL, 1 },
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 2 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 2 },
    };
    static const STATDATA initnew3_expect[] =
    {
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 1 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 1 },
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 2 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 2 },
        {{ CF_METAFILEPICT, 0, DVASPECT_CONTENT, -1, TYMED_MFPICT },  0, NULL, 3 },
    };
    static const STATDATA initnew4_expect[] =
    {
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 2 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 2 },
        {{ CF_METAFILEPICT, 0, DVASPECT_CONTENT, -1, TYMED_MFPICT },  0, NULL, 3 },
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 4 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 4 },
    };

    hr = StgCreateDocfile( NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_DELETEONRELEASE, 0, &stg_dib );
    ok( hr == S_OK, "got %08x\n", hr);
    hr = IStorage_SetClass( stg_dib, &CLSID_Picture_Dib );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = StgCreateDocfile( NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_DELETEONRELEASE, 0, &stg_mf );
    ok( hr == S_OK, "got %08x\n", hr);
    hr = IStorage_SetClass( stg_mf, &CLSID_Picture_Metafile );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = StgCreateDocfile( NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_DELETEONRELEASE, 0, &stg_wine );
    ok( hr == S_OK, "got %08x\n", hr);
    hr = IStorage_SetClass( stg_wine, &CLSID_WineTestOld );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = CreateDataCache( NULL, &CLSID_WineTestOld, &IID_IOleCache2, (void **)&cache );
    ok( hr == S_OK, "got %08x\n", hr );
    IOleCache2_QueryInterface( cache, &IID_IPersistStorage, (void **) &persist );

    hr = IPersistStorage_InitNew( persist, stg_dib );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_GetClassID( persist, &clsid );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( IsEqualCLSID( &clsid, &CLSID_Picture_Dib ), "got %s\n", wine_dbgstr_guid( &clsid ) );

    check_enum_cache( cache, initnew_expect, 2 );

    hr = IPersistStorage_InitNew( persist, stg_mf );
    ok( hr == CO_E_ALREADYINITIALIZED, "got %08x\n", hr);

    hr = IPersistStorage_HandsOffStorage( persist );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_GetClassID( persist, &clsid );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( IsEqualCLSID( &clsid, &CLSID_Picture_Dib ), "got %s\n", wine_dbgstr_guid( &clsid ) );

    hr = IPersistStorage_InitNew( persist, stg_mf );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_GetClassID( persist, &clsid );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( IsEqualCLSID( &clsid, &CLSID_Picture_Metafile ), "got %s\n", wine_dbgstr_guid( &clsid ) );

    check_enum_cache( cache, initnew2_expect, 3 );

    hr = IPersistStorage_HandsOffStorage( persist );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_InitNew( persist, stg_dib );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_GetClassID( persist, &clsid );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( IsEqualCLSID( &clsid, &CLSID_Picture_Dib ), "got %s\n", wine_dbgstr_guid( &clsid ) );

    check_enum_cache( cache, initnew3_expect, 5 );

    hr = IPersistStorage_HandsOffStorage( persist );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_InitNew( persist, stg_wine );
    ok( hr == S_OK, "got %08x\n", hr);

    hr = IPersistStorage_GetClassID( persist, &clsid );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( IsEqualCLSID( &clsid, &CLSID_WineTestOld ), "got %s\n", wine_dbgstr_guid( &clsid ) );

    check_enum_cache( cache, initnew4_expect, 5 );

    IStorage_Release( stg_wine );
    IStorage_Release( stg_mf );
    IStorage_Release( stg_dib );

    IPersistStorage_Release( persist );
    IOleCache2_Release( cache );
}