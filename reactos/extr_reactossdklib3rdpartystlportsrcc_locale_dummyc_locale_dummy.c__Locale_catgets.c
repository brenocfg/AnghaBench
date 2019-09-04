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
struct _Locale_messages {int dummy; } ;
typedef  int /*<<< orphan*/  nl_catd_type ;

/* Variables and functions */

const char* _Locale_catgets(struct _Locale_messages* lmes, nl_catd_type cat,
                            int setid, int msgid, const char *dfault)
{ return dfault; }