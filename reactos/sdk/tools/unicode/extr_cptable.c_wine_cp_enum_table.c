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
typedef  union cptable {int dummy; } cptable ;

/* Variables and functions */
 unsigned int NB_CODEPAGES ; 
 union cptable const** cptables ; 

const union cptable *wine_cp_enum_table( unsigned int index )
{
    if (index >= NB_CODEPAGES) return NULL;
    return cptables[index];
}