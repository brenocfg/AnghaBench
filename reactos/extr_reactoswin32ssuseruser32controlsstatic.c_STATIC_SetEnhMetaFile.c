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
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HENHMETAFILE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ GetObjectType (scalar_t__) ; 
 int /*<<< orphan*/  HICON_GWL_OFFSET ; 
 scalar_t__ OBJ_ENHMETAFILE ; 
 int SS_ENHMETAFILE ; 
 int SS_TYPEMASK ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HENHMETAFILE STATIC_SetEnhMetaFile( HWND hwnd, HENHMETAFILE hEnhMetaFile, DWORD style )
{
    if ((style & SS_TYPEMASK) != SS_ENHMETAFILE) return 0;
    if (hEnhMetaFile && GetObjectType(hEnhMetaFile) != OBJ_ENHMETAFILE) {
        WARN("hEnhMetaFile != 0, but it's not an enhanced metafile\n");
        return 0;
    }
    return (HENHMETAFILE)SetWindowLongPtrW( hwnd, HICON_GWL_OFFSET, (LONG_PTR)hEnhMetaFile );
}