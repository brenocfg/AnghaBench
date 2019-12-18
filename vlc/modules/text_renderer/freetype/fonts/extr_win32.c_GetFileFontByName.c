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
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int ConcatenatedIndex (char*,char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FONT_DIR_NT ; 
 char* FromWide (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValue (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int GetFileFontByName( const WCHAR * font_name, char **psz_filename, int *i_index )
{
    HKEY hKey;
    WCHAR vbuffer[MAX_PATH];
    WCHAR dbuffer[256];

    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, FONT_DIR_NT, 0, KEY_READ, &hKey)
            != ERROR_SUCCESS )
        return 1;

    char *font_name_temp = FromWide( font_name );

    for( int index = 0;; index++ )
    {
        DWORD vbuflen = MAX_PATH - 1;
        DWORD dbuflen = 255;

        LONG i_result = RegEnumValue( hKey, index, vbuffer, &vbuflen,
                                      NULL, NULL, (LPBYTE)dbuffer, &dbuflen);
        if( i_result != ERROR_SUCCESS )
        {
            free( font_name_temp );
            RegCloseKey( hKey );
            return i_result;
        }

        char *psz_value = FromWide( vbuffer );

        char *s = strchr( psz_value,'(' );
        if( s != NULL && s != psz_value ) s[-1] = '\0';

        int i_concat_idx = 0;
        if( ( i_concat_idx = ConcatenatedIndex( psz_value, font_name_temp ) ) != -1 )
        {
            *i_index = i_concat_idx;
            *psz_filename = FromWide( dbuffer );
            free( psz_value );
            break;
        }

        free( psz_value );
    }

    free( font_name_temp );
    RegCloseKey( hKey );
    return 0;
}