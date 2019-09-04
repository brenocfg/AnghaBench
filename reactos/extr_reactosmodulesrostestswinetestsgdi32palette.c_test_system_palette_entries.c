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
typedef  int /*<<< orphan*/  HMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CloseMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateMetaFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RASTERCAPS ; 
 int RC_PALETTE ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_system_palette_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_system_palette_entries(void)
{
    HDC hdc;
    HDC metafile_dc;
    HMETAFILE metafile;

    hdc = GetDC(0);

    if (!(GetDeviceCaps( hdc, RASTERCAPS ) & RC_PALETTE))
    {
        check_system_palette_entries(hdc);
    }
    else
    {
        skip( "device is palette-based, skipping test\n" );
    }

    ReleaseDC( 0, hdc );

    metafile_dc = CreateMetaFileA(NULL);

    check_system_palette_entries(metafile_dc);

    metafile = CloseMetaFile(metafile_dc);
    DeleteMetaFile(metafile);
}