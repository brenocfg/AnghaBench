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
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pstrcat_s (char*,int,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strcat_s(void)
{
    char dest[8];
    const char *small = "sma";
    int ret;

    if(!pstrcat_s)
    {
        win_skip("strcat_s not found\n");
        return;
    }

    memset(dest, 'X', sizeof(dest));
    dest[0] = '\0';
    ret = pstrcat_s(dest, sizeof(dest), small);
    ok(ret == 0, "strcat_s: Copying a string into a big enough destination returned %d, expected 0\n", ret);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == '\0'&&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
    ret = pstrcat_s(dest, sizeof(dest), small);
    ok(ret == 0, "strcat_s: Attaching a string to a big enough destination returned %d, expected 0\n", ret);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == 's' &&
       dest[4] == 'm' && dest[5] == 'a' && dest[6] == '\0'&& dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    ret = pstrcat_s(dest, sizeof(dest), small);
    ok(ret == ERANGE, "strcat_s: Attaching a string to a filled up destination returned %d, expected ERANGE\n", ret);
    ok(dest[0] == '\0'&& dest[1] == 'm' && dest[2] == 'a' && dest[3] == 's' &&
       dest[4] == 'm' && dest[5] == 'a' && dest[6] == 's' && dest[7] == 'm',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    dest[0] = 'a';
    dest[1] = '\0';

    ret = pstrcat_s(dest, 0, small);
    ok(ret == EINVAL, "strcat_s: Source len = 0 returned %d, expected EINVAL\n", ret);
    ok(dest[0] == 'a' && dest[1] == '\0'&& dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    ret = pstrcat_s(dest, 0, NULL);
    ok(ret == EINVAL, "strcat_s: len = 0 and src = NULL returned %d, expected EINVAL\n", ret);
    ok(dest[0] == 'a' && dest[1] == '\0'&& dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    ret = pstrcat_s(dest, sizeof(dest), NULL);
    ok(ret == EINVAL, "strcat_s:  Sourcing from NULL returned %d, expected EINVAL\n", ret);
    ok(dest[0] == '\0'&& dest[1] == '\0'&& dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    ret = pstrcat_s(NULL, sizeof(dest), small);
    ok(ret == EINVAL, "strcat_s: Writing to a NULL string returned %d, expected EINVAL\n", ret);
}