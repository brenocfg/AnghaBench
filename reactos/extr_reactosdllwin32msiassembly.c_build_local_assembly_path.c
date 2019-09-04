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
typedef  size_t UINT ;

/* Variables and functions */
 char* msi_alloc (int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *build_local_assembly_path( const WCHAR *filename )
{
    UINT i;
    WCHAR *ret;

    if (!(ret = msi_alloc( (strlenW( filename ) + 1) * sizeof(WCHAR) )))
        return NULL;

    for (i = 0; filename[i]; i++)
    {
        if (filename[i] == '\\' || filename[i] == '/') ret[i] = '|';
        else ret[i] = filename[i];
    }
    ret[i] = 0;
    return ret;
}