#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {int bpp; int /*<<< orphan*/  vs_height; int /*<<< orphan*/  vs_width; } ;
typedef  scalar_t__ GR_CURSOR_ID ;

/* Variables and functions */
 int /*<<< orphan*/  GR_ROOT_WINDOW_ID ; 
 int /*<<< orphan*/  GrClose () ; 
 int /*<<< orphan*/  GrDestroyGC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrDestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrFillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrGetScreenInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  GrMainLoop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrMapWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrNewGC () ; 
 int /*<<< orphan*/  GrNewWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GrOpen () ; 
 int /*<<< orphan*/  GrRegisterInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrSelectEvents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GrSetGCForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int g_Bpp ; 
 int g_bpp ; 
 TYPE_2__ g_clip ; 
 int /*<<< orphan*/  g_directory ; 
 int /*<<< orphan*/  g_domain ; 
 int /*<<< orphan*/  g_flags ; 
 int /*<<< orphan*/  g_gc ; 
 int /*<<< orphan*/  g_gc_clean ; 
 int /*<<< orphan*/  g_height ; 
 scalar_t__ g_null_cursor ; 
 int /*<<< orphan*/  g_password ; 
 int /*<<< orphan*/  g_sck ; 
 TYPE_1__ g_screen_info ; 
 int g_server_bpp ; 
 int /*<<< orphan*/  g_servername ; 
 int /*<<< orphan*/  g_shell ; 
 int /*<<< orphan*/  g_width ; 
 int /*<<< orphan*/  g_wnd ; 
 int /*<<< orphan*/  get_username_and_hostname () ; 
 int /*<<< orphan*/  init_keys () ; 
 int /*<<< orphan*/  nanox_event ; 
 int /*<<< orphan*/  parse_parameters (int,char**) ; 
 int /*<<< orphan*/  rdp_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ ui_create_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_destroy_cursor (void*) ; 

int main(int in_argc, char ** in_argv)
{
  get_username_and_hostname();
  /* read command line options */
  if (!parse_parameters(in_argc, in_argv))
  {
    exit(0);
  }
  /* connect to server */
  if (GrOpen() < 0)
  {
    fprintf(stderr, "Couldn't connect to Nano-X server\n");
    exit(1);
  }
  GrGetScreenInfo(&g_screen_info);
  g_bpp = g_screen_info.bpp;
  g_Bpp = (g_screen_info.bpp + 7) / 8;
  g_width = g_screen_info.vs_width;
  g_height = g_screen_info.vs_height;
  g_clip.x = 0;
  g_clip.y = 0;
  g_clip.width = g_width;
  g_clip.height = g_height;
  if (!((g_bpp == 32 && g_server_bpp == 16) ||
        (g_bpp == 16 && g_server_bpp == 16)))
  {
    fprintf(stderr, "unsupported bpp, server = %d, client = %d\n",
            g_server_bpp, g_bpp);
    GrClose();
    exit(0);
  }
  init_keys();
  /* connect to server */
  if (!rdp_connect(g_servername, g_flags, g_domain, g_password, g_shell,
                   g_directory))
  {
    fprintf(stderr, "Error connecting\n");
    GrClose();
    exit(1);
  }
  /* create window */
  g_wnd = GrNewWindow(GR_ROOT_WINDOW_ID, 0, 0, g_width, g_height, 0, 0, 0);
  /* show window */
  GrMapWindow(g_wnd);
  /* create graphic context */
  g_gc = GrNewGC();
  g_gc_clean = GrNewGC();
  /* clear screen */
  GrSetGCForeground(g_gc, 0);
  GrFillRect(g_wnd, g_gc, 0, 0, g_width, g_height);
  /* create null cursor */
  g_null_cursor = (GR_CURSOR_ID)ui_create_cursor(0, 0, 32, 32, 0, 0);
  /* register callbacks, set mask, and run main loop */
  GrSelectEvents(g_wnd, -1); /* all events */
  GrRegisterInput(g_sck);
  GrMainLoop(nanox_event);
  /* free null cursor */
  ui_destroy_cursor((void*)g_null_cursor);
  /* free graphic context */
  GrDestroyGC(g_gc);
  GrDestroyGC(g_gc_clean);
  /* free window */
  GrDestroyWindow(g_wnd);
  /* close connection */
  GrClose();
  return 0;
}