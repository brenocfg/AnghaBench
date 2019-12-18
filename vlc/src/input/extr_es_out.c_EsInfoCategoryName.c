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
struct TYPE_3__ {int /*<<< orphan*/  i_meta_id; } ;
typedef  TYPE_1__ es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int asprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *EsInfoCategoryName( es_out_id_t* es )
{
    char *psz_category;

    if( asprintf( &psz_category, _("Stream %d"), es->i_meta_id ) == -1 )
        return NULL;

    return psz_category;
}