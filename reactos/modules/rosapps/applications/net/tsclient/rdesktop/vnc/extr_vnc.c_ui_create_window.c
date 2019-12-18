#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int w; int h; int linew; char* data; TYPE_1__* format; void* owner; } ;
typedef  TYPE_2__ vncBuffer ;
struct TYPE_8__ {void* trueColour; } ;
struct TYPE_10__ {char* frameBuffer; int port; int listenSock; TYPE_1__ serverFormat; int /*<<< orphan*/  deferUpdateTime; int /*<<< orphan*/  inetdSock; void* neverShared; void* alwaysShared; void* httpPort; int /*<<< orphan*/  kbdAddEvent; int /*<<< orphan*/  ptrAddEvent; int /*<<< orphan*/  desktopName; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 void* client_counter ; 
 int /*<<< orphan*/  defer_time ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_2__* frameBuffer ; 
 int g_height ; 
 int /*<<< orphan*/  g_title ; 
 int g_width ; 
 int /*<<< orphan*/  init_keyboard () ; 
 scalar_t__ malloc (int) ; 
 int* reverseByte ; 
 int /*<<< orphan*/  rfbClientSocket ; 
 TYPE_3__* rfbGetScreen (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  rfbInitServer (TYPE_3__*) ; 
 int /*<<< orphan*/  rfbInitSockets (TYPE_3__*) ; 
 int rfb_port ; 
 TYPE_3__* server ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ui_set_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vncKey ; 
 int /*<<< orphan*/  vncMouse ; 

BOOL
ui_create_window()
{
	int i;

	for (i = 0; i < 0x100; i++)
		reverseByte[i] =
			(((i >> 7) & 1)) | (((i >> 6) & 1) << 1) | (((i >> 5) & 1) << 2) |
			(((i >> 4) & 1) << 3) | (((i >> 3) & 1) << 4) | (((i >> 2) & 1) << 5) |
			(((i >> 1) & 1) << 6) | (((i >> 0) & 1) << 7);

	server = rfbGetScreen(0, NULL, g_width, g_height, 8, 1, 1);
	server->desktopName = g_title;
	server->frameBuffer = (char *) malloc(g_width * g_height);
	server->ptrAddEvent = vncMouse;
	server->kbdAddEvent = vncKey;
#ifdef ENABLE_SHADOW
	server->httpPort = 6124 + client_counter;
	server->port = 5924 + client_counter;
	rfbInitSockets(server);
	server->alwaysShared = TRUE;
	server->neverShared = FALSE;
#else
	server->port = -1;
	server->alwaysShared = FALSE;
	server->neverShared = FALSE;
#endif
	server->inetdSock = rfbClientSocket;
	server->serverFormat.trueColour = FALSE;	/* activate colour maps */
	server->deferUpdateTime = defer_time;

	frameBuffer = (vncBuffer *) malloc(sizeof(vncBuffer));
	frameBuffer->w = g_width;
	frameBuffer->h = g_height;
	frameBuffer->linew = g_width;
	frameBuffer->data = server->frameBuffer;
	frameBuffer->owner = FALSE;
	frameBuffer->format = &server->serverFormat;

	ui_set_clip(0, 0, g_width, g_height);

	rfbInitServer(server);
#ifndef ENABLE_SHADOW
	server->port = rfb_port;
#else
	fprintf(stderr, "server listening on port %d (socket %d)\n", server->port,
		server->listenSock);
#endif

	init_keyboard();

	return (server != NULL);
}