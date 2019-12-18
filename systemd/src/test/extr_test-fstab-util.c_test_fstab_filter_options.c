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
 int /*<<< orphan*/  do_fstab_filter_options (char*,char*,int,char*,char*,char*) ; 

__attribute__((used)) static void test_fstab_filter_options(void) {
        do_fstab_filter_options("opt=0", "opt\0x-opt\0", 1, "opt", "0", "");
        do_fstab_filter_options("opt=0", "x-opt\0opt\0", 1, "opt", "0", "");
        do_fstab_filter_options("opt", "opt\0x-opt\0", 1, "opt", NULL, "");
        do_fstab_filter_options("opt", "x-opt\0opt\0", 1, "opt", NULL, "");
        do_fstab_filter_options("x-opt", "x-opt\0opt\0", 1, "x-opt", NULL, "");

        do_fstab_filter_options("opt=0,other", "opt\0x-opt\0", 1, "opt", "0", "other");
        do_fstab_filter_options("opt=0,other", "x-opt\0opt\0", 1, "opt", "0", "other");
        do_fstab_filter_options("opt,other", "opt\0x-opt\0", 1, "opt", NULL, "other");
        do_fstab_filter_options("opt,other", "x-opt\0opt\0", 1, "opt", NULL, "other");
        do_fstab_filter_options("x-opt,other", "opt\0x-opt\0", 1, "x-opt", NULL, "other");

        do_fstab_filter_options("opto=0,other", "opt\0x-opt\0", 0, NULL, NULL, NULL);
        do_fstab_filter_options("opto,other", "opt\0x-opt\0", 0, NULL, NULL, NULL);
        do_fstab_filter_options("x-opto,other", "opt\0x-opt\0", 0, NULL, NULL, NULL);

        do_fstab_filter_options("first,opt=0", "opt\0x-opt\0", 1, "opt", "0", "first");
        do_fstab_filter_options("first=1,opt=0", "opt\0x-opt\0", 1, "opt", "0", "first=1");
        do_fstab_filter_options("first,opt=", "opt\0x-opt\0", 1, "opt", "", "first");
        do_fstab_filter_options("first=1,opt", "opt\0x-opt\0", 1, "opt", NULL, "first=1");
        do_fstab_filter_options("first=1,x-opt", "opt\0x-opt\0", 1, "x-opt", NULL, "first=1");

        do_fstab_filter_options("first,opt=0,last=1", "opt\0x-opt\0", 1, "opt", "0", "first,last=1");
        do_fstab_filter_options("first=1,opt=0,last=2", "x-opt\0opt\0", 1, "opt", "0", "first=1,last=2");
        do_fstab_filter_options("first,opt,last", "opt\0", 1, "opt", NULL, "first,last");
        do_fstab_filter_options("first=1,opt,last", "x-opt\0opt\0", 1, "opt", NULL, "first=1,last");
        do_fstab_filter_options("first=,opt,last", "opt\0noopt\0", 1, "opt", NULL, "first=,last");

        /* check repeated options */
        do_fstab_filter_options("first,opt=0,noopt=1,last=1", "opt\0noopt\0", 1, "noopt", "1", "first,last=1");
        do_fstab_filter_options("first=1,opt=0,last=2,opt=1", "opt\0", 1, "opt", "1", "first=1,last=2");
        do_fstab_filter_options("x-opt=0,x-opt=1", "opt\0x-opt\0", 1, "x-opt", "1", "");
        do_fstab_filter_options("opt=0,x-opt=1", "opt\0x-opt\0", 1, "x-opt", "1", "");

        /* check that semicolons are not misinterpreted */
        do_fstab_filter_options("opt=0;", "opt\0", 1, "opt", "0;", "");
        do_fstab_filter_options("opt;=0", "x-opt\0opt\0noopt\0x-noopt\0", 0, NULL, NULL, NULL);
        do_fstab_filter_options("opt;", "opt\0x-opt\0", 0, NULL, NULL, NULL);

        /* check that spaces are not misinterpreted */
        do_fstab_filter_options("opt=0 ", "opt\0", 1, "opt", "0 ", "");
        do_fstab_filter_options("opt =0", "x-opt\0opt\0noopt\0x-noopt\0", 0, NULL, NULL, NULL);
        do_fstab_filter_options(" opt ", "opt\0x-opt\0", 0, NULL, NULL, NULL);

        /* check function will NULL args */
        do_fstab_filter_options(NULL, "opt\0", 0, NULL, NULL, "");
        do_fstab_filter_options("", "opt\0", 0, NULL, NULL, "");
}