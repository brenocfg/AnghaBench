#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* psz_iso639_1; int /*<<< orphan*/  psz_eng_name; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
 TYPE_1__* GetLang_1 (char const*) ; 
 TYPE_1__* GetLang_2B (char const*) ; 
 TYPE_1__* GetLang_2T (char const*) ; 
 char* LanguageGetCode (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 char const* vlc_gettext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *LanguageGetName( const char *psz_code )
{
    const iso639_lang_t *pl;

    if( psz_code == NULL || !strcmp( psz_code, "und" ) )
    {
        return strdup( "" );
    }

    if( strlen( psz_code ) == 2 )
    {
        pl = GetLang_1( psz_code );
    }
    else if( strlen( psz_code ) == 3 )
    {
        pl = GetLang_2B( psz_code );
        if( !strcmp( pl->psz_iso639_1, "??" ) )
        {
            pl = GetLang_2T( psz_code );
        }
    }
    else
    {
        char *lang = LanguageGetCode( psz_code );
        pl = GetLang_1( lang );
        free( lang );
    }

    if( !strcmp( pl->psz_iso639_1, "??" ) )
    {
       return strdup( psz_code );
    }
    else
    {
        return strdup( vlc_gettext(pl->psz_eng_name) );
    }
}