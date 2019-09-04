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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ GetPrivateProfileString (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fwrite (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_ini_file ; 
 void* http_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wprintf (char*) ; 

__attribute__((used)) static void do_update_base()
{
	wchar_t up_url[MAX_PATH];
	void   *data = NULL;
	u_long  size;
	FILE   *f;

	if (GetPrivateProfileString(L"URL", L"udpate", NULL, up_url, MAX_PATH, gl_ini_file) == 0) {
		wprintf(L"Update URL not found in rosddt.ini\n"); return;
	}

	wprintf(L"Downloading new rosddt.ini...\n");

	if (data == http_get(up_url, &size)) 
	{
		f = _wfopen(gl_ini_file, L"wb");
		if (f) {
			fwrite(data, 1, size, f);
			fclose(f);
			wprintf(L"Update completed\n");
		} else {
			wprintf(L"Can not open rosddt.ini for writing\n"); 
		}
		free(data);
	} else {
		wprintf(L"Error, rosddt.ini can not be loaded\n");
	}
}