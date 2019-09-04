#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ encryption; } ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_ENCRYPT ; 
 int /*<<< orphan*/  rdp_hdr ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sec_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static STREAM
rdp_init_data(RDPCLIENT * This, int maxlen)
{
	STREAM s;

	s = sec_init(This, This->encryption ? SEC_ENCRYPT : 0, maxlen + 18);

	if(s == NULL)
		return NULL;

	s_push_layer(s, rdp_hdr, 18);

	return s;
}