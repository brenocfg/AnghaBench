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
typedef  int /*<<< orphan*/  psz_locale ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  scalar_t__ CFArrayRef ;

/* Variables and functions */
 scalar_t__ CFArrayGetCount (scalar_t__) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CFBundleCopyLocalizationsForPreferences (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ CFLocaleCopyAvailableLocaleIdentifiers () ; 
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int /*<<< orphan*/  CFStringGetCString (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

void system_Init(void)
{
#ifdef ENABLE_NLS
    /* Check if $LANG is set. */
    if( NULL == getenv("LANG") )
    {
        /*
           Retrieve the preferred language as chosen in  System Preferences.app
           (note that CFLocaleCopyCurrent() is not used because it returns the
            preferred locale not language)
        */
        CFArrayRef all_locales, preferred_locales;
        char psz_locale[50];

        all_locales = CFLocaleCopyAvailableLocaleIdentifiers();

        preferred_locales = CFBundleCopyLocalizationsForPreferences( all_locales, NULL );

        if ( preferred_locales )
        {
            if ( CFArrayGetCount( preferred_locales ) )
            {
                CFStringRef user_language_string_ref = CFArrayGetValueAtIndex( preferred_locales, 0 );
                CFStringGetCString( user_language_string_ref, psz_locale, sizeof(psz_locale), kCFStringEncodingUTF8 );
                setenv( "LANG", psz_locale, 1 );
            }
            CFRelease( preferred_locales );
        }
        CFRelease( all_locales );
    }
#endif
}