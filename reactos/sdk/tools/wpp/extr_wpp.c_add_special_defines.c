#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {void* type; } ;
typedef  TYPE_1__ pp_entry_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* def_special ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 TYPE_1__* pp_add_define (char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_special_defines(void)
{
    time_t now = time(NULL);
    pp_entry_t *ppp;
    char buf[32];

    strftime(buf, sizeof(buf), "\"%b %d %Y\"", localtime(&now));
    pp_add_define( "__DATE__", buf );

    strftime(buf, sizeof(buf), "\"%H:%M:%S\"", localtime(&now));
    pp_add_define( "__TIME__", buf );

    ppp = pp_add_define( "__FILE__", "" );
    if(ppp)
        ppp->type = def_special;

    ppp = pp_add_define( "__LINE__", "" );
    if(ppp)
        ppp->type = def_special;
}