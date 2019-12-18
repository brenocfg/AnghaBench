#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_2__ {int len; scalar_t__* strW; scalar_t__* strA; } ;
typedef  scalar_t__ HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_TEXT ; 
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CP_ACP ; 
 int CloseClipboard () ; 
 scalar_t__ GetClipboardData (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int GlobalSize (scalar_t__) ; 
 int IsClipboardFormatAvailable (int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int OpenClipboard (int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 TYPE_1__* test_data ; 
 int /*<<< orphan*/  wine_dbgstr_wn (scalar_t__,int) ; 

__attribute__((used)) static void test_string_data_process( int i )
{
    BOOL r;
    HANDLE data;
    UINT len, len2;
    char bufferA[12];
    WCHAR bufferW[12];

    r = OpenClipboard( 0 );
    ok( r, "gle %d\n", GetLastError() );
    if (test_data[i].strA[0])
    {
        data = GetClipboardData( CF_TEXT );
        ok( data != 0, "%u: could not get data\n", i );
        len = GlobalSize( data );
        ok( len == test_data[i].len, "%u: wrong size %u / %u\n", i, len, test_data[i].len );
        memcpy( bufferA, test_data[i].strA, test_data[i].len );
        bufferA[test_data[i].len - 1] = 0;
        ok( !memcmp( data, bufferA, len ), "%u: wrong data %.*s\n", i, len, (char *)data );
        data = GetClipboardData( CF_UNICODETEXT );
        ok( data != 0, "%u: could not get data\n", i );
        len = GlobalSize( data );
        len2 = MultiByteToWideChar( CP_ACP, 0, bufferA, test_data[i].len, bufferW, 12 );
        ok( len == len2 * sizeof(WCHAR), "%u: wrong size %u / %u\n", i, len, len2 );
        ok( !memcmp( data, bufferW, len ), "%u: wrong data %s\n", i, wine_dbgstr_wn( data, len2 ));
    }
    else
    {
        data = GetClipboardData( CF_UNICODETEXT );
        ok( data != 0, "%u: could not get data\n", i );
        len = GlobalSize( data );
        ok( len == test_data[i].len, "%u: wrong size %u / %u\n", i, len, test_data[i].len );
        memcpy( bufferW, test_data[i].strW, test_data[i].len );
        bufferW[(test_data[i].len + 1) / sizeof(WCHAR) - 1] = 0;
        ok( !memcmp( data, bufferW, len ),
            "%u: wrong data %s\n", i, wine_dbgstr_wn( data, (len + 1) / sizeof(WCHAR) ));
        data = GetClipboardData( CF_TEXT );
        if (test_data[i].len >= sizeof(WCHAR))
        {
            ok( data != 0, "%u: could not get data\n", i );
            len = GlobalSize( data );
            len2 = WideCharToMultiByte( CP_ACP, 0, bufferW, test_data[i].len / sizeof(WCHAR),
                                        bufferA, 12, NULL, NULL );
            bufferA[len2 - 1] = 0;
            ok( len == len2, "%u: wrong size %u / %u\n", i, len, len2 );
            ok( !memcmp( data, bufferA, len ), "%u: wrong data %.*s\n", i, len, (char *)data );
        }
        else
        {
            ok( !data, "%u: got data for empty string\n", i );
            ok( IsClipboardFormatAvailable( CF_TEXT ), "%u: text not available\n", i );
        }
    }
    r = CloseClipboard();
    ok( r, "gle %d\n", GetLastError() );
}