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
typedef  int /*<<< orphan*/  buffer ;
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 char* ERROR_INSUFFICIENT_BUFFER ; 
 char* ERROR_INTERNET_INVALID_OPTION ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* GetLastError () ; 
 int ICU_BROWSER_MODE ; 
 int ICU_DECODE ; 
 int ICU_NO_ENCODE ; 
 int InternetCanonicalizeUrlA (char*,char*,int*,int) ; 
 int InternetSetOptionA (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ lstrcmpA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_InternetCanonicalizeUrlA(void)
{
    CHAR    buffer[256];
    LPCSTR  url;
    DWORD   urllen;
    DWORD   dwSize;
    DWORD   res;

    /* Acrobat Updater 5 calls this for Adobe Reader 8.1 */
    url = "http://swupmf.adobe.com/manifest/50/win/AdobeUpdater.upd";
    urllen = lstrlenA(url);

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    dwSize = 1; /* Acrobat Updater use this size */
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, buffer, &dwSize, 0);
    ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER) && (dwSize == (urllen+1)),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));


    /* buffer has no space for the terminating '\0' */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    dwSize = urllen;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, buffer, &dwSize, 0);
    /* dwSize is nr. of needed bytes with the terminating '\0' */
    ok( !res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER) && (dwSize == (urllen+1)),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));

    /* buffer has the required size */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    dwSize = urllen+1;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, buffer, &dwSize, 0);
    /* dwSize is nr. of copied bytes without the terminating '\0' */
    ok( res && (dwSize == urllen) && (lstrcmpA(url, buffer) == 0),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    dwSize = sizeof(buffer);
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA("file:///C:/Program%20Files/Atmel/AVR%20Tools/STK500/STK500.xml", buffer, &dwSize, ICU_DECODE | ICU_NO_ENCODE);
    ok(res, "InternetCanonicalizeUrlA failed %u\n", GetLastError());
    ok(dwSize == lstrlenA(buffer), "got %d expected %d\n", dwSize, lstrlenA(buffer));
    ok(!lstrcmpA("file://C:\\Program Files\\Atmel\\AVR Tools\\STK500\\STK500.xml", buffer),
       "got %s expected 'file://C:\\Program Files\\Atmel\\AVR Tools\\STK500\\STK500.xml'\n", buffer);

    /* buffer is larger as the required size */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    dwSize = urllen+2;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, buffer, &dwSize, 0);
    /* dwSize is nr. of copied bytes without the terminating '\0' */
    ok( res && (dwSize == urllen) && (lstrcmpA(url, buffer) == 0),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));


    /* check NULL pointers */
    memset(buffer, '#', urllen + 4);
    buffer[urllen + 4] = '\0';
    dwSize = urllen+1;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(NULL, buffer, &dwSize, 0);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));

    memset(buffer, '#', urllen + 4);
    buffer[urllen + 4] = '\0';
    dwSize = urllen+1;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, NULL, &dwSize, 0);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));

    memset(buffer, '#', urllen + 4);
    buffer[urllen + 4] = '\0';
    dwSize = urllen+1;
    SetLastError(0xdeadbeef);
    res = InternetCanonicalizeUrlA(url, buffer, NULL, 0);
    ok( !res && (GetLastError() == ERROR_INVALID_PARAMETER),
        "got %u and %u with size %u for '%s' (%d)\n",
        res, GetLastError(), dwSize, buffer, lstrlenA(buffer));

    /* test with trailing space */
    dwSize = 256;
    res = InternetCanonicalizeUrlA("http://www.winehq.org/index.php?x= ", buffer, &dwSize, ICU_BROWSER_MODE);
    ok(res == 1, "InternetCanonicalizeUrlA failed\n");
    ok(!strcmp(buffer, "http://www.winehq.org/index.php?x="), "Trailing space should have been stripped even in ICU_BROWSER_MODE (%s)\n", buffer);

    res = InternetSetOptionA(NULL, 0xdeadbeef, buffer, sizeof(buffer));
    ok(!res, "InternetSetOptionA succeeded\n");
    ok(GetLastError() == ERROR_INTERNET_INVALID_OPTION,
       "InternetSetOptionA failed %u, expected ERROR_INTERNET_INVALID_OPTION\n", GetLastError());
}