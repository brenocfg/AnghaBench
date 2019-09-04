#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ver ;
typedef  int /*<<< orphan*/  entry ;
typedef  int WORD ;
typedef  char WCHAR ;
struct TYPE_3__ {char* defToc; char* defTopic; char* defTitle; char* compiledFile; void* defWindow; int /*<<< orphan*/  codePage; int /*<<< orphan*/  pStorage; } ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  char DWORD ;
typedef  TYPE_1__ CHMInfo ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ IStorage_OpenStream (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int LOCALE_IDEFAULTANSICODEPAGE ; 
 int LOCALE_RETURN_NUMBER ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_an (char*,int) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_realloc (char*,char) ; 
 void* strdupnAtoW (char*,int) ; 

__attribute__((used)) static BOOL ReadChmSystem(CHMInfo *chm)
{
    IStream *stream;
    DWORD ver=0xdeadbeef, read, buf_size;
    char *buf;
    HRESULT hres;

    struct {
        WORD code;
        WORD len;
    } entry;

    static const WCHAR wszSYSTEM[] = {'#','S','Y','S','T','E','M',0};

    hres = IStorage_OpenStream(chm->pStorage, wszSYSTEM, NULL, STGM_READ, 0, &stream);
    if(FAILED(hres)) {
        WARN("Could not open #SYSTEM stream: %08x\n", hres);
        return FALSE;
    }

    IStream_Read(stream, &ver, sizeof(ver), &read);
    TRACE("version is %x\n", ver);

    buf = heap_alloc(8*sizeof(DWORD));
    buf_size = 8*sizeof(DWORD);

    while(1) {
        hres = IStream_Read(stream, &entry, sizeof(entry), &read);
        if(hres != S_OK)
            break;

        if(entry.len > buf_size)
            buf = heap_realloc(buf, buf_size=entry.len);

        hres = IStream_Read(stream, buf, entry.len, &read);
        if(hres != S_OK)
            break;

        switch(entry.code) {
        case 0x0:
            TRACE("TOC is %s\n", debugstr_an(buf, entry.len));
            heap_free(chm->defToc);
            chm->defToc = strdupnAtoW(buf, entry.len);
            break;
        case 0x2:
            TRACE("Default topic is %s\n", debugstr_an(buf, entry.len));
            heap_free(chm->defTopic);
            chm->defTopic = strdupnAtoW(buf, entry.len);
            break;
        case 0x3:
            TRACE("Title is %s\n", debugstr_an(buf, entry.len));
            heap_free(chm->defTitle);
            chm->defTitle = strdupnAtoW(buf, entry.len);
            break;
        case 0x4:
            /* TODO: Currently only the Locale ID is loaded from this field */
            TRACE("Locale is: %d\n", *(LCID*)&buf[0]);
            if(!GetLocaleInfoW(*(LCID*)&buf[0], LOCALE_IDEFAULTANSICODEPAGE|LOCALE_RETURN_NUMBER,
                               (WCHAR *)&chm->codePage, sizeof(chm->codePage)/sizeof(WCHAR)))
                chm->codePage = CP_ACP;
            break;
        case 0x5:
            TRACE("Window name is %s\n", debugstr_an(buf, entry.len));
            chm->defWindow = strdupnAtoW(buf, entry.len);
            break;
        case 0x6:
            TRACE("Compiled file is %s\n", debugstr_an(buf, entry.len));
            heap_free(chm->compiledFile);
            chm->compiledFile = strdupnAtoW(buf, entry.len);
            break;
        case 0x9:
            TRACE("Version is %s\n", debugstr_an(buf, entry.len));
            break;
        case 0xa:
            TRACE("Time is %08x\n", *(DWORD*)buf);
            break;
        case 0xc:
            TRACE("Number of info types: %d\n", *(DWORD*)buf);
            break;
        case 0xf:
            TRACE("Check sum: %x\n", *(DWORD*)buf);
            break;
        default:
            TRACE("unhandled code %x, size %x\n", entry.code, entry.len);
        }
    }

    heap_free(buf);
    IStream_Release(stream);

    return SUCCEEDED(hres);
}