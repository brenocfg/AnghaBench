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
struct TYPE_4__ {int ct; int buf; } ;
typedef  TYPE_1__ opj_bio_t ;
typedef  int OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_bio_bytein (TYPE_1__*) ; 

__attribute__((used)) static OPJ_UINT32 opj_bio_getbit(opj_bio_t *bio)
{
    if (bio->ct == 0) {
        opj_bio_bytein(
            bio); /* MSD: why not check the return value of this function ? */
    }
    bio->ct--;
    return (bio->buf >> bio->ct) & 1;
}