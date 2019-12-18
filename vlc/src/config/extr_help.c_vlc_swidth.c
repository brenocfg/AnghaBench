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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 size_t vlc_towc (char const*,int /*<<< orphan*/ *) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_swidth(const char *str)
{
    for (int total = 0;;)
    {
        uint32_t cp;
        size_t charlen = vlc_towc(str, &cp);

        if (charlen == 0)
            return total;
        if (charlen == (size_t)-1)
            return -1;
        str += charlen;

        int w = wcwidth(cp);
        if (w == -1)
            return -1;
        total += w;
    }
}