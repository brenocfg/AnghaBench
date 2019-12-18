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
 int /*<<< orphan*/  LocaleFree (char*) ; 
 char const* PACKAGE_NAME ; 
 char* ToLocale (char*) ; 
 int /*<<< orphan*/  VLC_LOCALE_DIR ; 
 int /*<<< orphan*/ * bind_textdomain_codeset (char const*,char*) ; 
 int /*<<< orphan*/ * bindtextdomain (char const*,char*) ; 
 char* config_GetSysPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int vlc_bindtextdomain (const char *domain)
{
#if defined (ENABLE_NLS)
    /* Specify where to find the locales for current domain */
    char *upath = config_GetSysPath(VLC_LOCALE_DIR, NULL);
    if (unlikely(upath == NULL))
        return -1;

    char *lpath = ToLocale(upath);
    if (lpath == NULL || bindtextdomain (domain, lpath) == NULL)
    {
        LocaleFree(lpath);
        fprintf (stderr, "%s: text domain not found in %s\n", domain, upath);
        free (upath);
        return -1;
    }
    LocaleFree(lpath);
    free (upath);

    /* LibVLC wants all messages in UTF-8.
     * Unfortunately, we cannot ask UTF-8 for strerror_r(), strsignal_r()
     * and other functions that are not part of our text domain.
     */
    if (bind_textdomain_codeset (PACKAGE_NAME, "UTF-8") == NULL)
    {
        fprintf (stderr, "%s: UTF-8 encoding not available\n", domain);
        // Unbinds the text domain to avoid broken encoding
        bindtextdomain (PACKAGE_NAME, "/DOES_NOT_EXIST");
        return -1;
    }

    /* LibVLC does NOT set the default textdomain, since it is a library.
     * This could otherwise break programs using LibVLC (other than VLC).
     * textdomain (PACKAGE_NAME);
     */

#else /* !ENABLE_NLS */
    (void)domain;
#endif

    return 0;
}