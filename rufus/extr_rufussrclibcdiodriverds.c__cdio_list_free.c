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
typedef  int /*<<< orphan*/  CdioList_t ;
typedef  int /*<<< orphan*/  CdioDataFree_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ _cdio_list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cdio_list_node_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
_cdio_list_free (CdioList_t *p_list, int free_data, CdioDataFree_t free_fn)
{
  while (_cdio_list_length (p_list))
    _cdio_list_node_free (_cdio_list_begin (p_list), free_data, free_fn);

  free (p_list);
}