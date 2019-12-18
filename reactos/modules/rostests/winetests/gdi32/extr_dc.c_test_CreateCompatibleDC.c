#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dmScale; } ;
struct TYPE_8__ {TYPE_1__ s1; } ;
struct TYPE_9__ {int /*<<< orphan*/  dmFields; TYPE_2__ u1; } ;
typedef  int /*<<< orphan*/ * INT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_3__ DEVMODEA ;
typedef  int /*<<< orphan*/ * BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseMetaFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDCA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * CreateEnhMetaFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateMetaFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DM_SCALE ; 
 int /*<<< orphan*/ * DT_METAFILE ; 
 int /*<<< orphan*/ * DT_RASDISPLAY ; 
 int /*<<< orphan*/ * DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENUM_CURRENT_SETTINGS ; 
 int /*<<< orphan*/ * EnumDisplaySettingsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDeviceCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetDCA (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TECHNOLOGY ; 
 int /*<<< orphan*/ * TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_device_caps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void test_CreateCompatibleDC(void)
{
    BOOL bRet;
    HDC hdc, hNewDC, hdcMetafile, screen_dc;
    HBITMAP bitmap;
    INT caps;
    DEVMODEA dm;

    bitmap = CreateBitmap( 10, 10, 1, 1, NULL );

    bRet = EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &dm);
    ok(bRet, "EnumDisplaySettingsEx failed\n");
    dm.u1.s1.dmScale = 200;
    dm.dmFields |= DM_SCALE;
    hdc = CreateDCA( "DISPLAY", NULL, NULL, &dm );

    screen_dc = CreateDCA( "DISPLAY", NULL, NULL, NULL );
    test_device_caps( hdc, screen_dc, "display dc", 1 );
    ResetDCA( hdc, &dm );
    test_device_caps( hdc, screen_dc, "display dc", 1 );
    DeleteDC( hdc );

    /* Create a DC compatible with the screen */
    hdc = CreateCompatibleDC(NULL);
    ok(hdc != NULL, "CreateCompatibleDC returned %p\n", hdc);
    ok( SelectObject( hdc, bitmap ) != 0, "SelectObject failed\n" );
    caps = GetDeviceCaps( hdc, TECHNOLOGY );
    ok( caps == DT_RASDISPLAY, "wrong caps %u\n", caps );

    test_device_caps( hdc, screen_dc, "display dc", 1 );

    /* Delete this DC, this should succeed */
    bRet = DeleteDC(hdc);
    ok(bRet == TRUE, "DeleteDC returned %u\n", bRet);

    /* Try to create a DC compatible to the deleted DC. This has to fail */
    hNewDC = CreateCompatibleDC(hdc);
    ok(hNewDC == NULL, "CreateCompatibleDC returned %p\n", hNewDC);

    hdc = GetDC( 0 );
    hdcMetafile = CreateEnhMetaFileA(hdc, NULL, NULL, NULL);
    ok(hdcMetafile != 0, "CreateEnhMetaFileA failed\n");
    hNewDC = CreateCompatibleDC( hdcMetafile );
    ok(hNewDC != NULL, "CreateCompatibleDC failed\n");
    ok( SelectObject( hNewDC, bitmap ) != 0, "SelectObject failed\n" );
    caps = GetDeviceCaps( hdcMetafile, TECHNOLOGY );
    ok( caps == DT_RASDISPLAY, "wrong caps %u\n", caps );
    test_device_caps( hdcMetafile, hdc, "enhmetafile dc", 1 );
    ResetDCA( hdcMetafile, &dm );
    test_device_caps( hdcMetafile, hdc, "enhmetafile dc", 1 );
    DeleteDC( hNewDC );
    DeleteEnhMetaFile( CloseEnhMetaFile( hdcMetafile ));
    ReleaseDC( 0, hdc );

    hdcMetafile = CreateMetaFileA(NULL);
    ok(hdcMetafile != 0, "CreateEnhMetaFileA failed\n");
    hNewDC = CreateCompatibleDC( hdcMetafile );
    ok(hNewDC == NULL, "CreateCompatibleDC succeeded\n");
    caps = GetDeviceCaps( hdcMetafile, TECHNOLOGY );
    ok( caps == DT_METAFILE, "wrong caps %u\n", caps );
    test_device_caps( hdcMetafile, screen_dc, "metafile dc", 1 );
    ResetDCA( hdcMetafile, &dm );
    test_device_caps( hdcMetafile, screen_dc, "metafile dc", 1 );
    DeleteMetaFile( CloseMetaFile( hdcMetafile ));

    DeleteObject( bitmap );
    DeleteDC( screen_dc );
}