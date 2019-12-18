#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; int sx; int sy; } ;
struct client {int references; int fd; int /*<<< orphan*/  click_timer; int /*<<< orphan*/  repeat_timer; TYPE_2__* keytable; int /*<<< orphan*/  flags; scalar_t__ prompt_index; int /*<<< orphan*/ * prompt_buffer; int /*<<< orphan*/ * prompt_string; int /*<<< orphan*/  message_log; int /*<<< orphan*/ * message_string; TYPE_1__ tty; int /*<<< orphan*/ * last_session; int /*<<< orphan*/ * session; int /*<<< orphan*/ * title; int /*<<< orphan*/ * stderr_data; int /*<<< orphan*/ * stdout_data; int /*<<< orphan*/ * stdin_data; int /*<<< orphan*/  queue; int /*<<< orphan*/ * cwd; int /*<<< orphan*/  environ; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  activity_time; int /*<<< orphan*/  peer; } ;
struct TYPE_4__ {int /*<<< orphan*/  references; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_FOCUSED ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clients ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  environ_create () ; 
 void* evbuffer_new () ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct client*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 scalar_t__ gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* key_bindings_get_table (char*,int) ; 
 int /*<<< orphan*/  log_debug (char*,struct client*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_add_peer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct client*) ; 
 int /*<<< orphan*/  server_client_click_timer ; 
 int /*<<< orphan*/  server_client_dispatch ; 
 int /*<<< orphan*/  server_client_repeat_timer ; 
 int /*<<< orphan*/  server_proc ; 
 int /*<<< orphan*/  setblocking (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_init (struct client*) ; 
 struct client* xcalloc (int,int) ; 

struct client *
server_client_create(int fd)
{
	struct client	*c;

	setblocking(fd, 0);

	c = xcalloc(1, sizeof *c);
	c->references = 1;
	c->peer = proc_add_peer(server_proc, fd, server_client_dispatch, c);

	if (gettimeofday(&c->creation_time, NULL) != 0)
		fatal("gettimeofday failed");
	memcpy(&c->activity_time, &c->creation_time, sizeof c->activity_time);

	c->environ = environ_create();

	c->fd = -1;
	c->cwd = NULL;

	TAILQ_INIT(&c->queue);

	c->stdin_data = evbuffer_new();
	if (c->stdin_data == NULL)
		fatalx("out of memory");
	c->stdout_data = evbuffer_new();
	if (c->stdout_data == NULL)
		fatalx("out of memory");
	c->stderr_data = evbuffer_new();
	if (c->stderr_data == NULL)
		fatalx("out of memory");

	c->tty.fd = -1;
	c->title = NULL;

	c->session = NULL;
	c->last_session = NULL;

	c->tty.sx = 80;
	c->tty.sy = 24;

	status_init(c);

	c->message_string = NULL;
	TAILQ_INIT(&c->message_log);

	c->prompt_string = NULL;
	c->prompt_buffer = NULL;
	c->prompt_index = 0;

	c->flags |= CLIENT_FOCUSED;

	c->keytable = key_bindings_get_table("root", 1);
	c->keytable->references++;

	evtimer_set(&c->repeat_timer, server_client_repeat_timer, c);
	evtimer_set(&c->click_timer, server_client_click_timer, c);

	TAILQ_INSERT_TAIL(&clients, c, entry);
	log_debug("new client %p", c);
	return (c);
}