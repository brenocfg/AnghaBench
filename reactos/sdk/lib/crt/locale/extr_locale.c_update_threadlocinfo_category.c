#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* locinfo; } ;
struct TYPE_8__ {TYPE_2__* lc_category; int /*<<< orphan*/ * lc_handle; TYPE_1__* lc_id; } ;
struct TYPE_7__ {int* locale; int* refcount; } ;
struct TYPE_6__ {int wLanguage; char wCountry; unsigned short wCodePage; } ;
typedef  TYPE_4__* MSVCRT__locale_t ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLocaleInfoA (int /*<<< orphan*/ ,int,char*,int) ; 
 int LOCALE_ILANGUAGE ; 
 int LOCALE_NOUSEROVERRIDE ; 
 int LOCALE_SENGCOUNTRY ; 
 int LOCALE_SENGLANGUAGE ; 
 int /*<<< orphan*/  MSVCRT_free (int*) ; 
 void* MSVCRT_malloc (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static BOOL update_threadlocinfo_category(LCID lcid, unsigned short cp,
        MSVCRT__locale_t loc, int category)
{
    char buf[256], *p;
    int len;

    if(GetLocaleInfoA(lcid, LOCALE_ILANGUAGE|LOCALE_NOUSEROVERRIDE, buf, 256)) {
        p = buf;

        loc->locinfo->lc_id[category].wLanguage = 0;
        while(*p) {
            loc->locinfo->lc_id[category].wLanguage *= 16;

            if(*p <= '9')
                loc->locinfo->lc_id[category].wLanguage += *p-'0';
            else
                loc->locinfo->lc_id[category].wLanguage += *p-'a'+10;

            p++;
        }

        loc->locinfo->lc_id[category].wCountry =
            loc->locinfo->lc_id[category].wLanguage;
    }

    loc->locinfo->lc_id[category].wCodePage = cp;

    loc->locinfo->lc_handle[category] = lcid;

    len = 0;
    len += GetLocaleInfoA(lcid, LOCALE_SENGLANGUAGE
            |LOCALE_NOUSEROVERRIDE, buf, 256);
    buf[len-1] = '_';
    len += GetLocaleInfoA(lcid, LOCALE_SENGCOUNTRY
            |LOCALE_NOUSEROVERRIDE, &buf[len], 256-len);
    buf[len-1] = '.';
    sprintf(buf+len, "%u", cp);
    len += strlen(buf+len)+1;

    loc->locinfo->lc_category[category].locale = MSVCRT_malloc(len);
    loc->locinfo->lc_category[category].refcount = MSVCRT_malloc(sizeof(int));
    if(!loc->locinfo->lc_category[category].locale
            || !loc->locinfo->lc_category[category].refcount) {
        MSVCRT_free(loc->locinfo->lc_category[category].locale);
        MSVCRT_free(loc->locinfo->lc_category[category].refcount);
        loc->locinfo->lc_category[category].locale = NULL;
        loc->locinfo->lc_category[category].refcount = NULL;
        return TRUE;
    }
    memcpy(loc->locinfo->lc_category[category].locale, buf, len);
    *loc->locinfo->lc_category[category].refcount = 1;

    return FALSE;
}