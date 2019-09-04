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
struct conf {int /*<<< orphan*/ * fh; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  conf_destroy (struct conf*) ; 
 int /*<<< orphan*/  conf_dump (struct conf*) ; 
 struct conf* conf_open (char*) ; 
 scalar_t__ conf_parse (struct conf*) ; 
 scalar_t__ conf_post_validate (struct conf*) ; 
 scalar_t__ conf_pre_validate (struct conf*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_stderr (char*,char*) ; 

struct conf *
conf_create(char *filename)
{
    rstatus_t status;
    struct conf *cf;

    cf = conf_open(filename);
    if (cf == NULL) {
        return NULL;
    }

    /* validate configuration file before parsing */
    status = conf_pre_validate(cf);
    if (status != NC_OK) {
        goto error;
    }

    /* parse the configuration file */
    status = conf_parse(cf);
    if (status != NC_OK) {
        goto error;
    }

    /* validate parsed configuration */
    status = conf_post_validate(cf);
    if (status != NC_OK) {
        goto error;
    }

    conf_dump(cf);

    fclose(cf->fh);
    cf->fh = NULL;

    return cf;

error:
    log_stderr("nutcracker: configuration file '%s' syntax is invalid",
               filename);
    fclose(cf->fh);
    cf->fh = NULL;
    conf_destroy(cf);
    return NULL;
}