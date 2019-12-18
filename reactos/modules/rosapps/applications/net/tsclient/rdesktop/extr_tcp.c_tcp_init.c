#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * end; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {TYPE_2__ out; } ;
struct TYPE_8__ {int disconnect_reason; TYPE_1__ tcp; } ;
typedef  TYPE_2__* STREAM ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 void* realloc (int /*<<< orphan*/ *,scalar_t__) ; 

STREAM
tcp_init(RDPCLIENT * This, uint32 maxlen)
{
	if (maxlen > This->tcp.out.size)
	{
		void * p;

		p = realloc(This->tcp.out.data, maxlen);

		if (p == NULL)
		{
			This->disconnect_reason = 262;
			return NULL;
		}

		This->tcp.out.data = (uint8 *)p;
		This->tcp.out.size = maxlen;
	}

	This->tcp.out.p = This->tcp.out.data;
	This->tcp.out.end = This->tcp.out.data + This->tcp.out.size;
	return &This->tcp.out;
}