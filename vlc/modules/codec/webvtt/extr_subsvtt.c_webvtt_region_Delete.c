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
struct TYPE_5__ {struct TYPE_5__* psz_id; int /*<<< orphan*/  p_cssstyle; } ;
typedef  TYPE_1__ webvtt_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  webvtt_region_ClearCues (TYPE_1__*) ; 

__attribute__((used)) static void webvtt_region_Delete( webvtt_region_t *p_region )
{
    text_style_Delete( p_region->p_cssstyle );
    webvtt_region_ClearCues( p_region );
    free( p_region->psz_id );
    free( p_region );
}