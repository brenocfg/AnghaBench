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
struct TYPE_5__ {int /*<<< orphan*/  psz_iso639_2T; scalar_t__ psz_eng_name; } ;
typedef  TYPE_1__ iso639_lang_t ;

/* Variables and functions */
 TYPE_1__* p_languages ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_1__ const unknown_language ; 

const iso639_lang_t * GetLang_2T( const char * psz_code )
{
    const iso639_lang_t *p_lang;

    for( p_lang = p_languages; p_lang->psz_eng_name; p_lang++ )
        if( !strncasecmp( p_lang->psz_iso639_2T, psz_code, 3 ) )
            return p_lang;

    return &unknown_language;
}