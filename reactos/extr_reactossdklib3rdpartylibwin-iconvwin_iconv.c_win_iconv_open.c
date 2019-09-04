#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cd; int /*<<< orphan*/  _errno; int /*<<< orphan*/  iconv; int /*<<< orphan*/  iconv_close; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ rec_iconv_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _errno ; 
 int /*<<< orphan*/  make_csconv (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_iconv ; 
 int /*<<< orphan*/  win_iconv_close ; 

__attribute__((used)) static int
win_iconv_open(rec_iconv_t *cd, const char *tocode, const char *fromcode)
{
    if (!make_csconv(fromcode, &cd->from) || !make_csconv(tocode, &cd->to))
        return FALSE;
    cd->iconv_close = win_iconv_close;
    cd->iconv = win_iconv;
    cd->_errno = _errno;
    cd->cd = (iconv_t)cd;
    return TRUE;
}