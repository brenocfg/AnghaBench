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
struct font_data {char* member_0; int member_1; int member_3; int member_4; int member_5; int member_6; int member_8; int /*<<< orphan*/  const member_9; int /*<<< orphan*/  member_7; int /*<<< orphan*/  const member_2; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeleteFileA (char*) ; 
 int ERROR_ACCESS_DENIED ; 
#define  FALSE 130 
 int /*<<< orphan*/  FR_PRIVATE ; 
#define  FW_NORMAL 129 
 int GET_BE_WORD (int) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MS_MAKE_TAG (char,char,char,char) ; 
#define  TRUE 128 
 scalar_t__ broken (int) ; 
 int* find_ttf_table (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* get_res_data (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_truetype_font_installed (char*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pAddFontResourceExA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRemoveFontResourceExA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_height (int /*<<< orphan*/ ,struct font_data const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  write_tmp_file (void*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_height_selection_vdmx( HDC hdc )
{
    static const struct font_data charset_0[] = /* doesn't use VDMX */
    {
        { "wine_vdmx", 10, FW_NORMAL, 10, 8, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 11, FW_NORMAL, 11, 9, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 12, FW_NORMAL, 12, 10, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 13, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 14, FW_NORMAL, 14, 12, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 15, FW_NORMAL, 15, 12, 3, 3, 0, 96, FALSE },
        { "wine_vdmx", 16, FW_NORMAL, 16, 13, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 17, FW_NORMAL, 17, 14, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 18, FW_NORMAL, 18, 15, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 19, FW_NORMAL, 19, 16, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 20, FW_NORMAL, 20, 17, 3, 4, 0, 96, FALSE },
        { "wine_vdmx", 21, FW_NORMAL, 21, 17, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", 22, FW_NORMAL, 22, 18, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", 23, FW_NORMAL, 23, 19, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", 24, FW_NORMAL, 24, 20, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", 25, FW_NORMAL, 25, 21, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", 26, FW_NORMAL, 26, 22, 4, 5, 0, 96, FALSE },
        { "wine_vdmx", 27, FW_NORMAL, 27, 22, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", 28, FW_NORMAL, 28, 23, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", 29, FW_NORMAL, 29, 24, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", 30, FW_NORMAL, 30, 25, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", 31, FW_NORMAL, 31, 26, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", 32, FW_NORMAL, 32, 27, 5, 6, 0, 96, FALSE },
        { "wine_vdmx", 48, FW_NORMAL, 48, 40, 8, 8, 0, 96, TRUE },
        { "wine_vdmx", 64, FW_NORMAL, 64, 53, 11, 11, 0, 96, TRUE },
        { "wine_vdmx", 96, FW_NORMAL, 96, 80, 16, 17, 0, 96, FALSE },
        { "wine_vdmx", -10, FW_NORMAL, 12, 10, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", -11, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", -12, FW_NORMAL, 14, 12, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", -13, FW_NORMAL, 16, 13, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", -14, FW_NORMAL, 17, 14, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", -15, FW_NORMAL, 18, 15, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", -16, FW_NORMAL, 19, 16, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", -17, FW_NORMAL, 21, 17, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", -18, FW_NORMAL, 22, 18, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", -19, FW_NORMAL, 23, 19, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", -20, FW_NORMAL, 24, 20, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", -21, FW_NORMAL, 25, 21, 4, 4, 0, 96, TRUE },
        { "wine_vdmx", -22, FW_NORMAL, 27, 22, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", -23, FW_NORMAL, 28, 23, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", -24, FW_NORMAL, 29, 24, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", -25, FW_NORMAL, 30, 25, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", -26, FW_NORMAL, 31, 26, 5, 5, 0, 96, TRUE },
        { "wine_vdmx", -27, FW_NORMAL, 33, 27, 6, 6, 0, 96, TRUE },
        { "wine_vdmx", -28, FW_NORMAL, 34, 28, 6, 6, 0, 96, TRUE },
        { "wine_vdmx", -29, FW_NORMAL, 35, 29, 6, 6, 0, 96, TRUE },
        { "wine_vdmx", -30, FW_NORMAL, 36, 30, 6, 6, 0, 96, TRUE },
        { "wine_vdmx", -31, FW_NORMAL, 37, 31, 6, 6, 0, 96, TRUE },
        { "wine_vdmx", -32, FW_NORMAL, 39, 32, 7, 7, 0, 96, TRUE },
        { "wine_vdmx", -48, FW_NORMAL, 58, 48, 10, 10, 0, 96, TRUE },
        { "wine_vdmx", -64, FW_NORMAL, 77, 64, 13, 13, 0, 96, TRUE },
        { "wine_vdmx", -96, FW_NORMAL, 116, 96, 20, 20, 0, 96, TRUE },
        { "", 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    static const struct font_data charset_1[] = /* Uses VDMX */
    {
        { "wine_vdmx", 10, FW_NORMAL, 10, 8, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 11, FW_NORMAL, 11, 9, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 12, FW_NORMAL, 12, 10, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 13, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 14, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 15, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", 16, FW_NORMAL, 16, 13, 3, 4, 0, 96, TRUE },
        { "wine_vdmx", 17, FW_NORMAL, 16, 13, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 18, FW_NORMAL, 16, 13, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", 19, FW_NORMAL, 19, 15, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 20, FW_NORMAL, 20, 16, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 21, FW_NORMAL, 21, 17, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 22, FW_NORMAL, 22, 18, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 23, FW_NORMAL, 23, 19, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 24, FW_NORMAL, 23, 19, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 25, FW_NORMAL, 25, 21, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", 26, FW_NORMAL, 26, 22, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", 27, FW_NORMAL, 27, 23, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", 28, FW_NORMAL, 27, 23, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", 29, FW_NORMAL, 29, 24, 5, 6, 0, 96, TRUE },
        { "wine_vdmx", 30, FW_NORMAL, 29, 24, 5, 6, 0, 96, TRUE },
        { "wine_vdmx", 31, FW_NORMAL, 29, 24, 5, 6, 0, 96, TRUE },
        { "wine_vdmx", 32, FW_NORMAL, 32, 26, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", 48, FW_NORMAL, 48, 40, 8, 10, 0, 96, TRUE },
        { "wine_vdmx", 64, FW_NORMAL, 64, 54, 10, 13, 0, 96, TRUE },
        { "wine_vdmx", 96, FW_NORMAL, 95, 79, 16, 18, 0, 96, TRUE },
        { "wine_vdmx", -10, FW_NORMAL, 12, 10, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", -11, FW_NORMAL, 13, 11, 2, 2, 0, 96, TRUE },
        { "wine_vdmx", -12, FW_NORMAL, 16, 13, 3, 4, 0, 96, TRUE },
        { "wine_vdmx", -13, FW_NORMAL, 16, 13, 3, 3, 0, 96, TRUE },
        { "wine_vdmx", -14, FW_NORMAL, 19, 15, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -15, FW_NORMAL, 20, 16, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -16, FW_NORMAL, 21, 17, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -17, FW_NORMAL, 22, 18, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -18, FW_NORMAL, 23, 19, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -19, FW_NORMAL, 25, 21, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", -20, FW_NORMAL, 26, 22, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", -21, FW_NORMAL, 27, 23, 4, 6, 0, 96, TRUE },
        { "wine_vdmx", -22, FW_NORMAL, 27, 23, 4, 5, 0, 96, TRUE },
        { "wine_vdmx", -23, FW_NORMAL, 29, 24, 5, 6, 0, 96, TRUE },
        { "wine_vdmx", -24, FW_NORMAL, 32, 26, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", -25, FW_NORMAL, 32, 26, 6, 7, 0, 96, TRUE },
        { "wine_vdmx", -26, FW_NORMAL, 33, 27, 6, 7, 0, 96, TRUE },
        { "wine_vdmx", -27, FW_NORMAL, 35, 29, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", -28, FW_NORMAL, 36, 30, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", -29, FW_NORMAL, 36, 30, 6, 7, 0, 96, TRUE },
        { "wine_vdmx", -30, FW_NORMAL, 38, 32, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", -31, FW_NORMAL, 39, 33, 6, 8, 0, 96, TRUE },
        { "wine_vdmx", -32, FW_NORMAL, 40, 33, 7, 8, 0, 96, TRUE },
        { "wine_vdmx", -48, FW_NORMAL, 60, 50, 10, 12, 0, 96, TRUE },
        { "wine_vdmx", -64, FW_NORMAL, 81, 67, 14, 17, 0, 96, TRUE },
        { "wine_vdmx", -96, FW_NORMAL, 119, 99, 20, 23, 0, 96, TRUE },
        { "", 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    static const struct vdmx_data
    {
        WORD version;
        BYTE bCharSet;
        const struct font_data *fd;
    } data[] =
    {
        { 0, 0, charset_0 },
        { 0, 1, charset_1 },
        { 1, 0, charset_0 },
        { 1, 1, charset_1 }
    };
    int i;
    DWORD size, num;
    WORD *vdmx_header;
    BYTE *ratio_rec;
    char ttf_name[MAX_PATH];
    void *res, *copy;
    BOOL ret;

    if (!pAddFontResourceExA)
    {
        win_skip("AddFontResourceExA unavailable\n");
        return;
    }

    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
        res = get_res_data( "wine_vdmx.ttf", &size );

        copy = HeapAlloc( GetProcessHeap(), 0, size );
        memcpy( copy, res, size );
        vdmx_header = find_ttf_table( copy, size, MS_MAKE_TAG('V','D','M','X') );
        vdmx_header[0] = GET_BE_WORD( data[i].version );
        ok( GET_BE_WORD( vdmx_header[1] ) == 1, "got %04x\n", GET_BE_WORD( vdmx_header[1] ) );
        ok( GET_BE_WORD( vdmx_header[2] ) == 1, "got %04x\n", GET_BE_WORD( vdmx_header[2] ) );
        ratio_rec = (BYTE *)&vdmx_header[3];
        ratio_rec[0] = data[i].bCharSet;

        write_tmp_file( copy, &size, ttf_name );
        HeapFree( GetProcessHeap(), 0, copy );

        ok( !is_truetype_font_installed("wine_vdmx"), "Already installed\n" );
        num = pAddFontResourceExA( ttf_name, FR_PRIVATE, 0 );
        if (!num) win_skip("Unable to add ttf font resource\n");
        else
        {
            ok( is_truetype_font_installed("wine_vdmx"), "Not installed\n" );
            test_height( hdc, data[i].fd );
            pRemoveFontResourceExA( ttf_name, FR_PRIVATE, 0 );
        }
        ret = DeleteFileA( ttf_name );
        ok(ret || broken(!ret && GetLastError() == ERROR_ACCESS_DENIED),
           "DeleteFile error %d\n", GetLastError());
    }
}