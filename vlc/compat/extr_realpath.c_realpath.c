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
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,size_t) ; 
 size_t WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t _MAX_PATH ; 
 int /*<<< orphan*/ * _wfullpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

char *realpath(const char * restrict relpath, char * restrict resolved_path)
{
    if (relpath == NULL)
    {
        errno = EINVAL;
        return NULL;
    }

#ifdef _WIN32
    size_t len = MultiByteToWideChar( CP_UTF8, 0, relpath, -1, NULL, 0 );
    if (len == 0)
        return NULL;

    wchar_t *wrelpath = malloc(len * sizeof (wchar_t));
    if (wrelpath == NULL)
        return NULL;

    MultiByteToWideChar( CP_UTF8, 0, relpath, -1, wrelpath, len );

    wchar_t *wfullpath = _wfullpath( NULL, wrelpath, _MAX_PATH );
    free(wrelpath);
    if (wfullpath != NULL)
    {
        len = WideCharToMultiByte( CP_UTF8, 0, wfullpath, -1, NULL, 0, NULL, NULL );
        if (len != 0)
        {
            if (resolved_path != NULL)
                len = len >= _MAX_PATH ? _MAX_PATH : len;
            else
                resolved_path = (char *)malloc(len);

            if (resolved_path != NULL)
                WideCharToMultiByte( CP_UTF8, 0, wfullpath, -1, resolved_path, len, NULL, NULL );
            free(wfullpath);
            return resolved_path;
        }
        free(wfullpath);
    }
#else
    (void)resolved_path;
#endif
    errno = EACCES;
    return NULL;
}