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
struct TYPE_2__ {int /*<<< orphan*/ * hlibiconv; } ;
typedef  TYPE_1__ rec_iconv_t ;
typedef  int /*<<< orphan*/  outbuf ;
typedef  scalar_t__ iconv_t ;
typedef  int /*<<< orphan*/  dllpath ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int _MAX_PATH ; 
 int errno ; 
 char* errstr (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t iconv (scalar_t__,char const**,size_t*,char**,size_t*) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* tohex (char const*,int) ; 
 scalar_t__ use_dll ; 

void
test(const char *from, const char *fromstr, int fromsize, const char *to, const char *tostr, int tosize, int errcode, int bufsize, int line)
{
    char outbuf[BUFSIZ];
    const char *pin;
    char *pout;
    size_t inbytesleft;
    size_t outbytesleft;
    iconv_t cd;
    size_t r;
#ifdef USE_LIBICONV_DLL
    char dllpath[_MAX_PATH];
#endif

    cd = iconv_open(to, from);
    if (cd == (iconv_t)(-1))
    {
        printf("%s -> %s: NG: INVALID ENCODING NAME: line=%d\n", from, to, line);
        exit(1);
    }

#ifdef USE_LIBICONV_DLL
    if (((rec_iconv_t *)cd)->hlibiconv != NULL)
        GetModuleFileNameA(((rec_iconv_t *)cd)->hlibiconv, dllpath, sizeof(dllpath));

    if (use_dll && ((rec_iconv_t *)cd)->hlibiconv == NULL)
    {
        printf("%s: %s -> %s: NG: FAILED TO USE DLL: line=%d\n", dllpath, from, to, line);
        exit(1);
    }
    else if (!use_dll && ((rec_iconv_t *)cd)->hlibiconv != NULL)
    {
        printf("%s: %s -> %s: NG: DLL IS LOADED UNEXPECTEDLY: line=%d\n", dllpath, from, to, line);
        exit(1);
    }
#endif

    errno = 0;

    pin = (char *)fromstr;
    pout = outbuf;
    inbytesleft = fromsize;
    outbytesleft = bufsize;
    r = iconv(cd, &pin, &inbytesleft, &pout, &outbytesleft);
    if (r != (size_t)(-1))
        r = iconv(cd, NULL, NULL, &pout, &outbytesleft);
    *pout = 0;

#ifdef USE_LIBICONV_DLL
    if (use_dll)
        printf("%s: ", dllpath);
#endif
    printf("%s(%s) -> ", from, tohex(fromstr, fromsize));
    printf("%s(%s%s%s): ", to, tohex(tostr, tosize),
            errcode == 0 ? "" : ":",
            errcode == 0 ? "" : errstr(errcode));
    if (strcmp(outbuf, tostr) == 0 && errno == errcode)
        printf("OK\n");
    else
    {
        printf("RESULT(%s:%s): ", tohex(outbuf, sizeof(outbuf) - outbytesleft),
                errstr(errno));
        printf("NG: line=%d\n", line);
        exit(1);
    }
}