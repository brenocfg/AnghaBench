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
struct TYPE_2__ {int member_0; int member_1; int member_2; char member_3; char member_4; int /*<<< orphan*/  member_5; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF7 ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_utf7_encoding(void)
{
    WCHAR input[16];
    char output[16], expected[16];
    int i, len, expected_len;

    static const BOOL directly_encodable_table[] =
    {
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, /* 0x00 - 0x0F */
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x10 - 0x1F */
        1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, /* 0x20 - 0x2F */
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, /* 0x30 - 0x3F */
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x40 - 0x4F */
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, /* 0x50 - 0x5F */
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /* 0x60 - 0x6F */
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0  /* 0x70 - 0x7F */
    };
    static const char base64_encoding_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    const struct
    {
        /* inputs */
        WCHAR src[16];
        int srclen;
        char *dst;
        int dstlen;
        /* expected outputs */
        char expected_dst[16];
        int chars_written;
        int len;
    }
    tests[] =
    {
        /* tests string conversion with srclen=-1 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, sizeof(output) - 1,
            "+T2BZfVQX-", 11, 11
        },
        /* tests string conversion with srclen=-2 */
        {
            {0x4F60,0x597D,0x5417,0}, -2, output, sizeof(output) - 1,
            "+T2BZfVQX-", 11, 11
        },
        /* tests string conversion with dstlen=strlen(expected_dst) */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, 10,
            "+T2BZfVQX-", 10, 0
        },
        /* tests string conversion with dstlen=strlen(expected_dst)+1 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, 11,
            "+T2BZfVQX-", 11, 11
        },
        /* tests string conversion with dstlen=strlen(expected_dst)+2 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, 12,
            "+T2BZfVQX-", 11, 11
        },
        /* tests dry run with dst=NULL and dstlen=0 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, NULL, 0,
            {0}, 0, 11
        },
        /* tests dry run with dst!=NULL and dstlen=0 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, 0,
            {0}, 0, 11
        },
        /* tests srclen < strlenW(src) with directly encodable chars */
        {
            {'h','e','l','l','o',0}, 2, output, sizeof(output) - 1,
            "he", 2, 2
        },
        /* tests srclen < strlenW(src) with non-directly encodable chars */
        {
            {0x4F60,0x597D,0x5417,0}, 2, output, sizeof(output) - 1,
            "+T2BZfQ-", 8, 8
        },
        /* tests a single null char */
        {
            {0}, -1, output, sizeof(output) - 1,
            "", 1, 1
        },
        /* tests a buffer that runs out while not encoding a UTF-7 sequence */
        {
            {'h','e','l','l','o',0}, -1, output, 2,
            "he", 2, 0
        },
        /* tests a buffer that runs out after writing 1 base64 character */
        {
            {0x4F60,0x0001,0}, -1, output, 2,
            "+T", 2, 0
        },
        /* tests a buffer that runs out after writing 2 base64 characters */
        {
            {0x4F60,0x0001,0}, -1, output, 3,
            "+T2", 3, 0
        },
        /* tests a buffer that runs out after writing 3 base64 characters */
        {
            {0x4F60,0x0001,0}, -1, output, 4,
            "+T2A", 4, 0
        },
        /* tests a buffer that runs out just after writing the + sign */
        {
            {0x4F60,0}, -1, output, 1,
            "+", 1, 0
        },
        /* tests a buffer that runs out just before writing the - sign
         * the number of bits to encode here is evenly divisible by 6 */
        {
            {0x4F60,0x597D,0x5417,0}, -1, output, 9,
            "+T2BZfVQX", 9, 0
        },
        /* tests a buffer that runs out just before writing the - sign
         * the number of bits to encode here is NOT evenly divisible by 6 */
        {
            {0x4F60,0}, -1, output, 4,
            "+T2", 3, 0
        },
        /* tests a buffer that runs out in the middle of escaping a + sign */
        {
            {'+',0}, -1, output, 1,
            "+", 1, 0
        }
    };

