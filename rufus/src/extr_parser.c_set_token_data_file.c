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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  bom ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ _wcsnicmp (char*,char*,size_t) ; 
 int /*<<< orphan*/ * _wfopen (char*,char const*) ; 
 int /*<<< orphan*/  _wunlink (char*) ; 
 scalar_t__ calloc (int,int) ; 
 char* conversion_error ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgetws (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputws (char*,int /*<<< orphan*/ *) ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf_s (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  fwrite (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 char* utf8_to_wchar (char const*) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 
 size_t wcslen (char*) ; 
 scalar_t__ wcsspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wspace ; 

char* set_token_data_file(const char* token, const char* data, const char* filename)
{
	const wchar_t* outmode[] = { L"w", L"w, ccs=UTF-8", L"w, ccs=UTF-16LE" };
	wchar_t *wtoken = NULL, *wfilename = NULL, *wtmpname = NULL, *wdata = NULL, bom = 0;
	wchar_t buf[1024];
	FILE *fd_in = NULL, *fd_out = NULL;
	size_t i, size;
	int mode = 0;
	char *ret = NULL, tmp[2];

	if ((filename == NULL) || (token == NULL) || (data == NULL))
		return NULL;
	if ((filename[0] == 0) || (token[0] == 0) || (data[0] == 0))
		return NULL;

	wfilename = utf8_to_wchar(filename);
	if (wfilename == NULL) {
		uprintf(conversion_error, filename);
		goto out;
	}
	wtoken = utf8_to_wchar(token);
	if (wfilename == NULL) {
		uprintf(conversion_error, token);
		goto out;
	}
	wdata = utf8_to_wchar(data);
	if (wdata == NULL) {
		uprintf(conversion_error, data);
		goto out;
	}

	fd_in = _wfopen(wfilename, L"r, ccs=UNICODE");
	if (fd_in == NULL) {
		uprintf("Could not open file '%s'\n", filename);
		goto out;
	}
	// Check the input file's BOM and create an output file with the same
	if (fread(&bom, sizeof(bom), 1, fd_in) == 1) {
		switch(bom) {
		case 0xFEFF:
			mode = 2;	// UTF-16 (LE)
			break;
		case 0xBBEF:	// Yeah, the UTF-8 BOM is really 0xEF,0xBB,0xBF, but
			mode = 1;	// find me a non UTF-8 file that actually begins with "ï»"
			break;
		default:
			mode = 0;	// ANSI
			break;
		}
		fseek(fd_in, 0, SEEK_SET);
	}

	wtmpname = (wchar_t*)calloc(wcslen(wfilename)+2, sizeof(wchar_t));
	if (wtmpname == NULL) {
		uprintf("Could not allocate space for temporary output name\n");
		goto out;
	}
	wcscpy(wtmpname, wfilename);
	wtmpname[wcslen(wtmpname)] = '~';

	fd_out = _wfopen(wtmpname, outmode[mode]);
	if (fd_out == NULL) {
		uprintf("Could not open temporary output file '%s~'\n", filename);
		goto out;
	}

	// Process individual lines. NUL is always appended.
	while (fgetws(buf, ARRAYSIZE(buf), fd_in) != NULL) {

		i = 0;

		// Skip leading spaces
		i += wcsspn(&buf[i], wspace);

		// Ignore comments or section headers
		if ((buf[i] == ';') || (buf[i] == '[')) {
			fputws(buf, fd_out);
			continue;
		}

		// Our token should begin a line
		if (_wcsnicmp(&buf[i], wtoken, wcslen(wtoken)) != 0) {
			fputws(buf, fd_out);
			continue;
		}

		// Token was found, move past token
		i += wcslen(wtoken);

		// Skip spaces
		i += wcsspn(&buf[i], wspace);

		// Check for an equal sign
		if (buf[i] != L'=') {
			fputws(buf, fd_out);
			continue;
		}
		i++;

		// Skip spaces after equal sign
		i += wcsspn(&buf[i], wspace);

		// Output the token
		buf[i] = 0;
		fputws(buf, fd_out);

		// Now output the new data
		// coverity[invalid_type]
		fwprintf_s(fd_out, L"%s\n", wdata);
		ret = (char*)data;
	}

	if (ret == NULL) {
		// Didn't find an existing token => append it
		// coverity[invalid_type]
		fwprintf_s(fd_out, L"%s = %s\n", wtoken, wdata);
		ret = (char*)data;
	}

out:
	if (fd_in != NULL) fclose(fd_in);
	if (fd_out != NULL) fclose(fd_out);

	// If an insertion occurred, delete existing file and use the new one
	if (ret != NULL) {
		// We're in Windows text mode => Remove CRs if requested
		fd_in = _wfopen(wtmpname, L"rb");
		fd_out = _wfopen(wfilename, L"wb");
		// Don't check fds
		if ((fd_in != NULL) && (fd_out != NULL)) {
			size = (mode==2)?2:1;
			while(fread(tmp, size, 1, fd_in) == 1)
				fwrite(tmp, size, 1, fd_out);
			fclose(fd_in);
			fclose(fd_out);
		} else {
			uprintf("Could not write '%s' - original file has been left unmodified\n", filename);
			ret = NULL;
			if (fd_in != NULL) fclose(fd_in);
			if (fd_out != NULL) fclose(fd_out);
		}
	}
	if (wtmpname != NULL)
		_wunlink(wtmpname);
	safe_free(wfilename);
	safe_free(wtmpname);
	safe_free(wtoken);
	safe_free(wdata);

	return ret;
}