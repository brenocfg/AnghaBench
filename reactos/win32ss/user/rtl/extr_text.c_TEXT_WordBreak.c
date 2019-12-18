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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  SIZE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int DT_CENTER ; 
 int DT_EDITCONTROL ; 
 int DT_PATH_ELLIPSIS ; 
 int DT_RIGHT ; 
 int DT_WORDBREAK ; 
 int DT_WORD_ELLIPSIS ; 
 int FALSE ; 
 int /*<<< orphan*/  GetTextExtentExPointW (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GreGetTextExtentExW (int /*<<< orphan*/ ,scalar_t__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsCJKT (scalar_t__) ; 
 int /*<<< orphan*/  KinsokuClassA ; 
 scalar_t__ SPACE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void TEXT_WordBreak (HDC hdc, WCHAR *str, unsigned int max_str,
                            unsigned int *len_str,
                            int width, int format, unsigned int chars_fit,
                            unsigned int *chars_used, SIZE *size)
{
    WCHAR *p;
    int word_fits;
    assert (format & DT_WORDBREAK);
    assert (chars_fit < *len_str);

    /* Work back from the last character that did fit to either a space or the
     * last character of a word, whichever is met first.
     */
    p = str + chars_fit; /* The character that doesn't fit */
    word_fits = TRUE;
    if (!chars_fit)
        word_fits = FALSE;
    else if (*p == SPACE) /* chars_fit < *len_str so this is valid */
        p--; /* the word just fitted */
    else
    {
        while (p > str && *(--p) != SPACE && (!IsCJKT(p[1]) || 
                p[1] == L'\0' || wcschr(KinsokuClassA, p[1]) != NULL))
            ;
        word_fits = (p != str || *p == SPACE || IsCJKT(p[1]));
    }
    /* If there was one. */
    if (word_fits)
    {
        int next_is_space;
        /* break the line before/after that character */
        if (!(format & (DT_RIGHT | DT_CENTER)) || *p != SPACE)
            p++;
        next_is_space = (unsigned int) (p - str) < *len_str && *p == SPACE;
        *len_str = p - str;
        /* and if the next character is a space then discard it. */
        *chars_used = *len_str;
        if (next_is_space)
            (*chars_used)++;
    }
    /* Suppose there was none. */
    else
    {
        if ((format & (DT_EDITCONTROL | DT_WORD_ELLIPSIS | DT_PATH_ELLIPSIS)) ==
            DT_EDITCONTROL)
        {
            /* break the word after the last character that fits (there must be
             * at least one). */
            if (!chars_fit)
                ++chars_fit;
            *len_str = chars_fit;
            *chars_used = chars_fit;

            /* FIXME - possible error.  Since the next character is now removed
             * this could make the text longer so that it no longer fits, and
             * so we need a loop to test and shrink.
             */
        }
        /* Otherwise */
        else
        {
            /* discard any trailing space. */
            const WCHAR *e = str + *len_str;
            p = str + chars_fit;
            while (p < e && *p != SPACE)
                p++;
            *chars_used = p - str;
            if (p < e) /* i.e. loop failed because *p == SPACE */
                (*chars_used)++;

            /* include the whole word; it may be ellipsified later */
            *len_str = p - str;
            /* Possible optimisation; if DT_WORD_ELLIPSIS only use chars_fit+1
             * so that it will be too long
             */
        }
    }
    /* Remeasure the string */
#ifdef _WIN32K_
    GreGetTextExtentExW (hdc, str, *len_str, 0, NULL, NULL, size, 0);
#else
    GetTextExtentExPointW (hdc, str, *len_str, 0, NULL, NULL, size);
#endif
}