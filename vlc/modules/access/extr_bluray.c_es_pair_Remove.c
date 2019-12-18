#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_array_t ;
struct TYPE_5__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ es_pair_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_array_index_of_item (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void es_pair_Remove(vlc_array_t *p_array, es_pair_t *p_pair)
{
    vlc_array_remove(p_array, vlc_array_index_of_item(p_array, p_pair));
    es_format_Clean(&p_pair->fmt);
    free(p_pair);
}