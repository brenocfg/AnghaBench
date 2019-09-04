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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_ID_VERSION ; 
 int atoiW (char*) ; 
 scalar_t__ isdigitW (char) ; 
 char* load_ttf_name_id (char const*,int /*<<< orphan*/ ) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int,int) ; 
 char* strchrW (char*,char) ; 
 int strlenW (char const*) ; 

WCHAR *msi_font_version_from_file( const WCHAR *filename )
{
    static const WCHAR fmtW[] = {'%','u','.','%','u','.','0','.','0',0};
    WCHAR *version, *p, *q, *ret = NULL;

    if ((version = load_ttf_name_id( filename, NAME_ID_VERSION )))
    {
        int len, major = 0, minor = 0;
        if ((p = strchrW( version, ';' ))) *p = 0;
        p = version;
        while (*p && !isdigitW( *p )) p++;
        if ((q = strchrW( p, '.' )))
        {
            major = atoiW( p );
            p = ++q;
            while (*q && isdigitW( *q )) q++;
            if (!*q || *q == ' ') minor = atoiW( p );
            else major = 0;
        }
        len = strlenW( fmtW ) + 20;
        ret = msi_alloc( len * sizeof(WCHAR) );
        sprintfW( ret, fmtW, major, minor );
        msi_free( version );
    }
    return ret;
}