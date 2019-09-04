#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wine_schemaW ;
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ ScriptHost ;
typedef  int LPCWSTR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HTMLScriptElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bind_script_to_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  create_uri (int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  memcmp (int,char const*,int) ; 
 int /*<<< orphan*/  parse_elem_text (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int strlenW (int) ; 

__attribute__((used)) static void parse_extern_script(ScriptHost *script_host, HTMLScriptElement *script_elem, LPCWSTR src)
{
    WCHAR *text;
    IUri *uri;
    HRESULT hres;

    static const WCHAR wine_schemaW[] = {'w','i','n','e',':'};

    if(strlenW(src) > sizeof(wine_schemaW)/sizeof(WCHAR) && !memcmp(src, wine_schemaW, sizeof(wine_schemaW)))
        src += sizeof(wine_schemaW)/sizeof(WCHAR);

    hres = create_uri(src, 0, &uri);
    if(FAILED(hres))
        return;

    hres = bind_script_to_text(script_host->window, uri, script_elem, &text);
    IUri_Release(uri);
    if(FAILED(hres) || !text)
        return;

    parse_elem_text(script_host, script_elem, text);

    heap_free(text);
}