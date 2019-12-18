#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_5__ {int decrypt_use_count; int /*<<< orphan*/  rc4_decrypt_key; int /*<<< orphan*/  decrypt_key; int /*<<< orphan*/  rc4_key_len; int /*<<< orphan*/  decrypt_update_key; } ;
struct TYPE_6__ {TYPE_1__ secure; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_update (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sec_decrypt(RDPCLIENT * This, uint8 * data, int length)
{
	if (This->secure.decrypt_use_count == 4096)
	{
		sec_update(This, This->secure.decrypt_key, This->secure.decrypt_update_key);
		RC4_set_key(&This->secure.rc4_decrypt_key, This->secure.rc4_key_len, This->secure.decrypt_key);
		This->secure.decrypt_use_count = 0;
	}

	RC4(&This->secure.rc4_decrypt_key, length, data, data);
	This->secure.decrypt_use_count++;
}