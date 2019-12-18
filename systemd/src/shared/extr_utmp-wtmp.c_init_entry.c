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
typedef  int /*<<< orphan*/  usec_t ;
struct utsname {char* release; } ;
struct utmpx {int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct utmpx*) ; 
 int /*<<< orphan*/  init_timestamp (struct utmpx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void init_entry(struct utmpx *store, usec_t t) {
        struct utsname uts = {};

        assert(store);

        init_timestamp(store, t);

        if (uname(&uts) >= 0)
                strncpy(store->ut_host, uts.release, sizeof(store->ut_host));

        strncpy(store->ut_line, "~", sizeof(store->ut_line));  /* or ~~ ? */
        strncpy(store->ut_id, "~~", sizeof(store->ut_id));
}