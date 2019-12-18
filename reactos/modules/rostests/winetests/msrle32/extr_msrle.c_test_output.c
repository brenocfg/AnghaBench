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
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int const) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_output(const BYTE *output, int out_size, const BYTE *expect, int size)
{
    char buf[512], *ptr;
    int i;

    i = out_size == size && !memcmp(output, expect, size);
    ok(i, "Unexpected output\n");
    if(i)
        return;

    for(i=0, ptr=buf; i<out_size; i++)
        ptr += sprintf(ptr, "%x ", output[i]);
    trace("Got: %s\n", buf);
    for(i=0, ptr=buf; i<size; i++)
        ptr += sprintf(ptr, "%x ", expect[i]);
    trace("Exp: %s\n", buf);
}