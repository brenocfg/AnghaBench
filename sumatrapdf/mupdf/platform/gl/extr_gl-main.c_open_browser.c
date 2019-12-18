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

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  ShellExecuteA (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlp (char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fz_cleanname (char*) ; 
 int /*<<< orphan*/  fz_dirname (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static void open_browser(const char *uri)
{
	char buf[PATH_MAX];

	/* Relative file:// URI, make it absolute! */
	if (!strncmp(uri, "file://", 7) && uri[7] != '/')
	{
		char buf_base[PATH_MAX];
		char buf_cwd[PATH_MAX];
		fz_dirname(buf_base, filename, sizeof buf_base);
		getcwd(buf_cwd, sizeof buf_cwd);
		fz_snprintf(buf, sizeof buf, "file://%s/%s/%s", buf_cwd, buf_base, uri+7);
		fz_cleanname(buf+7);
		uri = buf;
	}

#ifdef _WIN32
	ShellExecuteA(NULL, "open", uri, 0, 0, SW_SHOWNORMAL);
#else
	const char *browser = getenv("BROWSER");
	if (!browser)
	{
#ifdef __APPLE__
		browser = "open";
#else
		browser = "xdg-open";
#endif
	}
	if (fork() == 0)
	{
		execlp(browser, browser, uri, (char*)0);
		fprintf(stderr, "cannot exec '%s'\n", browser);
		exit(0);
	}
#endif
}