#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_1__ stream_extractor_t ;

/* Variables and functions */
 void CommonClose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ExtractorClose( vlc_object_t* p_obj )
{
    stream_extractor_t* p_extractor = (void*)p_obj;
    return CommonClose( p_extractor->p_sys );
}