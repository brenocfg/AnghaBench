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
struct TYPE_3__ {scalar_t__ i_codec; } ;
typedef  TYPE_1__ es_format_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_AMR_NB ; 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * box_new (char*) ; 

__attribute__((used)) static bo_t *GetDamrTag(es_format_t *p_fmt)
{
    bo_t *damr = box_new("damr");
    if(!damr)
        return NULL;

    bo_add_fourcc(damr, "REFC");
    bo_add_8(damr, 0);

    if (p_fmt->i_codec == VLC_CODEC_AMR_NB)
        bo_add_16be(damr, 0x81ff); /* Mode set (all modes for AMR_NB) */
    else
        bo_add_16be(damr, 0x83ff); /* Mode set (all modes for AMR_WB) */
    bo_add_16be(damr, 0x1); /* Mode change period (no restriction) */

    return damr;
}