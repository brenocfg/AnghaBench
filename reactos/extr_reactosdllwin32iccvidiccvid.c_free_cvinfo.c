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
struct TYPE_4__ {unsigned int strip_num; struct TYPE_4__** v1_codebook; struct TYPE_4__** v4_codebook; } ;
typedef  TYPE_1__ cinepak_info ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void free_cvinfo( cinepak_info *cvinfo )
{
    unsigned int i;

    for( i=0; i<cvinfo->strip_num; i++ )
    {
        heap_free(cvinfo->v4_codebook[i]);
        heap_free(cvinfo->v1_codebook[i]);
    }
    heap_free( cvinfo );
}