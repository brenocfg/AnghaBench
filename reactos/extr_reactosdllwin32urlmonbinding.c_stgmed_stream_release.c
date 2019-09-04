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
typedef  int /*<<< orphan*/  stgmed_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/  IStream_iface; } ;
typedef  TYPE_1__ ProtocolStream ;

/* Variables and functions */
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stgmed_stream_release(stgmed_obj_t *obj)
{
    ProtocolStream *stream = (ProtocolStream*)obj;
    IStream_Release(&stream->IStream_iface);
}