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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LD_STR_AUTO ; 
 int /*<<< orphan*/  LD_STR_HUMAN ; 
 int MAX_LONG_DOUBLE_CHARS ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int ld2string (char*,int,long double,int /*<<< orphan*/ ) ; 

robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
    char buf[MAX_LONG_DOUBLE_CHARS];
    int len = ld2string(buf,sizeof(buf),value,humanfriendly? LD_STR_HUMAN: LD_STR_AUTO);
    return createStringObject(buf,len);
}