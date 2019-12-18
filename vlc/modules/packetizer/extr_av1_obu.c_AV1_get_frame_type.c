#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum av1_frame_type_e { ____Placeholder_av1_frame_type_e } av1_frame_type_e ;
struct TYPE_4__ {int frame_type; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
typedef  TYPE_2__ av1_OBU_frame_header_t ;

/* Variables and functions */

enum av1_frame_type_e AV1_get_frame_type(const av1_OBU_frame_header_t *p_fh)
{
    return p_fh->header.frame_type;
}