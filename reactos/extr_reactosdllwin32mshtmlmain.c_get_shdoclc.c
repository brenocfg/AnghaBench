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
typedef  scalar_t__ HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_LIBRARY_AS_DATAFILE ; 
 scalar_t__ LoadLibraryExW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ shdoclc ; 

HINSTANCE get_shdoclc(void)
{
    static const WCHAR wszShdoclc[] =
        {'s','h','d','o','c','l','c','.','d','l','l',0};

    if(shdoclc)
        return shdoclc;

    return shdoclc = LoadLibraryExW(wszShdoclc, NULL, LOAD_LIBRARY_AS_DATAFILE);
}