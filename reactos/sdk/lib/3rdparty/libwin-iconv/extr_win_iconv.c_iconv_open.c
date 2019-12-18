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
typedef  int /*<<< orphan*/  rec_iconv_t ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ libiconv_iconv_open (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ win_iconv_open (int /*<<< orphan*/ *,char const*,char const*) ; 

iconv_t
iconv_open(const char *tocode, const char *fromcode)
{
    rec_iconv_t *cd;

    cd = (rec_iconv_t *)calloc(1, sizeof(rec_iconv_t));
    if (cd == NULL)
        return (iconv_t)(-1);

#if defined(USE_LIBICONV_DLL)
    errno = 0;
    if (libiconv_iconv_open(cd, tocode, fromcode))
        return (iconv_t)cd;
#endif

    /* reset the errno to prevent reporting wrong error code.
     * 0 for unsorted error. */
    errno = 0;
    if (win_iconv_open(cd, tocode, fromcode))
        return (iconv_t)cd;

    free(cd);

    return (iconv_t)(-1);
}