    /* test which characters are encoded if surrounded by non-encoded characters */
    for (i = 0; i <= 0xFFFF; i++)
    {
        input[0] = ' ';
        input[1] = i;
        input[2] = ' ';
        input[3] = 0;

        memset(output, '#', sizeof(output) - 1);
        output[sizeof(output) - 1] = 0;

        len = WideCharToMultiByte(CP_UTF7, 0, input, 4, output, sizeof(output) - 1, NULL, NULL);

        if (i == '+')
        {
            /* '+' is a special case and is encoded as "+-" */
            expected_len = 5;
            strcpy(expected, " +- ");
        }
        else if (i <= 0x7F && directly_encodable_table[i])
        {
            /* encodes directly */
            expected_len = 4;
            sprintf(expected, " %c ", i);
        }
        else
        {
            /* base64-encodes */
            expected_len = 8;
            sprintf(expected, " +%c%c%c- ",
                    base64_encoding_table[(i & 0xFC00) >> 10],
                    base64_encoding_table[(i & 0x03F0) >> 4],
                    base64_encoding_table[(i & 0x000F) << 2]);
        }

        ok(len == expected_len, "i=0x%04x: expected len=%i, got len=%i\n", i, expected_len, len);
        ok(memcmp(output, expected, expected_len) == 0,
           "i=0x%04x: expected output='%s', got output='%s'\n", i, expected, output);
        ok(output[expected_len] == '#', "i=0x%04x: expected output[%i]='#', got output[%i]=%i\n",
           i, expected_len, expected_len, output[expected_len]);
    }

    /* test which one-byte characters are absorbed into surrounding base64 blocks
     * (Windows always ends the base64 block when it encounters a directly encodable character) */
    for (i = 0; i <= 0xFFFF; i++)
    {
        input[0] = 0x2672;
        input[1] = i;
        input[2] = 0x2672;
        input[3] = 0;

        memset(output, '#', sizeof(output) - 1);
        output[sizeof(output) - 1] = 0;

        len = WideCharToMultiByte(CP_UTF7, 0, input, 4, output, sizeof(output) - 1, NULL, NULL);

        if (i == '+')
        {
            /* '+' is a special case and is encoded as "+-" */
            expected_len = 13;
            strcpy(expected, "+JnI-+-+JnI-");
        }
        else if (i <= 0x7F && directly_encodable_table[i])
        {
            /* encodes directly */
            expected_len = 12;
            sprintf(expected, "+JnI-%c+JnI-", i);
        }
        else
        {
            /* base64-encodes */
            expected_len = 11;
            sprintf(expected, "+Jn%c%c%c%cZy-",
                    base64_encoding_table[8 | ((i & 0xC000) >> 14)],
                    base64_encoding_table[(i & 0x3F00) >> 8],
                    base64_encoding_table[(i & 0x00FC) >> 2],
                    base64_encoding_table[((i & 0x0003) << 4) | 2]);
        }

        ok(len == expected_len, "i=0x%04x: expected len=%i, got len=%i\n", i, expected_len, len);
        ok(memcmp(output, expected, expected_len) == 0,
           "i=0x%04x: expected output='%s', got output='%s'\n", i, expected, output);
        ok(output[expected_len] == '#', "i=0x%04x: expected output[%i]='#', got output[%i]=%i\n",
           i, expected_len, expected_len, output[expected_len]);
    }

    for (i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        memset(output, '#', sizeof(output) - 1);
        output[sizeof(output) - 1] = 0;
        SetLastError(0xdeadbeef);

        len = WideCharToMultiByte(CP_UTF7, 0, tests[i].src, tests[i].srclen,
                                  tests[i].dst, tests[i].dstlen, NULL, NULL);

        if (!tests[i].len)
        {
            ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
               "tests[%i]: expected error=0x%x, got error=0x%x\n",
               i, ERROR_INSUFFICIENT_BUFFER, GetLastError());
        }
        ok(len == tests[i].len, "tests[%i]: expected len=%i, got len=%i\n", i, tests[i].len, len);

        if (tests[i].dst)
        {
            ok(memcmp(tests[i].dst, tests[i].expected_dst, tests[i].chars_written) == 0,
               "tests[%i]: expected dst='%s', got dst='%s'\n",
               i, tests[i].expected_dst, tests[i].dst);
            ok(tests[i].dst[tests[i].chars_written] == '#',
               "tests[%i]: expected dst[%i]='#', got dst[%i]=%i\n",
               i, tests[i].chars_written, tests[i].chars_written, tests[i].dst[tests[i].chars_written]);
        }
    }
}