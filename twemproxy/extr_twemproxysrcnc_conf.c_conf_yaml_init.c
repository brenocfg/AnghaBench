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
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
struct conf {int valid_parser; int /*<<< orphan*/  fh; TYPE_1__ parser; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int yaml_parser_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rstatus_t
conf_yaml_init(struct conf *cf)
{
    int rv;

    ASSERT(!cf->valid_parser);

    rv = fseek(cf->fh, 0L, SEEK_SET);
    if (rv < 0) {
        log_error("conf: failed to seek to the beginning of file '%s': %s",
                  cf->fname, strerror(errno));
        return NC_ERROR;
    }

    rv = yaml_parser_initialize(&cf->parser);
    if (!rv) {
        log_error("conf: failed (err %d) to initialize yaml parser",
                  cf->parser.error);
        return NC_ERROR;
    }

    yaml_parser_set_input_file(&cf->parser, cf->fh);
    cf->valid_parser = 1;

    return NC_OK;
}