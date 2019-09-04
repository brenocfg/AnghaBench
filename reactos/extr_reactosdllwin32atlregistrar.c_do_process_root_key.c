#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* str; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ strbuf ;
struct TYPE_8__ {int /*<<< orphan*/  key; int /*<<< orphan*/  name; } ;
typedef  scalar_t__* LPCOLESTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  do_process_key (scalar_t__**,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_word (scalar_t__**,TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* root_keys ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 

__attribute__((used)) static HRESULT do_process_root_key(LPCOLESTR data, BOOL do_register)
{
    LPCOLESTR iter = data;
    strbuf buf;
    HRESULT hres;
    unsigned int i;

    strbuf_init(&buf);
    hres = get_word(&iter, &buf);
    if(FAILED(hres))
        return hres;

    while(*iter) {
        if(!buf.len) {
            WARN("ward.len == 0, failed\n");
            hres = DISP_E_EXCEPTION;
            break;
        }
        for(i=0; i<ARRAY_SIZE(root_keys); i++) {
            if(!lstrcmpiW(buf.str, root_keys[i].name))
                break;
        }
        if(i == ARRAY_SIZE(root_keys)) {
            WARN("Wrong root key name: %s\n", debugstr_w(buf.str));
            hres = DISP_E_EXCEPTION;
            break;
        }
        hres = get_word(&iter, &buf);
        if(FAILED(hres))
            break;
        if(buf.str[1] || buf.str[0] != '{') {
            WARN("Failed, expected '{', got %s\n", debugstr_w(buf.str));
            hres = DISP_E_EXCEPTION;
            break;
        }
        hres = do_process_key(&iter, root_keys[i].key, &buf, do_register);
        if(FAILED(hres)) {
            WARN("Processing key failed: %08x\n", hres);
            break;
        }
        hres = get_word(&iter, &buf);
        if(FAILED(hres))
            break;
    }
    HeapFree(GetProcessHeap(), 0, buf.str);
    return hres;
}