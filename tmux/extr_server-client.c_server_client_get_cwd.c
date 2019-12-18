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
struct session {char const* cwd; } ;
struct client {char const* cwd; struct session* session; } ;
struct TYPE_2__ {char const* cwd; } ;

/* Variables and functions */
 TYPE_1__* cfg_client ; 
 int /*<<< orphan*/  cfg_finished ; 
 char* find_home () ; 

const char *
server_client_get_cwd(struct client *c, struct session *s)
{
	const char	*home;

	if (!cfg_finished && cfg_client != NULL)
		return (cfg_client->cwd);
	if (c != NULL && c->session == NULL && c->cwd != NULL)
		return (c->cwd);
	if (s != NULL && s->cwd != NULL)
		return (s->cwd);
	if (c != NULL && (s = c->session) != NULL && s->cwd != NULL)
		return (s->cwd);
	if ((home = find_home()) != NULL)
		return (home);
	return ("/");
}