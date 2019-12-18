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
typedef  int /*<<< orphan*/  encbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 char* FromCharset (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 char* strndup (char const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static char *vlc_from_EIT (const void *buf, size_t length)
{
    if (unlikely(length == 0))
        return NULL;

    char encbuf[12];
    const char *encoding = encbuf;

    const char *in = buf;
    size_t offset = 1;
    unsigned char c = *in;

    if (c >= 0x20)
    {
        offset = 0;
        encoding = "ISO_6937";
    }
    else if ((1 << c) & 0x0EFE) /* 1-7, 9-11 -> ISO 8859-(c+4) */
    {
        snprintf (encbuf, sizeof (encbuf), "ISO_8859-%u", 4u + c);
    }
    else switch (c)
    {
        case 0x10: /* two more bytes */
            offset = 3;
            if (length < 3 || in[1] != 0x00)
                return NULL;

            c = in[2];
            if ((1 << c) & 0xEFFE) /* 1-11, 13-15 -> ISO 8859-(c) */
               snprintf (encbuf, sizeof (encbuf), "ISO_8859-%hhu", c);
           else
               return NULL;
           break;
        case 0x11: /* the BMP */
        case 0x14: /* Big5 subset of the BMP */
            encoding = "UCS-2BE";
            break;
        case 0x12:
            /* DVB has no clue about Korean. KS X 1001 (a.k.a. KS C 5601) is a
             * character set, not a character encoding... So we assume EUC-KR.
             * It is an encoding of KS X 1001. In practice, I guess nobody uses
             * this in any real DVB system. */
            encoding = "EUC-KR";
            break;
        case 0x13: /* GB-2312-1980 */
            encoding = "GB2312";
            break;
        case 0x15:
            encoding = "UTF-8";
            break;
#if 0
        case 0x1F: /* operator-specific(?) */
            offset = 2;
#endif
        default:
            return NULL;
    }

    in += offset;
    length -= offset;

    char *out = FromCharset (encoding, in, length);
    if (out == NULL)
    {   /* Fallback... */
        out = strndup (in, length);
        if (unlikely(out == NULL))
            return NULL;
        EnsureUTF8 (out);
    }

    length = strlen(out);
    /* Convert control codes */
    for (char *p = strchr (out, '\xC2'); p; p = strchr (p + 1, '\xC2'))
    {
        /* We have valid UTF-8, to 0xC2 is followed by a continuation byte. */
        /* 0x80-0x85,0x88-0x89 are reserved.
         * 0x86-0x87 are identical to Unicode and Latin-1.
         * 0x8A is CR/LF.
         * 0x8B-0x9F are unspecified. */
        if (p[1] == '\x8A')
            memcpy (p, "\r\n", 2);

        /* Strip character emphasis */
        if (p[1] == '\x86' || p[1] == '\x87') {
            const size_t n = p - out;
            memmove (p, p+2, length - n);
            length -= 2;
            out[length] = '\0';
            if (length == n)
                break;
        }
    }

    /* Private use area */
    for (char *p = strchr (out, '\xEE'); p; p = strchr (p + 1, '\xEE'))
    {
        /* Within UTF-8, 0xEE is followed by a two continuation bytes. */
        if (p[1] != '\x82')
            continue;
        if (p[2] == '\x8A')
            memcpy (p, "\r\r\n", 3); /* we need three bytes, so to CRs ;) */

        /* Strip character emphasis */
        if (p[2] == '\x86' || p[2] == '\x87') {
            const size_t n = p - out;
            memmove (p, p+3, length - n);
            length -= 3;
            out[length] = '\0';
            if (length == n)
                break;
        }
    }

    return out;
}