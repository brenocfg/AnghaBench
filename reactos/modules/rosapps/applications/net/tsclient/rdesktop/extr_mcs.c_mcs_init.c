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
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/ * iso_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mcs_hdr ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

STREAM
mcs_init(RDPCLIENT * This, int length)
{
	STREAM s;

	s = iso_init(This, length + 8);

	if(s == NULL)
		return NULL;

	s_push_layer(s, mcs_hdr, 8);

	return s;
}