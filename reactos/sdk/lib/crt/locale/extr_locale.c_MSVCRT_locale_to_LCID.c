#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* search_language; char* search_country; char* search_codepage; int match_flags; char* found_codepage; int /*<<< orphan*/  found_lang_id; } ;
typedef  TYPE_1__ locale_search_t ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int LCID ;

/* Variables and functions */
 int /*<<< orphan*/  EnumResourceLanguagesA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FOUND_CODEPAGE ; 
 int FOUND_COUNTRY ; 
 int /*<<< orphan*/  GetLocaleInfoA (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ IsValidCodePage (unsigned short) ; 
 int /*<<< orphan*/  LOCALE_IDEFAULTANSICODEPAGE ; 
 int /*<<< orphan*/  LOCALE_IDEFAULTCODEPAGE ; 
 scalar_t__ LOCALE_ILANGUAGE ; 
 int MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_ELEM_LEN ; 
 scalar_t__ RT_STRING ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 unsigned short atoi (char*) ; 
 int /*<<< orphan*/  find_best_locale_proc ; 
 int /*<<< orphan*/  lstrcpynA (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remap_synonym (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strchr (char const*,char) ; 

LCID MSVCRT_locale_to_LCID(const char *locale, unsigned short *codepage)
{
    LCID lcid;
    locale_search_t search;
    const char *cp, *region;

    memset(&search, 0, sizeof(locale_search_t));

    cp = strchr(locale, '.');
    region = strchr(locale, '_');

    lstrcpynA(search.search_language, locale, MAX_ELEM_LEN);
    if(region) {
        lstrcpynA(search.search_country, region+1, MAX_ELEM_LEN);
        if(region-locale < MAX_ELEM_LEN)
            search.search_language[region-locale] = '\0';
    } else
        search.search_country[0] = '\0';

    if(cp) {
        lstrcpynA(search.search_codepage, cp+1, MAX_ELEM_LEN);
        if(region && cp-region-1<MAX_ELEM_LEN)
          search.search_country[cp-region-1] = '\0';
        if(cp-locale < MAX_ELEM_LEN)
            search.search_language[cp-locale] = '\0';
    } else
        search.search_codepage[0] = '\0';

    if(!search.search_country[0] && !search.search_codepage[0])
        remap_synonym(search.search_language);

    EnumResourceLanguagesA(GetModuleHandleA("KERNEL32"), (LPSTR)RT_STRING,
            (LPCSTR)LOCALE_ILANGUAGE,find_best_locale_proc,
            (LONG_PTR)&search);

    if (!search.match_flags)
        return -1;

    /* If we were given something that didn't match, fail */
    if (search.search_country[0] && !(search.match_flags & FOUND_COUNTRY))
        return -1;

    lcid =  MAKELCID(search.found_lang_id, SORT_DEFAULT);

    /* Populate partial locale, translating LCID to locale string elements */
    if (!(search.match_flags & FOUND_CODEPAGE)) {
        /* Even if a codepage is not enumerated for a locale
         * it can be set if valid */
        if (search.search_codepage[0]) {
            if (IsValidCodePage(atoi(search.search_codepage)))
                memcpy(search.found_codepage,search.search_codepage,MAX_ELEM_LEN);
            else {
                /* Special codepage values: OEM & ANSI */
                if (!strcasecmp(search.search_codepage,"OCP")) {
                    GetLocaleInfoA(lcid, LOCALE_IDEFAULTCODEPAGE,
                            search.found_codepage, MAX_ELEM_LEN);
                } else if (!strcasecmp(search.search_codepage,"ACP")) {
                    GetLocaleInfoA(lcid, LOCALE_IDEFAULTANSICODEPAGE,
                            search.found_codepage, MAX_ELEM_LEN);
                } else
                    return -1;

                if (!atoi(search.found_codepage))
                    return -1;
            }
        } else {
            /* Prefer ANSI codepages if present */
            GetLocaleInfoA(lcid, LOCALE_IDEFAULTANSICODEPAGE,
                    search.found_codepage, MAX_ELEM_LEN);
            if (!search.found_codepage[0] || !atoi(search.found_codepage))
                GetLocaleInfoA(lcid, LOCALE_IDEFAULTCODEPAGE,
                        search.found_codepage, MAX_ELEM_LEN);
        }
    }
    if (codepage)
        *codepage = atoi(search.found_codepage);

    return lcid;
}