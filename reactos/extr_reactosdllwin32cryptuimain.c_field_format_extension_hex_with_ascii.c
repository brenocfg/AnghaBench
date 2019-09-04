#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pad ;
typedef  char WCHAR ;
struct TYPE_4__ {int cbData; char* pbData; } ;
struct TYPE_5__ {TYPE_1__ Value; } ;
typedef  int DWORD ;
typedef  TYPE_2__ CERT_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ isprintW (char) ; 
 int /*<<< orphan*/  isspaceW (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char) ; 

__attribute__((used)) static WCHAR *field_format_extension_hex_with_ascii(const CERT_EXTENSION *ext)
{
    WCHAR *str = NULL;

    if (ext->Value.cbData)
    {
        /* The output is formatted as:
         * <hex bytes>  <ascii bytes>\n
         * where <hex bytes> is a string of up to 8 bytes, output as %02x,
         * and <ascii bytes> is the ASCII equivalent of each byte, or '.' if
         * the byte is not printable.
         * So, for example, the extension value consisting of the following
         * bytes:
         *   0x30,0x14,0x31,0x12,0x30,0x10,0x06,0x03,0x55,0x04,0x03,
         *   0x13,0x09,0x4a,0x75,0x61,0x6e,0x20,0x4c,0x61,0x6e,0x67
         * is output as:
         *   30 14 31 12 30 10 06 03  0.1.0...
         *   55 04 03 13 09 4a 75 61  U....Jua
         *   6e 20 4c 61 6e 67        n Lang
         * The allocation size therefore requires:
         * - 4 characters per character in an 8-byte line
         *   (2 for the hex format, one for the space, one for the ASCII value)
         * - 3 more characters per 8-byte line (two spaces and a newline)
         * - 1 character for the terminating nul
         * FIXME: should use a fixed-width font for this
         */
        DWORD lines = (ext->Value.cbData + 7) / 8;

        str = HeapAlloc(GetProcessHeap(), 0,
         (lines * 8 * 4 + lines * 3 + 1) * sizeof(WCHAR));
        if (str)
        {
            static const WCHAR fmt[] = { '%','0','2','x',' ',0 };
            DWORD i, j;
            WCHAR *ptr;

            for (i = 0, ptr = str; i < ext->Value.cbData; i += 8)
            {
                /* Output as hex bytes first */
                for (j = i; j < min(i + 8, ext->Value.cbData); j++, ptr += 3)
                    sprintfW(ptr, fmt, ext->Value.pbData[j]);
                /* Pad the hex output with spaces for alignment */
                if (j == ext->Value.cbData && j % 8)
                {
                    static const WCHAR pad[] = { ' ',' ',' ' };

                    for (; j % 8; j++, ptr += ARRAY_SIZE(pad))
                        memcpy(ptr, pad, sizeof(pad));
                }
                /* The last sprintfW included a space, so just insert one
                 * more space between the hex bytes and the ASCII output
                 */
                *ptr++ = ' ';
                /* Output as ASCII bytes */
                for (j = i; j < min(i + 8, ext->Value.cbData); j++, ptr++)
                {
                    if (isprintW(ext->Value.pbData[j]) &&
                     !isspaceW(ext->Value.pbData[j]))
                        *ptr = ext->Value.pbData[j];
                    else
                        *ptr = '.';
                }
                *ptr++ = '\n';
            }
            *ptr++ = '\0';
        }
    }
    return str;
}