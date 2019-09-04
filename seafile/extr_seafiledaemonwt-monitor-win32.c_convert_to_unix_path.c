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
typedef  int /*<<< orphan*/  const wchar_t ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/  const*) ; 
 char* g_utf16_to_utf8 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* win32_83_path_to_long_path (char const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static char *
convert_to_unix_path (const char *worktree, const wchar_t *path, int path_len,
                      gboolean convert_long_path)
{
    char *utf8_path = NULL;

    if (convert_long_path) {
        wchar_t *long_path = win32_83_path_to_long_path (worktree,
                                                         path,
                                                         path_len/sizeof(wchar_t));
        if (long_path) {
            utf8_path = g_utf16_to_utf8 (long_path, -1, NULL, NULL, NULL);
            g_free (long_path);
        } else
            utf8_path = g_utf16_to_utf8 (path, path_len/sizeof(wchar_t),
                                         NULL, NULL, NULL);
    } else
        utf8_path = g_utf16_to_utf8 (path, path_len/sizeof(wchar_t), NULL, NULL, NULL);

    if (!utf8_path)
        return NULL;

    char *p;
    for (p = utf8_path; *p != 0; ++p)
        if (*p == '\\')
            *p = '/';

    return utf8_path;
}