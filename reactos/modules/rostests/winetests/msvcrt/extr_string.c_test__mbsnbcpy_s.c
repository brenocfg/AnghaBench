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
 int ERANGE ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned char,...) ; 
 int p_mbsnbcpy_s (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__mbsnbcpy_s(void)
{
    unsigned char dest[8];
    const unsigned char big[] = "atoolongstringforthislittledestination";
    const unsigned char small[] = "small";
    int ret;

    if(!p_mbsnbcpy_s)
    {
        win_skip("_mbsnbcpy_s not found\n");
        return;
    }

    memset(dest, 'X', sizeof(dest));
    ret = p_mbsnbcpy_s(dest, sizeof(dest), small, sizeof(small));
    ok(ret == 0, "_mbsnbcpy_s: Copying a string into a big enough destination returned %d, expected 0\n", ret);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == 'l' &&
       dest[4] == 'l' && dest[5] == '\0'&& dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from _mbsnbcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    /* WTF? */
    memset(dest, 'X', sizeof(dest));
    ret = p_mbsnbcpy_s(dest, sizeof(dest) - 2, big, sizeof(small));
    ok(ret == ERANGE, "_mbsnbcpy_s: Copying a too long string returned %d, expected ERANGE\n", ret);
    ok(dest[0] == '\0'&& dest[1] == 't' && dest[2] == 'o' && dest[3] == 'o' &&
       dest[4] == 'l' && dest[5] == 'o' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from _mbsnbcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    ret = p_mbsnbcpy_s(dest, sizeof(dest) - 2, big, 4);
    ok(ret == 0, "_mbsnbcpy_s: Copying a too long string with a count cap returned %d, expected 0\n", ret);
    ok(dest[0] == 'a' && dest[1] == 't' && dest[2] == 'o' && dest[3] == 'o' &&
       dest[4] == '\0'&& dest[5] == 'X' && dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from _mbsnbcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);

    memset(dest, 'X', sizeof(dest));
    ret = p_mbsnbcpy_s(dest, sizeof(dest) - 2, small, sizeof(small) + 10);
    ok(ret == 0, "_mbsnbcpy_s: Copying more data than the source string len returned %d, expected 0\n", ret);
    ok(dest[0] == 's' && dest[1] == 'm' && dest[2] == 'a' && dest[3] == 'l' &&
       dest[4] == 'l' && dest[5] == '\0'&& dest[6] == 'X' && dest[7] == 'X',
       "Unexpected return data from _mbsnbcpy_s: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
       dest[0], dest[1], dest[2], dest[3], dest[4], dest[5], dest[6], dest[7]);
}