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
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  append_number (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_open (char*) ; 

__attribute__((used)) static void setup_sequential(void) {
        JournalFile *one, *two;
        one = test_open("one.journal");
        two = test_open("two.journal");
        append_number(one, 1, NULL);
        append_number(one, 2, NULL);
        append_number(two, 3, NULL);
        append_number(two, 4, NULL);
        test_close(one);
        test_close(two);
}