#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct conf {int valid_token; TYPE_1__ parser; int /*<<< orphan*/  token; scalar_t__ valid_parser; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ERROR ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 int yaml_parser_scan (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static rstatus_t
conf_token_next(struct conf *cf)
{
    int rv;

    ASSERT(cf->valid_parser && !cf->valid_token);

    rv = yaml_parser_scan(&cf->parser, &cf->token);
    if (!rv) {
        log_error("conf: failed (err %d) to scan next token", cf->parser.error);
        return NC_ERROR;
    }
    cf->valid_token = 1;

    return NC_OK;
}