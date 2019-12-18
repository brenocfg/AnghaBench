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
struct conf {int sound; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 scalar_t__ conf_validate_document (struct conf*) ; 
 scalar_t__ conf_validate_structure (struct conf*) ; 
 scalar_t__ conf_validate_tokens (struct conf*) ; 

__attribute__((used)) static rstatus_t
conf_pre_validate(struct conf *cf)
{
    rstatus_t status;

    status = conf_validate_document(cf);
    if (status != NC_OK) {
        return status;
    }

    status = conf_validate_tokens(cf);
    if (status != NC_OK) {
        return status;
    }

    status = conf_validate_structure(cf);
    if (status != NC_OK) {
        return status;
    }

    cf->sound = 1;

    return NC_OK;
}