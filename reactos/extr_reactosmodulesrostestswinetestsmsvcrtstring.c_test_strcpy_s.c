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
typedef  int /*<<< orphan*/  small ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,char,...) ; 
 int /*<<< orphan*/  p_strcpy (char*,char*) ; 
 int pstrcpy_s (char*,int,char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strcpy_s(void)
{
    char dest[8];
    const char small[] = "small";
    const char big[] = "atoolongstringforthislittledestination";
    int ret;

    if(!pstrcpy_s)
    {
        win_skip("strcpy_s not found\n");
        return;
    }

    memset(dest, 'X', sizeof(dest));
    ret = pstrcpy_s(dest, sizeof(dest), small);
    ok(ret == 0, "Copying a string into a big enough destination returned %d, expected 0\n", ret);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == 'l' &&
       dest[4] == 'l' && dest[5] == '\0'&& dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    ret = pstrcpy_s(dest, 0, big);
    ok(ret == EINVAL, "Copying into a destination of size 0 returned %d, expected EINVAL\n", ret);
    ok(dest[0] == 'X' && dest[1] == 'X' && dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
    ret = pstrcpy_s(dest, 0, NULL);
    ok(ret == EINVAL, "Copying into a destination of size 0 returned %d, expected EINVAL\n", ret);
    ok(dest[0] == 'X' && dest[1] == 'X' && dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    ret = pstrcpy_s(dest, sizeof(dest), big);
    ok(ret == ERANGE, "Copying a big string in a small location returned %d, expected ERANGE\n", ret);
    ok(dest[0] == '\0'&& dest[1] == 't' && dest[2] == 'o' && dest[3] == 'o' &&
       dest[4] == 'l' && dest[5] == 'o' && dest[6] == 'n' && dest[7] == 'g',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    ret = pstrcpy_s(dest, sizeof(dest), NULL);
    ok(ret == EINVAL, "Copying from a NULL source string returned %d, expected EINVAL\n", ret);
    ok(dest[0] == '\0'&& dest[1] == 'X' && dest[2] == 'X' && dest[3] == 'X' &&
       dest[4] == 'X' && dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from strcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    ret = pstrcpy_s(NULL, sizeof(dest), small);
    ok(ret == EINVAL, "Copying a big string a NULL dest returned %d, expected EINVAL\n", ret);

    /* strcpy overlapping buffers test */
    memset(dest, 'X', sizeof(dest));
    memcpy(dest+1, small, sizeof(small));
    p_strcpy(dest, dest+1);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == 'l' &&
            dest[4] == 'l' && dest[5] == '\0' && dest[6] == '\0' && dest[7] == 'X',
            "Unexpected return data from strcpy: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
            dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
}