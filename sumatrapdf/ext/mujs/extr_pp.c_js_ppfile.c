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
typedef  int /*<<< orphan*/  js_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,char*) ; 
 char* js_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_ppstring (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

void js_ppfile(js_State *J, const char *filename, int minify)
{
	FILE *f;
	char *s;
	int n, t;

	f = fopen(filename, "rb");
	if (!f) {
		js_error(J, "cannot open file: '%s'", filename);
	}

	if (fseek(f, 0, SEEK_END) < 0) {
		fclose(f);
		js_error(J, "cannot seek in file: '%s'", filename);
	}

	n = ftell(f);
	if (n < 0) {
		fclose(f);
		js_error(J, "cannot tell in file: '%s'", filename);
	}

	if (fseek(f, 0, SEEK_SET) < 0) {
		fclose(f);
		js_error(J, "cannot seek in file: '%s'", filename);
	}

	s = js_malloc(J, n + 1); /* add space for string terminator */
	if (!s) {
		fclose(f);
		js_error(J, "cannot allocate storage for file contents: '%s'", filename);
	}

	t = fread(s, 1, (size_t)n, f);
	if (t != n) {
		js_free(J, s);
		fclose(f);
		js_error(J, "cannot read data from file: '%s'", filename);
	}

	s[n] = 0; /* zero-terminate string containing file data */

	if (js_try(J)) {
		js_free(J, s);
		fclose(f);
		js_throw(J);
	}

	js_ppstring(J, filename, s, minify);

	js_free(J, s);
	fclose(f);
	js_endtry(J);
}