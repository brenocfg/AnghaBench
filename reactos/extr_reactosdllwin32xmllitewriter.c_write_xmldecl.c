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
struct TYPE_4__ {int /*<<< orphan*/  output; scalar_t__ omitxmldecl; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ xmlwriter ;
typedef  scalar_t__ XmlStandalone ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ XmlStandalone_Omit ; 
 scalar_t__ XmlStandalone_Yes ; 
 int /*<<< orphan*/  XmlWriterState_DocStarted ; 
 char const* closepiW ; 
 int /*<<< orphan*/  get_output_encoding_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_encoding_bom (TYPE_1__*) ; 
 int /*<<< orphan*/  write_output_buffer (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_output_buffer_quoted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT write_xmldecl(xmlwriter *writer, XmlStandalone standalone)
{
    static const WCHAR versionW[] = {'<','?','x','m','l',' ','v','e','r','s','i','o','n','=','"','1','.','0','"'};
    static const WCHAR encodingW[] = {' ','e','n','c','o','d','i','n','g','='};

    write_encoding_bom(writer);
    writer->state = XmlWriterState_DocStarted;
    if (writer->omitxmldecl) return S_OK;

    /* version */
    write_output_buffer(writer->output, versionW, ARRAY_SIZE(versionW));

    /* encoding */
    write_output_buffer(writer->output, encodingW, ARRAY_SIZE(encodingW));
    write_output_buffer_quoted(writer->output, get_output_encoding_name(writer->output), -1);

    /* standalone */
    if (standalone == XmlStandalone_Omit)
        write_output_buffer(writer->output, closepiW, ARRAY_SIZE(closepiW));
    else {
        static const WCHAR standaloneW[] = {' ','s','t','a','n','d','a','l','o','n','e','=','\"'};
        static const WCHAR yesW[] = {'y','e','s','\"','?','>'};
        static const WCHAR noW[] = {'n','o','\"','?','>'};

        write_output_buffer(writer->output, standaloneW, ARRAY_SIZE(standaloneW));
        if (standalone == XmlStandalone_Yes)
            write_output_buffer(writer->output, yesW, ARRAY_SIZE(yesW));
        else
            write_output_buffer(writer->output, noW, ARRAY_SIZE(noW));
    }

    return S_OK;
}