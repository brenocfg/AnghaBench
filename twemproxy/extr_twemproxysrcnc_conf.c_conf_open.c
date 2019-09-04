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
struct string {int dummy; } ;
struct conf_pool {int dummy; } ;
struct conf {char* fname; scalar_t__ valid; scalar_t__ parsed; scalar_t__ sound; scalar_t__ valid_token; scalar_t__ valid_event; scalar_t__ valid_parser; scalar_t__ seq; scalar_t__ depth; int /*<<< orphan*/ * fh; int /*<<< orphan*/  arg; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ rstatus_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_DEFAULT_ARGS ; 
 int /*<<< orphan*/  CONF_DEFAULT_POOL ; 
 int /*<<< orphan*/  LOG_VVERB ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  array_deinit (int /*<<< orphan*/ *) ; 
 scalar_t__ array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  log_error (char*,char*,int /*<<< orphan*/ ) ; 
 struct conf* nc_alloc (int) ; 
 int /*<<< orphan*/  nc_free (struct conf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct conf *
conf_open(char *filename)
{
    rstatus_t status;
    struct conf *cf;
    FILE *fh;

    fh = fopen(filename, "r");
    if (fh == NULL) {
        log_error("conf: failed to open configuration '%s': %s", filename,
                  strerror(errno));
        return NULL;
    }

    cf = nc_alloc(sizeof(*cf));
    if (cf == NULL) {
        fclose(fh);
        return NULL;
    }

    status = array_init(&cf->arg, CONF_DEFAULT_ARGS, sizeof(struct string));
    if (status != NC_OK) {
        nc_free(cf);
        fclose(fh);
        return NULL;
    }

    status = array_init(&cf->pool, CONF_DEFAULT_POOL, sizeof(struct conf_pool));
    if (status != NC_OK) {
        array_deinit(&cf->arg);
        nc_free(cf);
        fclose(fh);
        return NULL;
    }

    cf->fname = filename;
    cf->fh = fh;
    cf->depth = 0;
    /* parser, event, and token are initialized later */
    cf->seq = 0;
    cf->valid_parser = 0;
    cf->valid_event = 0;
    cf->valid_token = 0;
    cf->sound = 0;
    cf->parsed = 0;
    cf->valid = 0;

    log_debug(LOG_VVERB, "opened conf '%s'", filename);

    return cf;
}