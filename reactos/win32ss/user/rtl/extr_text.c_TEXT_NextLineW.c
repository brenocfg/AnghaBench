#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned int before; scalar_t__ under; int after; int len; } ;
typedef  TYPE_1__ ellipsis_data ;
typedef  scalar_t__ WCHAR ;
struct TYPE_13__ {scalar_t__ cy; int cx; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SIZE ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ const ALPHA_PREFIX ; 
 scalar_t__ const CR ; 
 int DT_END_ELLIPSIS ; 
 int DT_EXPANDTABS ; 
 int DT_NOPREFIX ; 
 int DT_PATH_ELLIPSIS ; 
 int DT_SINGLELINE ; 
 int DT_WORDBREAK ; 
 int DT_WORD_ELLIPSIS ; 
 int /*<<< orphan*/  GetTextExtentExPointW (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int,int*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GreGetTextExtentExW (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ const KANA_PREFIX ; 
 scalar_t__ const LF ; 
 scalar_t__ const PREFIX ; 
 scalar_t__ const TAB ; 
 int /*<<< orphan*/  TEXT_Ellipsify (int /*<<< orphan*/ ,scalar_t__*,int,unsigned int*,int,TYPE_2__*,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  TEXT_PathEllipsify (int /*<<< orphan*/ ,scalar_t__*,int,unsigned int*,int,TYPE_2__*,scalar_t__*,TYPE_1__*) ; 
 int TEXT_Reprefix (scalar_t__ const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  TEXT_SkipChars (int*,scalar_t__ const**,int,scalar_t__ const*,int,unsigned int,int) ; 
 int /*<<< orphan*/  TEXT_WordBreak (int /*<<< orphan*/ ,scalar_t__*,int,unsigned int*,int,int,int,unsigned int*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ remainder_is_none_or_newline (int,scalar_t__ const*) ; 

__attribute__((used)) static const WCHAR *TEXT_NextLineW( HDC hdc, const WCHAR *str, int *count,
                                 WCHAR *dest, int *len, int width, DWORD format,
                                 SIZE *retsize, int last_line, WCHAR **p_retstr,
                                 int tabwidth, int *pprefix_offset,
                                 ellipsis_data *pellip)
{
    int i = 0, j = 0;
    int plen = 0;
    SIZE size = {0, 0};
    int maxl = *len;
    int seg_i, seg_count, seg_j;
    int max_seg_width;
    int num_fit;
    int word_broken;
    int line_fits;
    unsigned int j_in_seg;
    int ellipsified;
    *pprefix_offset = -1;

    /* For each text segment in the line */

    retsize->cy = 0;
    while (*count)
    {

        /* Skip any leading tabs */

        if (str[i] == TAB && (format & DT_EXPANDTABS))
        {
            plen = ((plen/tabwidth)+1)*tabwidth;
            (*count)--; if (j < maxl) dest[j++] = str[i++]; else i++;
            while (*count && str[i] == TAB)
            {
                plen += tabwidth;
                (*count)--; if (j < maxl) dest[j++] = str[i++]; else i++;
            }
        }


        /* Now copy as far as the next tab or cr/lf or eos */

        seg_i = i;
        seg_count = *count;
        seg_j = j;

        while (*count &&
               (str[i] != TAB || !(format & DT_EXPANDTABS)) &&
               ((str[i] != CR && str[i] != LF) || (format & DT_SINGLELINE)))
        {
            if ((format & DT_NOPREFIX) || *count <= 1)
            {
                (*count)--; if (j < maxl) dest[j++] = str[i++]; else i++;
                continue;
            }

	    if (str[i] == PREFIX || str[i] == ALPHA_PREFIX) {
                (*count)--, i++; /* Throw away the prefix itself */
                if (str[i] == PREFIX)
                {
                    /* Swallow it before we see it again */
		    (*count)--; if (j < maxl) dest[j++] = str[i++]; else i++;
                }
		else if (*pprefix_offset == -1 || *pprefix_offset >= seg_j)
                {
                    *pprefix_offset = j;
                }
                /* else the previous prefix was in an earlier segment of the
                 * line; we will leave it to the drawing code to catch this
                 * one.
                 */
	    }
	    else if (str[i] == KANA_PREFIX)
            {
                /* Throw away katakana access keys */
                (*count)--, i++; /* skip the prefix */
                (*count)--, i++; /* skip the letter */
            }
            else
            {
                (*count)--; if (j < maxl) dest[j++] = str[i++]; else i++;
            }
        }


        /* Measure the whole text segment and possibly WordBreak and
         * ellipsify it
         */

        j_in_seg = j - seg_j;
        max_seg_width = width - plen;
#ifdef _WIN32K_
        GreGetTextExtentExW (hdc, dest + seg_j, j_in_seg, max_seg_width, (PULONG)&num_fit, NULL, &size, 0);
#else
        GetTextExtentExPointW (hdc, dest + seg_j, j_in_seg, max_seg_width, &num_fit, NULL, &size);
#endif

        /* The Microsoft handling of various combinations of formats is weird.
         * The following may very easily be incorrect if several formats are
         * combined, and may differ between versions (to say nothing of the
         * several bugs in the Microsoft versions).
         */
        word_broken = 0;
        line_fits = (num_fit >= j_in_seg);
        if (!line_fits && (format & DT_WORDBREAK))
        {
            const WCHAR *s;
            unsigned int chars_used;
            TEXT_WordBreak (hdc, dest+seg_j, maxl-seg_j, &j_in_seg,
                            max_seg_width, format, num_fit, &chars_used, &size);
            line_fits = (size.cx <= max_seg_width);
            /* and correct the counts */
            TEXT_SkipChars (count, &s, seg_count, str+seg_i, i-seg_i,
                            chars_used, !(format & DT_NOPREFIX));
            i = s - str;
            word_broken = 1;
        }
        pellip->before = j_in_seg;
        pellip->under = 0;
        pellip->after = 0;
        pellip->len = 0;
        ellipsified = 0;
        if (!line_fits && (format & DT_PATH_ELLIPSIS))
        {
            TEXT_PathEllipsify (hdc, dest + seg_j, maxl-seg_j, &j_in_seg,
                                max_seg_width, &size, *p_retstr, pellip);
            line_fits = (size.cx <= max_seg_width);
            ellipsified = 1;
        }
        /* NB we may end up ellipsifying a word-broken or path_ellipsified
         * string */
        if ((!line_fits && (format & DT_WORD_ELLIPSIS)) ||
            ((format & DT_END_ELLIPSIS) &&
              ((last_line && *count) ||
               (remainder_is_none_or_newline (*count, &str[i]) && !line_fits))))
        {
            int before, len_ellipsis;
            TEXT_Ellipsify (hdc, dest + seg_j, maxl-seg_j, &j_in_seg,
                            max_seg_width, &size, *p_retstr, &before, &len_ellipsis);
            if (before > pellip->before)
            {
                /* We must have done a path ellipsis too */
                pellip->after = before - pellip->before - pellip->len;
                /* Leave the len as the length of the first ellipsis */
            }
            else
            {
                /* If we are here after a path ellipsification it must be
                 * because even the ellipsis itself didn't fit.
                 */
                assert (pellip->under == 0 && pellip->after == 0);
                pellip->before = before;
                pellip->len = len_ellipsis;
                /* pellip->after remains as zero as does
                 * pellip->under
                 */
            }
            line_fits = (size.cx <= max_seg_width);
            ellipsified = 1;
        }
        /* As an optimisation if we have ellipsified and we are expanding
         * tabs and we haven't reached the end of the line we can skip to it
         * now rather than going around the loop again.
         */
        if ((format & DT_EXPANDTABS) && ellipsified)
        {
            if (format & DT_SINGLELINE)
                *count = 0;
            else
            {
                while ((*count) && str[i] != CR && str[i] != LF)
                {
                    (*count)--, i++;
                }
            }
        }

        j = seg_j + j_in_seg;
        if (*pprefix_offset >= seg_j + pellip->before)
        {
            *pprefix_offset = TEXT_Reprefix (str + seg_i, i - seg_i, pellip);
            if (*pprefix_offset != -1)
                *pprefix_offset += seg_j;
        }

        plen += size.cx;
        if (size.cy > retsize->cy)
            retsize->cy = size.cy;

        if (word_broken)
            break;
        else if (!*count)
            break;
        else if (str[i] == CR || str[i] == LF)
        {
            (*count)--, i++;
            if (*count && (str[i] == CR || str[i] == LF) && str[i] != str[i-1])
            {
                (*count)--, i++;
            }
            break;
        }
        /* else it was a Tab and we go around again */
    }

    retsize->cx = plen;
    *len = j;
    if (*count)
        return (&str[i]);
    else
        return NULL;
}