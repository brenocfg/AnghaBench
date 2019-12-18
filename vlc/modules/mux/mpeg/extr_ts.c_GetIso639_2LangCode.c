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
struct TYPE_5__ {char const* psz_iso639_2T; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
 TYPE_1__* GetLang_1 (char const*) ; 
 TYPE_1__* GetLang_2B (char const*) ; 
 TYPE_1__* GetLang_2T (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *GetIso639_2LangCode(const char *lang)
{
    const iso639_lang_t *pl;

    if (strlen(lang) == 2)
    {
        pl = GetLang_1(lang);
    }
    else
    {
        pl = GetLang_2B(lang);      /* try native code first */
        if (!*pl->psz_iso639_2T)
            pl = GetLang_2T(lang);  /* else fallback to english code */

    }

    return pl->psz_iso639_2T;   /* returns the english code */
}