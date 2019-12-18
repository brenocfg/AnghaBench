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
typedef  scalar_t__ vlc_iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int iconv_close (scalar_t__) ; 

int vlc_iconv_close( vlc_iconv_t cd )
{
#ifndef __linux__
    if ( cd == (vlc_iconv_t)(-2) || cd == (vlc_iconv_t)(-3) )
        return 0;
#endif
#if defined(HAVE_ICONV)
    return iconv_close( cd );
#else
    abort ();
#endif
}