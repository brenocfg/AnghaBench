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
struct skynet_context {int dummy; } ;
struct gate {int max_connection; int client_tag; int header_size; TYPE_1__* conn; int /*<<< orphan*/  hash; struct skynet_context* ctx; int /*<<< orphan*/  watchdog; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int PTYPE_CLIENT ; 
 int /*<<< orphan*/  _cb ; 
 int /*<<< orphan*/  hashid_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skynet_callback (struct skynet_context*,struct gate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,...) ; 
 TYPE_1__* skynet_malloc (int) ; 
 int /*<<< orphan*/  skynet_queryname (struct skynet_context*,char*) ; 
 int sscanf (char*,char*,char*,char*,char*,int*,int*) ; 
 int start_listen (struct gate*,char*) ; 
 int strlen (char*) ; 

int
gate_init(struct gate *g , struct skynet_context * ctx, char * parm) {
	if (parm == NULL)
		return 1;
	int max = 0;
	int sz = strlen(parm)+1;
	char watchdog[sz];
	char binding[sz];
	int client_tag = 0;
	char header;
	int n = sscanf(parm, "%c %s %s %d %d", &header, watchdog, binding, &client_tag, &max);
	if (n<4) {
		skynet_error(ctx, "Invalid gate parm %s",parm);
		return 1;
	}
	if (max <=0 ) {
		skynet_error(ctx, "Need max connection");
		return 1;
	}
	if (header != 'S' && header !='L') {
		skynet_error(ctx, "Invalid data header style");
		return 1;
	}

	if (client_tag == 0) {
		client_tag = PTYPE_CLIENT;
	}
	if (watchdog[0] == '!') {
		g->watchdog = 0;
	} else {
		g->watchdog = skynet_queryname(ctx, watchdog);
		if (g->watchdog == 0) {
			skynet_error(ctx, "Invalid watchdog %s",watchdog);
			return 1;
		}
	}

	g->ctx = ctx;

	hashid_init(&g->hash, max);
	g->conn = skynet_malloc(max * sizeof(struct connection));
	memset(g->conn, 0, max *sizeof(struct connection));
	g->max_connection = max;
	int i;
	for (i=0;i<max;i++) {
		g->conn[i].id = -1;
	}
	
	g->client_tag = client_tag;
	g->header_size = header=='S' ? 2 : 4;

	skynet_callback(ctx,g,_cb);

	return start_listen(g,binding);
}