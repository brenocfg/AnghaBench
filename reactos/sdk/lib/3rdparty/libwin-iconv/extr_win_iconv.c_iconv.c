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
struct TYPE_2__ {size_t (* iconv ) (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ;int /*<<< orphan*/ * (* _errno ) () ;int /*<<< orphan*/  cd; } ;
typedef  TYPE_1__ rec_iconv_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 size_t stub1 (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/ * stub2 () ; 

size_t
iconv(iconv_t _cd, const char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft)
{
    rec_iconv_t *cd = (rec_iconv_t *)_cd;
    size_t r = cd->iconv(cd->cd, inbuf, inbytesleft, outbuf, outbytesleft);
    errno = *(cd->_errno());
    return r;
}