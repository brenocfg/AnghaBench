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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 char* FromWide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDNA_ALLOW_UNASSIGNED ; 
#define  IDNA_DLOPEN_ERROR 130 
#define  IDNA_MALLOC_ERROR 129 
#define  IDNA_SUCCESS 128 
 int /*<<< orphan*/  IDN_ALLOW_UNASSIGNED ; 
 int IdnToAscii (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ToWide (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int idna_to_ascii_8z (char const*,char**,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_alloc (int,int) ; 

__attribute__((used)) static char *vlc_idna_to_ascii (const char *idn)
{
#if defined (HAVE_IDN)
    char *adn;

    switch (idna_to_ascii_8z(idn, &adn, IDNA_ALLOW_UNASSIGNED))
    {
        case IDNA_SUCCESS:
            return adn;
        case IDNA_MALLOC_ERROR:
            errno = ENOMEM;
            return NULL;
        case IDNA_DLOPEN_ERROR:
            errno = ENOSYS;
            return NULL;
        default:
            errno = EINVAL;
            return NULL;
    }

#elif defined (_WIN32)
    char *ret = NULL;

    if (idn[0] == '\0')
        return strdup("");

    wchar_t *wide = ToWide (idn);
    if (wide == NULL)
        return NULL;

    int len = IdnToAscii (IDN_ALLOW_UNASSIGNED, wide, -1, NULL, 0);
    if (len == 0)
    {
        errno = EINVAL;
        goto error;
    }

    wchar_t *buf = vlc_alloc (len, sizeof (*buf));
    if (unlikely(buf == NULL))
        goto error;
    if (!IdnToAscii (IDN_ALLOW_UNASSIGNED, wide, -1, buf, len))
    {
        free (buf);
        errno = EINVAL;
        goto error;
    }
    ret = FromWide (buf);
    free (buf);
error:
    free (wide);
    return ret;

#else
    /* No IDN support, filter out non-ASCII domain names */
    for (const char *p = idn; *p; p++)
        if (((unsigned char)*p) >= 0x80)
        {
            errno = ENOSYS;
            return NULL;
        }

    return strdup (idn);

#endif
}