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
typedef  int /*<<< orphan*/  bufferA ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {char* url; int len; int /*<<< orphan*/  newurl; } ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ParseURL_table ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 
 int pParseURLFromOutsideSourceW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_ParseURLFromOutsideSourceW(void)
{
    WCHAR urlW[INTERNET_MAX_URL_LENGTH];
    WCHAR bufferW[INTERNET_MAX_URL_LENGTH];
    CHAR  bufferA[INTERNET_MAX_URL_LENGTH];
    DWORD maxlen;
    DWORD dummy;
    DWORD len;
    DWORD res;

    if (!pParseURLFromOutsideSourceW) {
        skip("ParseURLFromOutsideSourceW not found\n");
        return;
    }
    MultiByteToWideChar(CP_ACP, 0, ParseURL_table[0].url, -1, urlW, INTERNET_MAX_URL_LENGTH);

    memset(bufferA, '#', sizeof(bufferA)-1);
    bufferA[sizeof(bufferA) - 1] = '\0';
    MultiByteToWideChar(CP_ACP, 0, bufferA, -1, bufferW, INTERNET_MAX_URL_LENGTH);

    /* len is in characters */
    len = ARRAY_SIZE(bufferW);
    dummy = 0;
    /* on success, 1 is returned for unicode version */
    res = pParseURLFromOutsideSourceW(urlW, bufferW, &len, &dummy);
    WideCharToMultiByte(CP_ACP, 0, bufferW, -1, bufferA, sizeof(bufferA), NULL, NULL);
    ok( res == 1 && len == ParseURL_table[0].len &&
        !lstrcmpA(bufferA, ParseURL_table[0].newurl),
        "got %d and %d with '%s' (expected 1 and %d with '%s')\n",
        res, len, bufferA, ParseURL_table[0].len, ParseURL_table[0].newurl);


    maxlen = len;

    memset(bufferA, '#', sizeof(bufferA)-1);
    bufferA[sizeof(bufferA) - 1] = '\0';
    MultiByteToWideChar(CP_ACP, 0, bufferA, -1, bufferW, INTERNET_MAX_URL_LENGTH);
    len = maxlen+1;
    dummy = 0;
    res = pParseURLFromOutsideSourceW(urlW, bufferW, &len, &dummy);
    WideCharToMultiByte(CP_ACP, 0, bufferW, -1, bufferA, sizeof(bufferA), NULL, NULL);
    /* len does not include the terminating 0, when buffer is large enough */
    ok( res != 0 && len == ParseURL_table[0].len &&
        !lstrcmpA(bufferA, ParseURL_table[0].newurl),
        "+1: got %d and %d with '%s' (expected '!=0' and %d with '%s')\n",
        res, len, bufferA, ParseURL_table[0].len, ParseURL_table[0].newurl);

    len = maxlen;
    dummy = 0;
    res = pParseURLFromOutsideSourceW(urlW, bufferW, &len, &dummy);
    /* len includes the terminating 0, when the buffer is too small */
    ok( res == 0 && len == ParseURL_table[0].len + 1,
        "==: got %d and %d (expected '0' and %d)\n",
        res, len, ParseURL_table[0].len + 1);

    len = maxlen - 1;
    dummy = 0;
    res = pParseURLFromOutsideSourceW(urlW, bufferW, &len, &dummy);
    /* len includes the terminating 0 on XP SP1 and before, when the buffer is too small */
    ok( res == 0 && (len == ParseURL_table[0].len || len == ParseURL_table[0].len + 1),
        "-1: got %d and %d (expected '0' and %d or %d)\n",
        res, len, ParseURL_table[0].len, ParseURL_table[0].len + 1);

}