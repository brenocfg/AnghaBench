#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int codepage; int /*<<< orphan*/ * compat; int /*<<< orphan*/ * mblen; void* wctomb; void* mbtowc; int /*<<< orphan*/ * flush; scalar_t__ mode; } ;
typedef  TYPE_1__ csconv_t ;
struct TYPE_6__ {int MaxCharSize; } ;
typedef  TYPE_2__ CPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int FALSE ; 
 int FLAG_IGNORE ; 
 int FLAG_TRANSLIT ; 
 int FLAG_USE_BOM ; 
 scalar_t__ GetCPInfo (int,TYPE_2__*) ; 
 scalar_t__ IsValidCodePage (int) ; 
 int TRUE ; 
 scalar_t__ _stricmp (char*,char*) ; 
 int /*<<< orphan*/ * cp20932_compat ; 
 int /*<<< orphan*/ * cp5022x_compat ; 
 int /*<<< orphan*/ * cp51932_compat ; 
 int /*<<< orphan*/ * cp932_compat ; 
 int /*<<< orphan*/ * dbcs_mblen ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * eucjp_mblen ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * iso2022jp_flush ; 
 void* iso2022jp_mbtowc ; 
 void* iso2022jp_wctomb ; 
 void* kernel_mbtowc ; 
 void* kernel_wctomb ; 
 scalar_t__ load_mlang () ; 
 int /*<<< orphan*/ * mbcs_mblen ; 
 void* mlang_mbtowc ; 
 void* mlang_wctomb ; 
 int name_to_codepage (char*) ; 
 int /*<<< orphan*/ * sbcs_mblen ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strrstr (char*,char*) ; 
 void* utf16_mbtowc ; 
 void* utf16_wctomb ; 
 void* utf32_mbtowc ; 
 void* utf32_wctomb ; 
 int /*<<< orphan*/ * utf8_mblen ; 
 char* xstrndup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_csconv(const char *_name, csconv_t *cv)
{
    CPINFO cpinfo;
    int use_compat = TRUE;
    int flag = 0;
    char *name;
    char *p;

    name = xstrndup(_name, strlen(_name));
    if (name == NULL)
        return FALSE;

    /* check for option "enc_name//opt1//opt2" */
    while ((p = strrstr(name, "//")) != NULL)
    {
        if (_stricmp(p + 2, "nocompat") == 0)
            use_compat = FALSE;
        else if (_stricmp(p + 2, "translit") == 0)
            flag |= FLAG_TRANSLIT;
        else if (_stricmp(p + 2, "ignore") == 0)
            flag |= FLAG_IGNORE;
        *p = 0;
    }

    cv->mode = 0;
    cv->flags = flag;
    cv->mblen = NULL;
    cv->flush = NULL;
    cv->compat = NULL;
    cv->codepage = name_to_codepage(name);
    if (cv->codepage == 1200 || cv->codepage == 1201)
    {
        cv->mbtowc = utf16_mbtowc;
        cv->wctomb = utf16_wctomb;
        if (_stricmp(name, "UTF-16") == 0 || _stricmp(name, "UTF16") == 0 ||
          _stricmp(name, "UCS-2") == 0 || _stricmp(name, "UCS2") == 0)
            cv->flags |= FLAG_USE_BOM;
    }
    else if (cv->codepage == 12000 || cv->codepage == 12001)
    {
        cv->mbtowc = utf32_mbtowc;
        cv->wctomb = utf32_wctomb;
        if (_stricmp(name, "UTF-32") == 0 || _stricmp(name, "UTF32") == 0 ||
          _stricmp(name, "UCS-4") == 0 || _stricmp(name, "UCS4") == 0)
            cv->flags |= FLAG_USE_BOM;
    }
    else if (cv->codepage == 65001)
    {
        cv->mbtowc = kernel_mbtowc;
        cv->wctomb = kernel_wctomb;
        cv->mblen = utf8_mblen;
    }
    else if ((cv->codepage == 50220 || cv->codepage == 50221 || cv->codepage == 50222) && load_mlang())
    {
        cv->mbtowc = iso2022jp_mbtowc;
        cv->wctomb = iso2022jp_wctomb;
        cv->flush = iso2022jp_flush;
    }
    else if (cv->codepage == 51932 && load_mlang())
    {
        cv->mbtowc = mlang_mbtowc;
        cv->wctomb = mlang_wctomb;
        cv->mblen = eucjp_mblen;
    }
    else if (IsValidCodePage(cv->codepage)
	     && GetCPInfo(cv->codepage, &cpinfo) != 0)
    {
        cv->mbtowc = kernel_mbtowc;
        cv->wctomb = kernel_wctomb;
        if (cpinfo.MaxCharSize == 1)
            cv->mblen = sbcs_mblen;
        else if (cpinfo.MaxCharSize == 2)
            cv->mblen = dbcs_mblen;
        else
	    cv->mblen = mbcs_mblen;
    }
    else
    {
        /* not supported */
        free(name);
        errno = EINVAL;
        return FALSE;
    }

    if (use_compat)
    {
        switch (cv->codepage)
        {
        case 932: cv->compat = cp932_compat; break;
        case 20932: cv->compat = cp20932_compat; break;
        case 51932: cv->compat = cp51932_compat; break;
        case 50220: case 50221: case 50222: cv->compat = cp5022x_compat; break;
        }
    }

    free(name);

    return TRUE;
}