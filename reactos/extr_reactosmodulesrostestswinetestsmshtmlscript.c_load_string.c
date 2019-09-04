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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IPersistStreamInit ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IPersistStreamInit ; 
 int /*<<< orphan*/  IPersistStreamInit_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStreamInit_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  doc_complete ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void load_string(IHTMLDocument2 *doc, const char *str)
{
    IPersistStreamInit *init;
    IStream *stream;
    HGLOBAL mem;
    SIZE_T len;

    doc_complete = FALSE;
    len = strlen(str);
    mem = GlobalAlloc(0, len);
    memcpy(mem, str, len);
    CreateStreamOnHGlobal(mem, TRUE, &stream);

    IHTMLDocument2_QueryInterface(doc, &IID_IPersistStreamInit, (void**)&init);

    IPersistStreamInit_Load(init, stream);
    IPersistStreamInit_Release(init);
    IStream_Release(stream);
}