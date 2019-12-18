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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  MessageBoxA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_error(const char *fmt, va_list ap)
{
#ifdef _WIN32
	char buf[1000];
	fz_vsnprintf(buf, sizeof buf, fmt, ap);
	MessageBoxA(NULL, buf, "MuPDF GLUT Error", MB_ICONERROR);
#else
	fprintf(stderr, "GLUT error: ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
#endif
}