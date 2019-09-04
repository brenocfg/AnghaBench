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
struct conf {int parsed; int /*<<< orphan*/  arg; scalar_t__ sound; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NC_OK ; 
 scalar_t__ array_n (int /*<<< orphan*/ *) ; 
 scalar_t__ conf_begin_parse (struct conf*) ; 
 scalar_t__ conf_end_parse (struct conf*) ; 
 scalar_t__ conf_parse_core (struct conf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static rstatus_t
conf_parse(struct conf *cf)
{
    rstatus_t status;

    ASSERT(cf->sound && !cf->parsed);
    ASSERT(array_n(&cf->arg) == 0);

    status = conf_begin_parse(cf);
    if (status != NC_OK) {
        return status;
    }

    status = conf_parse_core(cf, NULL);
    if (status != NC_OK) {
        return status;
    }

    status = conf_end_parse(cf);
    if (status != NC_OK) {
        return status;
    }

    cf->parsed = 1;

    return NC_OK;
}