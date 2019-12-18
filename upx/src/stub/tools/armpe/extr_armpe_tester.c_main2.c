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
 int /*<<< orphan*/  call () ; 
 int /*<<< orphan*/  dump (char) ; 
 scalar_t__ import () ; 
 scalar_t__ load (char*) ; 
 int print (char*,...) ; 
 scalar_t__ read () ; 
 scalar_t__ reloc () ; 

__attribute__((used)) static int main2(int argc, char **argv)
{
    if (argc != 2)
        return print("usage: %s arm_pe_file\n", argv[0]), 1;
    if (load(argv[1]))
        return 2;
    if (read())
        return 3;
    dump('0');
    if (import())
        return 4;
    dump('1');
    if (reloc())
        return 5;
    dump('2');

    call();
    print("ok.\n");
    return 0;
}