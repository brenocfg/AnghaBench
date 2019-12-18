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
struct TYPE_3__ {int (* iconv_close ) (int /*<<< orphan*/ ) ;int* (* _errno ) () ;int /*<<< orphan*/ * hlibiconv; int /*<<< orphan*/  cd; } ;
typedef  TYPE_1__ rec_iconv_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int* stub2 () ; 

int
iconv_close(iconv_t _cd)
{
    rec_iconv_t *cd = (rec_iconv_t *)_cd;
    int r = cd->iconv_close(cd->cd);
    int e = *(cd->_errno());
#if defined(USE_LIBICONV_DLL)
    if (cd->hlibiconv != NULL)
        FreeLibrary(cd->hlibiconv);
#endif
    free(cd);
    errno = e;
    return r;
}