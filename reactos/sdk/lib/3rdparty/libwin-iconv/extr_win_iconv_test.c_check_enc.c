#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int codepage; } ;
struct TYPE_4__ {TYPE_1__ from; } ;
typedef  TYPE_2__ rec_iconv_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,...) ; 

int
check_enc(const char *encname, int codepage)
{
    iconv_t cd;
    int cp;
    cd = iconv_open("utf-8", encname);
    if (cd == (iconv_t)(-1))
    {
        printf("%s(%d) IS NOT SUPPORTED: SKIP THE TEST\n", encname, codepage);
        return FALSE;
    }
#ifndef USE_ICONV_H
    cp = ((rec_iconv_t *)cd)->from.codepage;
    if (cp != codepage)
    {
        printf("%s(%d) ALIAS IS MAPPED TO DIFFERENT CODEPAGE (%d)\n", encname, codepage, cp);
        exit(1);
    }
#endif
    iconv_close(cd);
    return TRUE;
}