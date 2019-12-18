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
typedef  int /*<<< orphan*/  dst ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ICU_BROWSER_MODE ; 
 int /*<<< orphan*/  ICU_DECODE ; 
 int /*<<< orphan*/  ICU_ENCODE_PERCENT ; 
 int /*<<< orphan*/  ICU_ENCODE_SPACES_ONLY ; 
 int /*<<< orphan*/  ICU_ESCAPE ; 
 int /*<<< orphan*/  ICU_NO_ENCODE ; 
 int /*<<< orphan*/  ICU_NO_META ; 
 int /*<<< orphan*/  InternetCanonicalizeUrlA (char*,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void InternetCanonicalizeUrl_test(void)
{
    char src[] = "http://www.winehq.org/%27/ /./>/#>  ";
    char dst[64];
    DWORD dstlen;

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, 0);
    ok(strcmp(dst, "http://www.winehq.org/%27/%20/%3E/#>") == 0, "Got \"%s\"\n", dst);

    /* despite what MSDN says, ICU_BROWSER_MODE seems to be ignored */
    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_BROWSER_MODE);
    ok(strcmp(dst, "http://www.winehq.org/%27/%20/%3E/#>") == 0, "Got \"%s\"\n", dst);

    /* ICU_ESCAPE is supposed to be ignored */
    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_ESCAPE);
    ok(strcmp(dst, "http://www.winehq.org/%27/%20/%3E/#>") == 0, "Got \"%s\"\n", dst);

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_DECODE);
    ok(strcmp(dst, "http://www.winehq.org/'/%20/%3E/#>") == 0, "Got \"%s\"\n", dst);

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_ENCODE_PERCENT);
    ok(strcmp(dst, "http://www.winehq.org/%2527/%20/%3E/#>") == 0, "Got \"%s\"\n", dst);

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_ENCODE_SPACES_ONLY);
    ok(strcmp(dst, "http://www.winehq.org/%27/%20/>/#>") == 0, "Got \"%s\"\n", dst);

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_NO_ENCODE);
    ok(strcmp(dst, "http://www.winehq.org/%27/ />/#>") == 0, "Got \"%s\"\n", dst);

    dstlen = sizeof(dst);
    InternetCanonicalizeUrlA(src, dst, &dstlen, ICU_NO_META);
    ok(strcmp(dst, "http://www.winehq.org/%27/%20/./%3E/#>") == 0, "Got \"%s\"\n", dst);
}