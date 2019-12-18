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
struct client {TYPE_1__* keytable; } ;
struct TYPE_3__ {int /*<<< orphan*/  references; } ;

/* Variables and functions */
 TYPE_1__* key_bindings_get_table (char const*,int) ; 
 int /*<<< orphan*/  key_bindings_unref_table (TYPE_1__*) ; 
 char* server_client_get_key_table (struct client*) ; 

void
server_client_set_key_table(struct client *c, const char *name)
{
	if (name == NULL)
		name = server_client_get_key_table(c);

	key_bindings_unref_table(c->keytable);
	c->keytable = key_bindings_get_table(name, 1);
	c->keytable->references++;
}