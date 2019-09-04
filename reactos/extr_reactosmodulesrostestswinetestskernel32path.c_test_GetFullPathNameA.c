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
typedef  int /*<<< orphan*/  testset ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  invalid_parameters ;
typedef  int UINT ;
typedef  char* LPSTR ;
typedef  char const* LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INVALID_NAME ; 
 int GetACP () ; 
 int GetFullPathNameA (char const*,int,char*,char**) ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  skip (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_GetFullPathNameA(void)
{
    char output[MAX_PATH], *filepart;
    DWORD ret;
    int i;
    UINT acp;

    const struct
    {
        LPCSTR name;
        DWORD len;
        LPSTR buffer;
        LPSTR *lastpart;
    } invalid_parameters[] =
    {
        {NULL, 0,        NULL,   NULL},
        {NULL, MAX_PATH, NULL,   NULL},
        {NULL, MAX_PATH, output, NULL},
        {NULL, MAX_PATH, output, &filepart},
        {"",   0,        NULL,   NULL},
        {"",   MAX_PATH, NULL,   NULL},
        {"",   MAX_PATH, output, NULL},
        {"",   MAX_PATH, output, &filepart},
    };

    for (i = 0; i < sizeof(invalid_parameters)/sizeof(invalid_parameters[0]); i++)
    {
        SetLastError(0xdeadbeef);
        strcpy(output, "deadbeef");
        filepart = (char *)0xdeadbeef;
        ret = GetFullPathNameA(invalid_parameters[i].name,
                               invalid_parameters[i].len,
                               invalid_parameters[i].buffer,
                               invalid_parameters[i].lastpart);
        ok(!ret, "[%d] Expected GetFullPathNameA to return 0, got %u\n", i, ret);
        ok(!strcmp(output, "deadbeef"), "[%d] Expected the output buffer to be unchanged, got \"%s\"\n", i, output);
        ok(filepart == (char *)0xdeadbeef, "[%d] Expected output file part pointer to be untouched, got %p\n", i, filepart);
        ok(GetLastError() == 0xdeadbeef ||
           GetLastError() == ERROR_INVALID_NAME, /* Win7 */
           "[%d] Expected GetLastError() to return 0xdeadbeef, got %u\n",
           i, GetLastError());
    }

    acp = GetACP();
    if (acp != 932)
        skip("Skipping DBCS(Japanese) GetFullPathNameA test in this codepage (%d)\n", acp);
    else {
        const struct dbcs_case {
            const char *input;
            const char *expected;
        } testset[] = {
            { "c:\\a\\\x95\x5c\x97\xa0.txt", "\x95\x5c\x97\xa0.txt" },
            { "c:\\\x83\x8f\x83\x43\x83\x93\\wine.c", "wine.c" },
            { "c:\\demo\\\x97\xa0\x95\x5c", "\x97\xa0\x95\x5c" }
        };
        for (i = 0; i < sizeof(testset)/sizeof(testset[0]); i++) {
            ret = GetFullPathNameA(testset[i].input, sizeof(output),
                                   output, &filepart);
            ok(ret, "[%d] GetFullPathName error %u\n", i, GetLastError());
            ok(!lstrcmpA(filepart, testset[i].expected),
               "[%d] expected %s got %s\n", i, testset[i].expected, filepart);
        }
    }
}