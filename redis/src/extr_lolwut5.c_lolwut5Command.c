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
 scalar_t__ getLongFromObjectOrReply (TYPE_1__*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lwDrawSchotter (long,long,long) ; 
 int /*<<< orphan*/  lwFreeCanvas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renderCanvas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void lolwut5Command(client *c) {
    long cols = 66;
    long squares_per_row = 8;
    long squares_per_col = 12;

    /* Parse the optional arguments if any. */
    if (c->argc > 1 &&
        getLongFromObjectOrReply(c,c->argv[1],&cols,NULL) != C_OK)
        return;

    if (c->argc > 2 &&
        getLongFromObjectOrReply(c,c->argv[2],&squares_per_row,NULL) != C_OK)
        return;

    if (c->argc > 3 &&
        getLongFromObjectOrReply(c,c->argv[3],&squares_per_col,NULL) != C_OK)
        return;

    /* Limits. We want LOLWUT to be always reasonably fast and cheap to execute
     * so we have maximum number of columns, rows, and output resulution. */
    if (cols < 1) cols = 1;
    if (cols > 1000) cols = 1000;
    if (squares_per_row < 1) squares_per_row = 1;
    if (squares_per_row > 200) squares_per_row = 200;
    if (squares_per_col < 1) squares_per_col = 1;
    if (squares_per_col > 200) squares_per_col = 200;

    /* Generate some computer art and reply. */
    lwCanvas *canvas = lwDrawSchotter(cols,squares_per_row,squares_per_col);
    sds rendered = renderCanvas(canvas);
    rendered = sdscat(rendered,
        "\nGeorg Nees - schotter, plotter on paper, 1968. Redis ver. ");
    rendered = sdscat(rendered,REDIS_VERSION);
    rendered = sdscatlen(rendered,"\n",1);
    addReplyVerbatim(c,rendered,sdslen(rendered),"txt");
    sdsfree(rendered);
    lwFreeCanvas(canvas);
}