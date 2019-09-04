#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  hGlobal; int /*<<< orphan*/  hBitmap; } ;
struct TYPE_19__ {int lindex; void* tymed; void* dwAspect; void* cfFormat; int /*<<< orphan*/ * ptd; } ;
struct TYPE_16__ {void* member_0; void* member_2; int member_3; void* member_4; int /*<<< orphan*/  member_1; } ;
struct TYPE_18__ {int dwConnection; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_17__ {void* tymed; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  TYPE_3__ STATDATA ;
typedef  int /*<<< orphan*/  IOleCache2 ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int HRESULT ;
typedef  TYPE_4__ FORMATETC ;
typedef  int DWORD ;

/* Variables and functions */
 int CACHE_S_SAMECACHE ; 
 void* CF_BITMAP ; 
 void* CF_DIB ; 
 void* CF_ENHMETAFILE ; 
 void* CF_METAFILEPICT ; 
 int /*<<< orphan*/  CLSID_NULL ; 
 int /*<<< orphan*/  CLSID_Picture_Dib ; 
 int CreateDataCache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 void* DVASPECT_CONTENT ; 
 void* DVASPECT_DOCPRINT ; 
 void* DVASPECT_ICON ; 
 void* DVASPECT_THUMBNAIL ; 
 int DV_E_FORMATETC ; 
 int DV_E_TYMED ; 
 int FAILED (int) ; 
 int IDataObject_GetData (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDataObject ; 
 int /*<<< orphan*/  IID_IOleCache2 ; 
 int IOleCache2_Cache (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int IOleCache2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleCache2_Release (int /*<<< orphan*/ *) ; 
 int IOleCache2_SetData (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int IOleCache2_Uncache (int /*<<< orphan*/ *,int) ; 
 int OLE_E_NOCONNECTION ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 void* TYMED_ENHMF ; 
 void* TYMED_GDI ; 
 void* TYMED_HGLOBAL ; 
 void* TYMED_MFPICT ; 
 TYPE_8__ U (TYPE_2__) ; 
 int /*<<< orphan*/  check_bitmap_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  check_dib_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  check_enum_cache (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  create_bitmap (TYPE_2__*) ; 
 int /*<<< orphan*/  create_dib (TYPE_2__*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_data_cache_cache(void)
{
    HRESULT hr;
    IOleCache2 *cache;
    IDataObject *data;
    FORMATETC fmt;
    DWORD conn;
    STGMEDIUM med;
    STATDATA expect[] =
    {
        {{ CF_DIB,          0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL }, 0, NULL, 0 },
        {{ CF_BITMAP,       0, DVASPECT_CONTENT, -1, TYMED_GDI },     0, NULL, 0 },
        {{ CF_METAFILEPICT, 0, DVASPECT_CONTENT, -1, TYMED_MFPICT },  0, NULL, 0 },
        {{ CF_ENHMETAFILE,  0, DVASPECT_CONTENT, -1, TYMED_ENHMF },   0, NULL, 0 }
    };
    STATDATA view_caching[] =
    {
        {{ 0,               0, DVASPECT_CONTENT,   -1, TYMED_ENHMF },   0, NULL, 0 },
        {{ 0,               0, DVASPECT_THUMBNAIL, -1, TYMED_HGLOBAL }, 0, NULL, 0 },
        {{ 0,               0, DVASPECT_DOCPRINT,  -1, TYMED_HGLOBAL }, 0, NULL, 0 },
        {{ CF_METAFILEPICT, 0, DVASPECT_ICON,      -1, TYMED_MFPICT },  0, NULL, 0 }
    };

    hr = CreateDataCache( NULL, &CLSID_NULL, &IID_IOleCache2, (void **)&cache );
    ok( hr == S_OK, "got %08x\n", hr );

    /* create a dib entry which will also create a bitmap entry too */
    fmt.cfFormat = CF_DIB;
    fmt.ptd = NULL;
    fmt.dwAspect = DVASPECT_CONTENT;
    fmt.lindex = -1;
    fmt.tymed = TYMED_HGLOBAL;

    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( conn == 2, "got %d\n", conn );
    expect[0].dwConnection = conn;
    expect[1].dwConnection = conn;

    check_enum_cache( cache, expect, 2 );

    /* now try to add a bitmap */
    fmt.cfFormat = CF_BITMAP;
    fmt.tymed = TYMED_GDI;

    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == CACHE_S_SAMECACHE, "got %08x\n", hr );

    /* metafile */
    fmt.cfFormat = CF_METAFILEPICT;
    fmt.tymed = TYMED_MFPICT;

    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( conn == 3, "got %d\n", conn );
    expect[2].dwConnection = conn;

    check_enum_cache( cache, expect,  3);

    /* enhmetafile */
    fmt.cfFormat = CF_ENHMETAFILE;
    fmt.tymed = TYMED_ENHMF;

    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( conn == 4, "got %d\n", conn );
    expect[3].dwConnection = conn;

    check_enum_cache( cache, expect, 4 );

    /* uncache everything */
    hr = IOleCache2_Uncache( cache, expect[3].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, expect[2].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, expect[0].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, expect[0].dwConnection );
    ok( hr == OLE_E_NOCONNECTION, "got %08x\n", hr );

    check_enum_cache( cache, expect, 0 );

    /* just create a bitmap entry which again adds both dib and bitmap */
    fmt.cfFormat = CF_BITMAP;
    fmt.tymed = TYMED_GDI;

    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );

    expect[0].dwConnection = conn;
    expect[1].dwConnection = conn;

    check_enum_cache( cache, expect, 2 );

    /* Try setting a 1x1 bitmap */
    hr = IOleCache2_QueryInterface( cache, &IID_IDataObject, (void **) &data );
    ok( hr == S_OK, "got %08x\n", hr );

    create_bitmap( &med );

    hr = IOleCache2_SetData( cache, &fmt, &med, TRUE );
    ok( hr == S_OK, "got %08x\n", hr );

    hr = IDataObject_GetData( data, &fmt, &med );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( med.tymed == TYMED_GDI, "got %d\n", med.tymed );
    check_bitmap_size( U(med).hBitmap, 1, 1 );
    ReleaseStgMedium( &med );

    fmt.cfFormat = CF_DIB;
    fmt.tymed = TYMED_HGLOBAL;
    hr = IDataObject_GetData( data, &fmt, &med );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( med.tymed == TYMED_HGLOBAL, "got %d\n", med.tymed );
    check_dib_size( U(med).hGlobal, 1, 1 );
    ReleaseStgMedium( &med );

    /* Now set a 2x1 dib */
    fmt.cfFormat = CF_DIB;
    fmt.tymed = TYMED_HGLOBAL;
    create_dib( &med );

    hr = IOleCache2_SetData( cache, &fmt, &med, TRUE );
    ok( hr == S_OK, "got %08x\n", hr );

    fmt.cfFormat = CF_BITMAP;
    fmt.tymed = TYMED_GDI;
    hr = IDataObject_GetData( data, &fmt, &med );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( med.tymed == TYMED_GDI, "got %d\n", med.tymed );
    check_bitmap_size( U(med).hBitmap, 2, 1 );
    ReleaseStgMedium( &med );

    fmt.cfFormat = CF_DIB;
    fmt.tymed = TYMED_HGLOBAL;
    hr = IDataObject_GetData( data, &fmt, &med );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( med.tymed == TYMED_HGLOBAL, "got %d\n", med.tymed );
    check_dib_size( U(med).hGlobal, 2, 1 );
    ReleaseStgMedium( &med );

    /* uncache everything */
    hr = IOleCache2_Uncache( cache, conn );
    ok( hr == S_OK, "got %08x\n", hr );

    /* view caching */
    fmt.cfFormat = 0;
    fmt.tymed = TYMED_ENHMF;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    view_caching[0].dwConnection = conn;

    fmt.tymed = TYMED_HGLOBAL;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == CACHE_S_SAMECACHE, "got %08x\n", hr );

    fmt.dwAspect = DVASPECT_THUMBNAIL;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    view_caching[1].dwConnection = conn;

    fmt.dwAspect = DVASPECT_DOCPRINT;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    view_caching[2].dwConnection = conn;

    /* DVASPECT_ICON view cache gets mapped to CF_METAFILEPICT */
    fmt.dwAspect = DVASPECT_ICON;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );
    view_caching[3].dwConnection = conn;

    check_enum_cache( cache, view_caching, 4 );

    /* uncache everything */
    hr = IOleCache2_Uncache( cache, view_caching[3].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, view_caching[2].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, view_caching[1].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );
    hr = IOleCache2_Uncache( cache, view_caching[0].dwConnection );
    ok( hr == S_OK, "got %08x\n", hr );

    /* Only able to set cfFormat == CF_METAFILEPICT (or == 0, see above) for DVASPECT_ICON */
    fmt.dwAspect = DVASPECT_ICON;
    fmt.cfFormat = CF_DIB;
    fmt.tymed = TYMED_HGLOBAL;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == DV_E_FORMATETC, "got %08x\n", hr );
    fmt.cfFormat = CF_BITMAP;
    fmt.tymed = TYMED_GDI;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == DV_E_FORMATETC, "got %08x\n", hr );
    fmt.cfFormat = CF_ENHMETAFILE;
    fmt.tymed = TYMED_ENHMF;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == DV_E_FORMATETC, "got %08x\n", hr );
    fmt.cfFormat = CF_METAFILEPICT;
    fmt.tymed = TYMED_MFPICT;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );

    /* uncache everything */
    hr = IOleCache2_Uncache( cache, conn );
    ok( hr == S_OK, "got %08x\n", hr );

    /* tymed == 0 */
    fmt.cfFormat = CF_ENHMETAFILE;
    fmt.dwAspect = DVASPECT_CONTENT;
    fmt.tymed = 0;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == DV_E_TYMED, "got %08x\n", hr );

    IDataObject_Release( data );
    IOleCache2_Release( cache );

    /* tests for a static class cache */
    hr = CreateDataCache( NULL, &CLSID_Picture_Dib, &IID_IOleCache2, (void **)&cache );

    fmt.cfFormat = CF_DIB;
    fmt.dwAspect = DVASPECT_CONTENT;
    fmt.tymed = TYMED_HGLOBAL;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == CACHE_S_SAMECACHE, "got %08x\n", hr );

    /* aspect other than DVASPECT_CONTENT should fail */
    fmt.dwAspect = DVASPECT_THUMBNAIL;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( FAILED(hr), "got %08x\n", hr );

    fmt.dwAspect = DVASPECT_DOCPRINT;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( FAILED(hr), "got %08x\n", hr );

    /* try caching another clip format */
    fmt.cfFormat = CF_METAFILEPICT;
    fmt.dwAspect = DVASPECT_CONTENT;
    fmt.tymed = TYMED_MFPICT;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( FAILED(hr), "got %08x\n", hr );

    /* As an exception, it's possible to add an icon aspect */
    fmt.cfFormat = CF_METAFILEPICT;
    fmt.dwAspect = DVASPECT_ICON;
    fmt.tymed = TYMED_MFPICT;
    hr = IOleCache2_Cache( cache, &fmt, 0, &conn );
    ok( hr == S_OK, "got %08x\n", hr );

    IOleCache2_Release( cache );
}