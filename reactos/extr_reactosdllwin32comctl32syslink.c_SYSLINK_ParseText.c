#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_10__ {int /*<<< orphan*/ * szUrl; int /*<<< orphan*/ * szID; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {TYPE_1__ Link; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct TYPE_12__ {char BreakChar; int Style; } ;
typedef  TYPE_3__ SYSLINK_INFO ;
typedef  scalar_t__ SL_ITEM_TYPE ;
typedef  TYPE_4__* PDOC_ITEM ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 void* Alloc (int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LIS_ENABLED ; 
 scalar_t__ L_MAX_URL_LENGTH ; 
 scalar_t__ MAX_LINKID_TEXT ; 
 TYPE_4__* SYSLINK_AppendDocItem (TYPE_3__*,char*,int,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int WS_DISABLED ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,char*,int) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ slLink ; 
 scalar_t__ slText ; 
 scalar_t__ strlenW (char*) ; 
 int /*<<< orphan*/  strncmpiW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT SYSLINK_ParseText (SYSLINK_INFO *infoPtr, LPCWSTR Text)
{
    static const WCHAR SL_LINKOPEN[] =  { '<','a' };
    static const WCHAR SL_HREF[] =      { 'h','r','e','f','=','\"' };
    static const WCHAR SL_ID[] =        { 'i','d','=','\"' };
    static const WCHAR SL_LINKCLOSE[] = { '<','/','a','>' };
    LPCWSTR current, textstart = NULL, linktext = NULL, firsttag = NULL;
    int taglen = 0, textlen = 0, linklen = 0, docitems = 0;
    PDOC_ITEM Last = NULL;
    SL_ITEM_TYPE CurrentType = slText;
    LPCWSTR lpID, lpUrl;
    UINT lenId, lenUrl;

    TRACE("(%p %s)\n", infoPtr, debugstr_w(Text));

    for(current = Text; *current != 0;)
    {
        if(*current == '<')
        {
            if(!strncmpiW(current, SL_LINKOPEN, ARRAY_SIZE(SL_LINKOPEN)) && (CurrentType == slText))
            {
                BOOL ValidParam = FALSE, ValidLink = FALSE;

                if(*(current + 2) == '>')
                {
                    /* we just have to deal with a <a> tag */
                    taglen = 3;
                    ValidLink = TRUE;
                    ValidParam = TRUE;
                    firsttag = current;
                    linklen = 0;
                    lpID = NULL;
                    lpUrl = NULL;
                }
                else if(*(current + 2) == infoPtr->BreakChar)
                {
                    /* we expect parameters, parse them */
                    LPCWSTR *CurrentParameter = NULL, tmp;
                    UINT *CurrentParameterLen = NULL;

                    taglen = 3;
                    tmp = current + taglen;
                    lpID = NULL;
                    lpUrl = NULL;
                    
CheckParameter:
                    /* compare the current position with all known parameters */
                    if(!strncmpiW(tmp, SL_HREF, ARRAY_SIZE(SL_HREF)))
                    {
                        taglen += 6;
                        ValidParam = TRUE;
                        CurrentParameter = &lpUrl;
                        CurrentParameterLen = &lenUrl;
                    }
                    else if(!strncmpiW(tmp, SL_ID, ARRAY_SIZE(SL_ID)))
                    {
                        taglen += 4;
                        ValidParam = TRUE;
                        CurrentParameter = &lpID;
                        CurrentParameterLen = &lenId;
                    }
                    else
                    {
                        ValidParam = FALSE;
                    }
                    
                    if(ValidParam)
                    {
                        /* we got a known parameter, now search until the next " character.
                           If we can't find a " character, there's a syntax error and we just assume it's text */
                        ValidParam = FALSE;
                        *CurrentParameter = current + taglen;
                        *CurrentParameterLen = 0;

                        for(tmp = *CurrentParameter; *tmp != 0; tmp++)
                        {
                            taglen++;
                            if(*tmp == '\"')
                            {
                                ValidParam = TRUE;
                                tmp++;
                                break;
                            }
                            (*CurrentParameterLen)++;
                        }
                    }
                    if(ValidParam)
                    {
                        /* we're done with this parameter, now there are only 2 possibilities:
                         * 1. another parameter is coming, so expect a ' ' (space) character
                         * 2. the tag is being closed, so expect a '<' character
                         */
                        if(*tmp == infoPtr->BreakChar)
                        {
                            /* we expect another parameter, do the whole thing again */
                            taglen++;
                            tmp++;
                            goto CheckParameter;
                        }
                        else if(*tmp == '>')
                        {
                            /* the tag is being closed, we're done */
                            ValidLink = TRUE;
                            taglen++;
                        }
                    }
                }
                
                if(ValidLink && ValidParam)
                {
                    /* the <a ...> tag appears to be valid. save all information
                       so we can add the link if we find a valid </a> tag later */
                    CurrentType = slLink;
                    linktext = current + taglen;
                    linklen = 0;
                    firsttag = current;
                }
                else
                {
                    taglen = 1;
                    lpID = NULL;
                    lpUrl = NULL;
                    if(textstart == NULL)
                    {
                        textstart = current;
                    }
                }
            }
            else if(!strncmpiW(current, SL_LINKCLOSE, ARRAY_SIZE(SL_LINKCLOSE)) && (CurrentType == slLink) && firsttag)
            {
                /* there's a <a...> tag opened, first add the previous text, if present */
                if(textstart != NULL && textlen > 0 && firsttag > textstart)
                {
                    Last = SYSLINK_AppendDocItem(infoPtr, textstart, firsttag - textstart, slText, Last);
                    if(Last == NULL)
                    {
                        ERR("Unable to create new document item!\n");
                        return docitems;
                    }
                    docitems++;
                    textstart = NULL;
                    textlen = 0;
                }
                
                /* now it's time to add the link to the document */
                current += 4;
                if(linktext != NULL && linklen > 0)
                {
                    Last = SYSLINK_AppendDocItem(infoPtr, linktext, linklen, slLink, Last);
                    if(Last == NULL)
                    {
                        ERR("Unable to create new document item!\n");
                        return docitems;
                    }
                    docitems++;
                    if(CurrentType == slLink)
                    {
                        int nc;

                        if(!(infoPtr->Style & WS_DISABLED))
                        {
                            Last->u.Link.state |= LIS_ENABLED;
                        }
                        /* Copy the tag parameters */
                        if(lpID != NULL)
                        {
                            nc = min(lenId, strlenW(lpID));
                            nc = min(nc, MAX_LINKID_TEXT - 1);
                            Last->u.Link.szID = Alloc((nc + 1) * sizeof(WCHAR));
                            if(Last->u.Link.szID != NULL)
                            {
                                lstrcpynW(Last->u.Link.szID, lpID, nc + 1);
                            }
                        }
                        else
                            Last->u.Link.szID = NULL;
                        if(lpUrl != NULL)
                        {
                            nc = min(lenUrl, strlenW(lpUrl));
                            nc = min(nc, L_MAX_URL_LENGTH - 1);
                            Last->u.Link.szUrl = Alloc((nc + 1) * sizeof(WCHAR));
                            if(Last->u.Link.szUrl != NULL)
                            {
                                lstrcpynW(Last->u.Link.szUrl, lpUrl, nc + 1);
                            }
                        }
                        else
                            Last->u.Link.szUrl = NULL;
                    }
                    linktext = NULL;
                }
                CurrentType = slText;
                firsttag = NULL;
                textstart = NULL;
                continue;
            }
            else
            {
                /* we don't know what tag it is, so just continue */
                taglen = 1;
                linklen++;
                if(CurrentType == slText && textstart == NULL)
                {
                    textstart = current;
                }
            }
            
            textlen += taglen;
            current += taglen;
        }
        else
        {
            textlen++;
            linklen++;

            /* save the pointer of the current text item if we couldn't find a tag */
            if(textstart == NULL && CurrentType == slText)
            {
                textstart = current;
            }
            
            current++;
        }
    }
    
    if(textstart != NULL && textlen > 0)
    {
        Last = SYSLINK_AppendDocItem(infoPtr, textstart, textlen, CurrentType, Last);
        if(Last == NULL)
        {
            ERR("Unable to create new document item!\n");
            return docitems;
        }
        if(CurrentType == slLink)
        {
            int nc;

            if(!(infoPtr->Style & WS_DISABLED))
            {
                Last->u.Link.state |= LIS_ENABLED;
            }
            /* Copy the tag parameters */
            if(lpID != NULL)
            {
                nc = min(lenId, strlenW(lpID));
                nc = min(nc, MAX_LINKID_TEXT - 1);
                Last->u.Link.szID = Alloc((nc + 1) * sizeof(WCHAR));
                if(Last->u.Link.szID != NULL)
                {
                    lstrcpynW(Last->u.Link.szID, lpID, nc + 1);
                }
            }
            else
                Last->u.Link.szID = NULL;
            if(lpUrl != NULL)
            {
                nc = min(lenUrl, strlenW(lpUrl));
                nc = min(nc, L_MAX_URL_LENGTH - 1);
                Last->u.Link.szUrl = Alloc((nc + 1) * sizeof(WCHAR));
                if(Last->u.Link.szUrl != NULL)
                {
                    lstrcpynW(Last->u.Link.szUrl, lpUrl, nc + 1);
                }
            }
            else
                Last->u.Link.szUrl = NULL;
        }
        docitems++;
    }

    if(linktext != NULL && linklen > 0)
    {
        /* we got an unclosed link, just display the text */
        Last = SYSLINK_AppendDocItem(infoPtr, linktext, linklen, slText, Last);
        if(Last == NULL)
        {
            ERR("Unable to create new document item!\n");
            return docitems;
        }
        docitems++;
    }

    return docitems;
}