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
struct TYPE_3__ {int zn_key_orig_numints; int zn_key_intlen; } ;
typedef  TYPE_1__ zap_name_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZAP_MAXNAMELEN ; 

__attribute__((used)) static int
fzap_checkname(zap_name_t *zn)
{
	if (zn->zn_key_orig_numints * zn->zn_key_intlen > ZAP_MAXNAMELEN)
		return (SET_ERROR(ENAMETOOLONG));
	return (0);
}