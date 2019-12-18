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
struct TYPE_2__ {float fontsize; float baseline; float lineheight; float gridsize; int /*<<< orphan*/  overlay_list; } ;

/* Variables and functions */
 float DEFAULT_UI_BASELINE ; 
 float DEFAULT_UI_FONTSIZE ; 
 float DEFAULT_UI_GRIDSIZE ; 
 float DEFAULT_UI_LINEHEIGHT ; 
 int /*<<< orphan*/  GLUT_ACTION_GLUTMAINLOOP_RETURNS ; 
 int /*<<< orphan*/  GLUT_ACTION_ON_WINDOW_CLOSE ; 
 int GLUT_DOUBLE ; 
 int GLUT_RGBA ; 
 int /*<<< orphan*/  GLUT_SCREEN_HEIGHT ; 
 int /*<<< orphan*/  GLUT_SCREEN_HEIGHT_MM ; 
 int /*<<< orphan*/  GLUT_SCREEN_WIDTH ; 
 int /*<<< orphan*/  GLUT_SCREEN_WIDTH_MM ; 
 int /*<<< orphan*/  GL_MAX_TEXTURE_SIZE ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGenLists (int) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glutCreateWindow (char const*) ; 
 int /*<<< orphan*/  glutDisplayFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutExtensionSupported (char*) ; 
 int glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInitDisplayMode (int) ; 
 int /*<<< orphan*/  glutInitErrorFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInitWarningFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInitWindowSize (int,int) ; 
 int /*<<< orphan*/  glutKeyboardExtFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutKeyboardFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutMotionFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutMouseFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutMouseWheelFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutPassiveMotionFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutReshapeFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutSetOption (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutSpecialFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutTimerFunc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_ARB_texture_non_power_of_two ; 
 int /*<<< orphan*/  max_texture_size ; 
 int /*<<< orphan*/  on_display ; 
 int /*<<< orphan*/  on_error ; 
 int /*<<< orphan*/  on_keyboard ; 
 int /*<<< orphan*/  on_motion ; 
 int /*<<< orphan*/  on_mouse ; 
 int /*<<< orphan*/  on_passive_motion ; 
 int /*<<< orphan*/  on_reshape ; 
 int /*<<< orphan*/  on_special ; 
 int /*<<< orphan*/  on_timer ; 
 int /*<<< orphan*/  on_warning ; 
 int /*<<< orphan*/  on_wheel ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_init_fonts () ; 

void ui_init(int w, int h, const char *title)
{
	float ui_scale;

#ifdef FREEGLUT
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

	glutInitErrorFunc(on_error);
	glutInitWarningFunc(on_warning);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);

	glutTimerFunc(500, on_timer, 0);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
#if defined(FREEGLUT) && (GLUT_API_VERSION >= 6)
	glutKeyboardExtFunc(on_keyboard);
#else
	glutKeyboardFunc(on_keyboard);
#endif
	glutSpecialFunc(on_special);
	glutMouseFunc(on_mouse);
	glutMotionFunc(on_motion);
	glutPassiveMotionFunc(on_passive_motion);
	glutMouseWheelFunc(on_wheel);

	has_ARB_texture_non_power_of_two = glutExtensionSupported("GL_ARB_texture_non_power_of_two");
	if (!has_ARB_texture_non_power_of_two)
		fz_warn(ctx, "OpenGL implementation does not support non-power of two texture sizes");

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);

	ui_scale = 1;
	{
		int wmm = glutGet(GLUT_SCREEN_WIDTH_MM);
		int wpx = glutGet(GLUT_SCREEN_WIDTH);
		int hmm = glutGet(GLUT_SCREEN_HEIGHT_MM);
		int hpx = glutGet(GLUT_SCREEN_HEIGHT);
		if (wmm > 0 && hmm > 0)
		{
			float ppi = ((wpx * 254) / wmm + (hpx * 254) / hmm) / 20;
			if (ppi >= 144) ui_scale = 1.5f;
			if (ppi >= 192) ui_scale = 2.0f;
			if (ppi >= 288) ui_scale = 3.0f;
		}
	}

	ui.fontsize = DEFAULT_UI_FONTSIZE * ui_scale;
	ui.baseline = DEFAULT_UI_BASELINE * ui_scale;
	ui.lineheight = DEFAULT_UI_LINEHEIGHT * ui_scale;
	ui.gridsize = DEFAULT_UI_GRIDSIZE * ui_scale;

	ui_init_fonts();

	ui.overlay_list = glGenLists(1);
}