#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_12__ {int /*<<< orphan*/  key; } ;
struct TYPE_14__ {void* licence_issued; TYPE_1__ licence; } ;
struct TYPE_13__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_2__* STREAM ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  int /*<<< orphan*/  RC4_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* True ; 
 int /*<<< orphan*/  in_uint16 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  in_uint16_le (TYPE_2__*,int) ; 
 int /*<<< orphan*/  in_uint32_le (TYPE_2__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_2__*,int) ; 
 int /*<<< orphan*/  s_check_rem (TYPE_2__*,int) ; 
 int /*<<< orphan*/  save_licence (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
licence_process_issue(RDPCLIENT * This, STREAM s)
{
	RC4_KEY crypt_key;
	uint32 length;
	uint16 check;
	int i;

	in_uint8s(s, 2);	/* 3d 45 - unknown */
	in_uint16_le(s, length);
	if (!s_check_rem(s, length))
		return;

	RC4_set_key(&crypt_key, 16, This->licence.key);
	RC4(&crypt_key, length, s->p, s->p);

	in_uint16(s, check);
	if (check != 0)
		return;

	This->licence_issued = True;

	in_uint8s(s, 2);	/* pad */

	/* advance to fourth string */
	length = 0;
	for (i = 0; i < 4; i++)
	{
		in_uint8s(s, length);
		in_uint32_le(s, length);
		if (!s_check_rem(s, length))
			return;
	}

	This->licence_issued = True;
	save_licence(This, s->p, length);
}