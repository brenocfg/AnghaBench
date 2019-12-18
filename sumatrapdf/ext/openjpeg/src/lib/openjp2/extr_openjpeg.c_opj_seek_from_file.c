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
typedef  int /*<<< orphan*/  OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OPJ_FALSE ; 
 scalar_t__ OPJ_FSEEK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  SEEK_SET ; 

__attribute__((used)) static OPJ_BOOL opj_seek_from_file(OPJ_OFF_T p_nb_bytes, FILE * p_user_data)
{
    if (OPJ_FSEEK(p_user_data, p_nb_bytes, SEEK_SET)) {
        return OPJ_FALSE;
    }

    return OPJ_TRUE;
}