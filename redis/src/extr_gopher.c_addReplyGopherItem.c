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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyProto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void addReplyGopherItem(client *c, const char *type, const char *descr,
                        const char *selector, const char *hostname, int port)
{
    sds item = sdscatfmt(sdsempty(),"%s%s\t%s\t%s\t%i\r\n",
                         type, descr,
                         selector ? selector : "(NULL)",
                         hostname ? hostname : "(NULL)",
                         port);
    addReplyProto(c,item,sdslen(item));
    sdsfree(item);
}