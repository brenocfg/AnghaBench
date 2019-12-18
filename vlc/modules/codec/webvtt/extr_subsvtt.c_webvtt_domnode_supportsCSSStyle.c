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
typedef  int /*<<< orphan*/  webvtt_dom_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_ppCSSStyle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool webvtt_domnode_supportsCSSStyle( webvtt_dom_node_t *p_node )
{
    return get_ppCSSStyle( p_node ) != NULL;
}