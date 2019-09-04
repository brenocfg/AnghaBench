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
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 char* PathFindExtensionW (char*) ; 
 char* StrChrW (char*,char) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR get_first_ext_from_spec(LPWSTR buf, LPCWSTR spec)
{
    WCHAR *endpos, *ext;

    lstrcpyW(buf, spec);
    if( (endpos = StrChrW(buf, ';')) )
        *endpos = '\0';

    ext = PathFindExtensionW(buf);
    if(StrChrW(ext, '*'))
        return NULL;

    return ext;
}