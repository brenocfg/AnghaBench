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

/* Variables and functions */
 int /*<<< orphan*/  print (char*,unsigned int,unsigned int,unsigned int,...) ; 

__attribute__((used)) static int getprocaddressa(unsigned h, const char *proc)
{
    unsigned p = (unsigned) proc;
    if (p < 0x10000)
    {
        print("getprocaddressa called %c%c%c, ordinal %u\n",
               h, h >> 8, h >> 16, p);
        return h + p * 0x10000;
    }
    print("getprocaddressa called %c%c%c, name %s\n",
           h, h >> 8, h >> 16, proc);
    return h + proc[0] * 0x10000 + proc[1] * 0x1000000;
}