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

/* Variables and functions */
 int /*<<< orphan*/  serverAssert (int) ; 
 unsigned char* ziplistPrev (unsigned char*,unsigned char*) ; 

void zzlPrev(unsigned char *zl, unsigned char **eptr, unsigned char **sptr) {
    unsigned char *_eptr, *_sptr;
    serverAssert(*eptr != NULL && *sptr != NULL);

    _sptr = ziplistPrev(zl,*eptr);
    if (_sptr != NULL) {
        _eptr = ziplistPrev(zl,_sptr);
        serverAssert(_eptr != NULL);
    } else {
        /* No previous entry. */
        _eptr = NULL;
    }

    *eptr = _eptr;
    *sptr = _sptr;
}