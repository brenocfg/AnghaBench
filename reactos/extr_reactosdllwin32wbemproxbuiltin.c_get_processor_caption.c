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
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 
 scalar_t__ get_osarchitecture () ; 
 scalar_t__ os_32bitW ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char const*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void get_processor_caption( WCHAR *caption )
{
    static const WCHAR fmtW[] =
        {'%','s',' ','F','a','m','i','l','y',' ','%','u',' ',
         'M','o','d','e','l',' ','%','u',' ','S','t','e','p','p','i','n','g',' ','%','u',0};
    static const WCHAR x86W[] = {'x','8','6',0};
    static const WCHAR intel64W[] = {'I','n','t','e','l','6','4',0};
    const WCHAR *arch = (get_osarchitecture() == os_32bitW) ? x86W : intel64W;
    unsigned int regs[4] = {0, 0, 0, 0};

    do_cpuid( 1, regs );
    sprintfW( caption, fmtW, arch, (regs[0] & (15 << 8)) >> 8, (regs[0] & (15 << 4)) >> 4, regs[0] & 15 );
}