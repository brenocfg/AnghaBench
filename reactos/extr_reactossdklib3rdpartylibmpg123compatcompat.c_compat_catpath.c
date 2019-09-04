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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char* compat_catpath(const char *prefix, const char* path)
{
	char *ret = NULL;
#ifdef WANT_WIN32_UNICODE
	wchar_t *wprefix = NULL; /* Wide windows versions of */
	wchar_t *wpath   = NULL; /* input arguments. */
	wchar_t *locwret = NULL; /* Tmp return value from LocalAlloc */
	/*
		This variation of combinepath can work with long and UNC paths, but
		is not officially exposed in any DLLs, It also allocates all its buffers
		internally via LocalAlloc, avoiding buffer overflow problems.
		ThOr: I presume this hack is for supporting pre-8 Windows, as
		from Windows 8 on, this is documented in the API.
	*/
	HRESULT (__stdcall *mypac)( const wchar_t *in, const wchar_t* more
	,	unsigned long flags, wchar_t **out ) = NULL;
	HMODULE pathcch = NULL;

	if(!prefix && !path)
		goto catpath_end;
	wprefix = u2wpath(prefix);
	wpath   = u2wpath(path);
	if((prefix && !wprefix) || (path && !wpath))
		goto catpath_end;

	/* Again: I presume this whole fun is to get at PathAllocCombine
	   even when pathcch.h is not available (like in MinGW32). */
	if( (pathcch = GetModuleHandleA("kernelbase")) )
		mypac = (void *)GetProcAddress(pathcch, "PathAllocCombine");
	if(mypac) /* PATHCCH_ALLOW_LONG_PATH = 1 per API docs */
	{
		debug("Actually calling PathAllocCombine!");
		mypac(wprefix, wpath, 1, &locwret);
	}
	else
	{
		/* Playing safe, if we'd care much about performance, this would be on
		   the stack. */
		locwret = LocalAlloc(LPTR, sizeof(wchar_t)*MAX_PATH);
		if(locwret)
			PathCombineW(locwret, wprefix, wpath);
	}
	ret = w2upath(locwret);

catpath_end:
	LocalFree(locwret);
	free(wprefix);
	free(wpath);
#else
	size_t len, prelen, patlen;

	if(path && path[0] == '/')
		prefix = NULL; /* Absolute path stays as it is. */
	prelen = prefix ? strlen(prefix) : 0;
	patlen = path   ? strlen(path)   : 0;
	/* Concatenate the two, put a / in between if both present. */
	len = ((prefix && path) ? 1 : 0) + prelen + patlen;
	ret = malloc(len+1);
	if(ret)
	{
		size_t off=0;
		memcpy(ret, prefix, prelen);
		if(prefix && path)
			ret[prelen+(off++)] = '/';
		memcpy(ret+prelen+off, path, patlen);
		ret[len] = 0;
	}
#endif
	return ret;
}