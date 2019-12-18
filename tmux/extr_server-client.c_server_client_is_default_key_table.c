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
struct key_table {int /*<<< orphan*/  name; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  server_client_get_key_table (struct client*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
server_client_is_default_key_table(struct client *c, struct key_table *table)
{
	return (strcmp(table->name, server_client_get_key_table(c)) == 0);
}