#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lwCanvas ;
struct TYPE_5__ {int argc; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 char* REDIS_VERSION ; 
 int /*<<< orphan*/  addReplyVerbatim (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generateSkyline (int /*<<< orphan*/ *) ; 
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lwCreateCanvas (long,long,int) ; 
 int /*<<< orphan*/  lwFreeCanvas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renderCanvas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void lolwut6Command(client *c) {
    long cols = 80;
    long rows = 20;

    /* Parse the optional arguments if any. */
    if (c->argc > 1 &&
        getLongFromObjectOrReply(c,c->argv[1],&cols,NULL) != C_OK)
        return;

    if (c->argc > 2 &&
        getLongFromObjectOrReply(c,c->argv[2],&rows,NULL) != C_OK)
        return;

    /* Limits. We want LOLWUT to be always reasonably fast and cheap to execute
     * so we have maximum number of columns, rows, and output resulution. */
    if (cols < 1) cols = 1;
    if (cols > 1000) cols = 1000;
    if (rows < 1) rows = 1;
    if (rows > 1000) rows = 1000;

    /* Generate the city skyline and reply. */
    lwCanvas *canvas = lwCreateCanvas(cols,rows,3);
    generateSkyline(canvas);
    sds rendered = renderCanvas(canvas);
    rendered = sdscat(rendered,
        "\nDedicated to the 8 bit game developers of past and present.\n"
        "Original 8 bit image from Plaguemon by hikikomori. Redis ver. ");
    rendered = sdscat(rendered,REDIS_VERSION);
    rendered = sdscatlen(rendered,"\n",1);
    addReplyVerbatim(c,rendered,sdslen(rendered),"txt");
    sdsfree(rendered);
    lwFreeCanvas(canvas);
}