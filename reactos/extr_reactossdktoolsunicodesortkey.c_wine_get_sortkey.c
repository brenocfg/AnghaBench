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
typedef  int WCHAR ;

/* Variables and functions */
 int C1_PUNCT ; 
 int C1_SPACE ; 
 int NORM_IGNORECASE ; 
 int NORM_IGNORESYMBOLS ; 
 int* collation_table ; 
 int get_char_typeW (int) ; 
 int tolowerW (int) ; 

int wine_get_sortkey(int flags, const WCHAR *src, int srclen, char *dst, int dstlen)
{
    WCHAR dummy[4]; /* no decomposition is larger than 4 chars */
    int key_len[4];
    char *key_ptr[4];
    const WCHAR *src_save = src;
    int srclen_save = srclen;

    key_len[0] = key_len[1] = key_len[2] = key_len[3] = 0;
    for (; srclen; srclen--, src++)
    {
        unsigned int i, decomposed_len = 1;/*wine_decompose(*src, dummy, 4);*/
        dummy[0] = *src;
        if (decomposed_len)
        {
            for (i = 0; i < decomposed_len; i++)
            {
                WCHAR wch = dummy[i];
                unsigned int ce;

                /* tests show that win2k just ignores NORM_IGNORENONSPACE,
                 * and skips white space and punctuation characters for
                 * NORM_IGNORESYMBOLS.
                 */
                if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                    continue;

                if (flags & NORM_IGNORECASE) wch = tolowerW(wch);

                ce = collation_table[collation_table[wch >> 8] + (wch & 0xff)];
                if (ce != (unsigned int)-1)
                {
                    if (ce >> 16) key_len[0] += 2;
                    if ((ce >> 8) & 0xff) key_len[1]++;
                    if ((ce >> 4) & 0x0f) key_len[2]++;
                    if (ce & 1)
                    {
                        if (wch >> 8) key_len[3]++;
                        key_len[3]++;
                    }
                }
                else
                {
                    key_len[0] += 2;
                    if (wch >> 8) key_len[0]++;
                    if (wch & 0xff) key_len[0]++;
		}
            }
        }
    }

    if (!dstlen) /* compute length */
        /* 4 * '\1' + 1 * '\0' + key length */
        return key_len[0] + key_len[1] + key_len[2] + key_len[3] + 4 + 1;

    if (dstlen < key_len[0] + key_len[1] + key_len[2] + key_len[3] + 4 + 1)
        return 0; /* overflow */

    src = src_save;
    srclen = srclen_save;

    key_ptr[0] = dst;
    key_ptr[1] = key_ptr[0] + key_len[0] + 1;
    key_ptr[2] = key_ptr[1] + key_len[1] + 1;
    key_ptr[3] = key_ptr[2] + key_len[2] + 1;

    for (; srclen; srclen--, src++)
    {
        unsigned int i, decomposed_len = 1;/*wine_decompose(*src, dummy, 4);*/
        dummy[0] = *src;
        if (decomposed_len)
        {
            for (i = 0; i < decomposed_len; i++)
            {
                WCHAR wch = dummy[i];
                unsigned int ce;

                /* tests show that win2k just ignores NORM_IGNORENONSPACE,
                 * and skips white space and punctuation characters for
                 * NORM_IGNORESYMBOLS.
                 */
                if ((flags & NORM_IGNORESYMBOLS) && (get_char_typeW(wch) & (C1_PUNCT | C1_SPACE)))
                    continue;

                if (flags & NORM_IGNORECASE) wch = tolowerW(wch);

                ce = collation_table[collation_table[wch >> 8] + (wch & 0xff)];
                if (ce != (unsigned int)-1)
                {
                    WCHAR key;
                    if ((key = ce >> 16))
                    {
                        *key_ptr[0]++ = key >> 8;
                        *key_ptr[0]++ = key & 0xff;
                    }
                    /* make key 1 start from 2 */
                    if ((key = (ce >> 8) & 0xff)) *key_ptr[1]++ = key + 1;
                    /* make key 2 start from 2 */
                    if ((key = (ce >> 4) & 0x0f)) *key_ptr[2]++ = key + 1;
                    /* key 3 is always a character code */
                    if (ce & 1)
                    {
                        if (wch >> 8) *key_ptr[3]++ = wch >> 8;
                        if (wch & 0xff) *key_ptr[3]++ = wch & 0xff;
                    }
                }
                else
                {
                    *key_ptr[0]++ = 0xff;
                    *key_ptr[0]++ = 0xfe;
                    if (wch >> 8) *key_ptr[0]++ = wch >> 8;
                    if (wch & 0xff) *key_ptr[0]++ = wch & 0xff;
                }
            }
        }
    }

    *key_ptr[0] = '\1';
    *key_ptr[1] = '\1';
    *key_ptr[2] = '\1';
    *key_ptr[3]++ = '\1';
    *key_ptr[3] = 0;

    return key_ptr[3] - dst;
}