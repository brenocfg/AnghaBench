#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buf; scalar_t__ ct; } ;
typedef  TYPE_1__ opj_bio_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  opj_bio_bytein (TYPE_1__*) ; 

OPJ_BOOL opj_bio_inalign(opj_bio_t *bio)
{
    if ((bio->buf & 0xff) == 0xff) {
        if (! opj_bio_bytein(bio)) {
            return OPJ_FALSE;
        }
    }
    bio->ct = 0;
    return OPJ_TRUE;
}