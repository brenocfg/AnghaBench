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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 unsigned int min (int,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static void dump(const void* ptr, unsigned len)
{
    unsigned int i, j;
    char        msg[128];
    const char* hexof = "0123456789abcdef";
    const BYTE* x = ptr;

    for (i = 0; i < len; i += 16)
    {
        sprintf(msg, "%08x: ", i);
        memset(msg + 10, ' ', 3 * 16 + 1 + 16);
        for (j = 0; j < min(16, len - i); j++)
        {
            msg[10 + 3 * j + 0] = hexof[x[i + j] >> 4];
            msg[10 + 3 * j + 1] = hexof[x[i + j] & 15];
            msg[10 + 3 * j + 2] = ' ';
            msg[10 + 3 * 16 + 1 + j] = (x[i + j] >= 0x20 && x[i + j] < 0x7f) ?
                x[i + j] : '.';
        }
        msg[10 + 3 * 16] = ' ';
        msg[10 + 3 * 16 + 1 + 16] = '\0';
        FIXME("%s\n", msg);
    }
}