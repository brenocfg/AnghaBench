#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  output ;
typedef  char WCHAR ;
struct TYPE_2__ {int member_0; int member_1; char member_2; char member_3; char member_4; char member_5; char member_6; char member_7; int /*<<< orphan*/  member_8; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF7 ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int GetLastError () ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int wine_dbgstr_wn (char*,int) ; 

__attribute__((used)) static void test_utf7_decoding(void)
{
    char input[32];
    WCHAR output[32], expected[32];
    int i, len, expected_len;

    static const signed char base64_decoding_table[] =
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /* 0x00-0x0F */
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /* 0x10-0x1F */
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, /* 0x20-0x2F */
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, /* 0x30-0x3F */
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, /* 0x40-0x4F */
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, /* 0x50-0x5F */
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, /* 0x60-0x6F */
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1  /* 0x70-0x7F */
    };

    struct
    {
        /* inputs */
        char src[32];
        int srclen;
        WCHAR *dst;
        int dstlen;
        /* expected outputs */
        WCHAR expected_dst[32];
        int chars_written;
        int len;
    }
    tests[] =
    {
        /* tests string conversion with srclen=-1 */
        {
            "+T2BZfQ-", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60,0x597D,0}, 3, 3
        },
        /* tests string conversion with srclen=-2 */
        {
            "+T2BZfQ-", -2, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60,0x597D,0}, 3, 3
        },
        /* tests string conversion with dstlen=strlen(expected_dst) */
        {
            "+T2BZfQ-", -1, output, 2,
            {0x4F60,0x597D}, 2, 0
        },
        /* tests string conversion with dstlen=strlen(expected_dst)+1 */
        {
            "+T2BZfQ-", -1, output, 3,
            {0x4F60,0x597D,0}, 3, 3
        },
        /* tests string conversion with dstlen=strlen(expected_dst)+2 */
        {
            "+T2BZfQ-", -1, output, 4,
            {0x4F60,0x597D,0}, 3, 3
        },
        /* tests dry run with dst=NULL and dstlen=0 */
        {
            "+T2BZfQ-", -1, NULL, 0,
            {0}, 0, 3
        },
        /* tests dry run with dst!=NULL and dstlen=0 */
        {
            "+T2BZfQ-", -1, output, 0,
            {0}, 0, 3
        },
        /* tests ill-formed UTF-7: 6 bits, not enough for a byte pair */
        {
            "+T-+T-+T-hello", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'h','e','l','l','o',0}, 6, 6
        },
        /* tests ill-formed UTF-7: 12 bits, not enough for a byte pair */
        {
            "+T2-+T2-+T2-hello", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'h','e','l','l','o',0}, 6, 6
        },
        /* tests ill-formed UTF-7: 18 bits, not a multiple of 16 and the last bit is a 1 */
        {
            "+T2B-+T2B-+T2B-hello", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60,0x4F60,0x4F60,'h','e','l','l','o',0}, 9, 9
        },
        /* tests ill-formed UTF-7: 24 bits, a multiple of 8 but not a multiple of 16 */
        {
            "+T2BZ-+T2BZ-+T2BZ-hello", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60,0x4F60,0x4F60,'h','e','l','l','o',0}, 9, 9
        },
        /* tests UTF-7 followed by characters that should be encoded but aren't */
        {
            "+T2BZ-\x82\xFE", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60,0x0082,0x00FE,0}, 4, 4
        },
        /* tests srclen > strlen(src) */
        {
            "a\0b", 4, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'a',0,'b',0}, 4, 4
        },
        /* tests srclen < strlen(src) outside of a UTF-7 sequence */
        {
            "hello", 2, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'h','e'}, 2, 2
        },
        /* tests srclen < strlen(src) inside of a UTF-7 sequence */
        {
            "+T2BZfQ-", 4, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60}, 1, 1
        },
        /* tests srclen < strlen(src) right at the beginning of a UTF-7 sequence */
        {
            "hi+T2A-", 3, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'h','i'}, 2, 2
        },
        /* tests srclen < strlen(src) right at the end of a UTF-7 sequence */
        {
            "+T2A-hi", 5, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0x4F60}, 1, 1
        },
        /* tests srclen < strlen(src) at the beginning of an escaped + sign */
        {
            "hi+-", 3, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'h','i'}, 2, 2
        },
        /* tests srclen < strlen(src) at the end of an escaped + sign */
        {
            "+-hi", 2, output, sizeof(output) / sizeof(WCHAR) - 1,
            {'+'}, 1, 1
        },
        /* tests len=0 but no error */
        {
            "+", 1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0}, 0, 0
        },
        /* tests a single null char */
        {
            "", -1, output, sizeof(output) / sizeof(WCHAR) - 1,
            {0}, 1, 1
        },
        /* tests a buffer that runs out while not decoding a UTF-7 sequence */
        {
            "hello", -1, output, 2,
            {'h','e'}, 2, 0
        },
        /* tests a buffer that runs out in the middle of decoding a UTF-7 sequence */
        {
            "+T2BZfQ-", -1, output, 1,
            {0x4F60}, 1, 0
        }
    };

    /* test which one-byte characters remove stray + signs */
    for (i = 0; i < 256; i++)
    {
        sprintf(input, "+%c+AAA", i);

        memset(output, 0x23, sizeof(output) - sizeof(WCHAR));
        output[sizeof(output) / sizeof(WCHAR) - 1] = 0;

        len = MultiByteToWideChar(CP_UTF7, 0, input, 7, output, sizeof(output) / sizeof(WCHAR) - 1);

        if (i == '-')
        {
            /* removes the - sign */
            expected_len = 3;
            expected[0] = 0x002B;
            expected[1] = 0;
            expected[2] = 0;
        }
        else if (i <= 0x7F && base64_decoding_table[i] != -1)
        {
            /* absorbs the character into the base64 sequence */
            expected_len = 2;
            expected[0] = (base64_decoding_table[i] << 10) | 0x03E0;
            expected[1] = 0;
        }
        else
        {
            /* removes the + sign */
            expected_len = 3;
            expected[0] = i;
            expected[1] = 0;
            expected[2] = 0;
        }
        expected[expected_len] = 0x2323;

        ok(len == expected_len, "i=0x%02x: expected len=%i, got len=%i\n", i, expected_len, len);
        ok(memcmp(output, expected, (expected_len + 1) * sizeof(WCHAR)) == 0,
           "i=0x%02x: expected output=%s, got output=%s\n",
           i, wine_dbgstr_wn(expected, expected_len + 1), wine_dbgstr_wn(output, expected_len + 1));
    }

    /* test which one-byte characters terminate a sequence
     * also test whether the unfinished byte pair is discarded or not */
    for (i = 0; i < 256; i++)
    {
        sprintf(input, "+B%c+AAA", i);

        memset(output, 0x23, sizeof(output) - sizeof(WCHAR));
        output[sizeof(output) / sizeof(WCHAR) - 1] = 0;

        len = MultiByteToWideChar(CP_UTF7, 0, input, 8, output, sizeof(output) / sizeof(WCHAR) - 1);

        if (i == '-')
        {
            /* explicitly terminates */
            expected_len = 2;
            expected[0] = 0;
            expected[1] = 0;
        }
        else if (i <= 0x7F)
        {
            if (base64_decoding_table[i] != -1)
            {
                /* absorbs the character into the base64 sequence */
                expected_len = 3;
                expected[0] = 0x0400 | (base64_decoding_table[i] << 4) | 0x000F;
                expected[1] = 0x8000;
                expected[2] = 0;
            }
            else
            {
                /* implicitly terminates and discards the unfinished byte pair */
                expected_len = 3;
                expected[0] = i;
                expected[1] = 0;
                expected[2] = 0;
            }
        }
        else
        {
            /* implicitly terminates but does not the discard unfinished byte pair */
            expected_len = 3;
            expected[0] = i;
            expected[1] = 0x0400;
            expected[2] = 0;
        }
        expected[expected_len] = 0x2323;

        ok(len == expected_len, "i=0x%02x: expected len=%i, got len=%i\n", i, expected_len, len);
        ok(memcmp(output, expected, (expected_len + 1) * sizeof(WCHAR)) == 0,
           "i=0x%02x: expected output=%s, got output=%s\n",
           i, wine_dbgstr_wn(expected, expected_len + 1), wine_dbgstr_wn(output, expected_len + 1));
    }

    for (i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        memset(output, 0x23, sizeof(output) - sizeof(WCHAR));
        output[sizeof(output) / sizeof(WCHAR) - 1] = 0;
        SetLastError(0xdeadbeef);

        len = MultiByteToWideChar(CP_UTF7, 0, tests[i].src, tests[i].srclen,
                                  tests[i].dst, tests[i].dstlen);

        tests[i].expected_dst[tests[i].chars_written] = 0x2323;

        if (!tests[i].len && tests[i].chars_written)
        {
            ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
               "tests[%i]: expected error=0x%x, got error=0x%x\n",
               i, ERROR_INSUFFICIENT_BUFFER, GetLastError());
        }
        ok(len == tests[i].len, "tests[%i]: expected len=%i, got len=%i\n", i, tests[i].len, len);

        if (tests[i].dst)
        {
            ok(memcmp(tests[i].dst, tests[i].expected_dst, (tests[i].chars_written + 1) * sizeof(WCHAR)) == 0,
               "tests[%i]: expected dst=%s, got dst=%s\n",
               i, wine_dbgstr_wn(tests[i].expected_dst, tests[i].chars_written + 1),
               wine_dbgstr_wn(tests[i].dst, tests[i].chars_written + 1));
        }
    }
}