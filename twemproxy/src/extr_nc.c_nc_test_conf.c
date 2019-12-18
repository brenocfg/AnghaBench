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
struct instance {int /*<<< orphan*/  conf_filename; } ;
struct conf {int dummy; } ;

/* Variables and functions */
 struct conf* conf_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_destroy (struct conf*) ; 
 int /*<<< orphan*/  log_stderr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nc_test_conf(struct instance *nci)
{
    struct conf *cf;

    cf = conf_create(nci->conf_filename);
    if (cf == NULL) {
        log_stderr("nutcracker: configuration file '%s' syntax is invalid",
                   nci->conf_filename);
        return false;
    }

    conf_destroy(cf);

    log_stderr("nutcracker: configuration file '%s' syntax is ok",
               nci->conf_filename);
    return true;
}