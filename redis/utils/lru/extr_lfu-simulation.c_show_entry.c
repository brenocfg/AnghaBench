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
struct entry {scalar_t__ ctime; scalar_t__ hits; int /*<<< orphan*/  decrtime; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int keyspace_size ; 
 int /*<<< orphan*/  printf (char*,long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

void show_entry(long pos, struct entry *e) {
    char *tag = "normal       ";

    if (pos >= 10 && pos <= 14) tag = "new no access";
    if (pos >= 15 && pos <= 19) tag = "new accessed ";
    if (pos >= keyspace_size -5) tag= "old no access";

    printf("%ld] <%s> frequency:%d decrtime:%d [%lu hits | age:%ld sec]\n",
        pos, tag, e->counter, e->decrtime, (unsigned long)e->hits,
            time(NULL) - e->ctime);
}