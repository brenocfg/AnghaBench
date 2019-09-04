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
typedef  int /*<<< orphan*/  wstrbuf_t ;
typedef  int /*<<< orphan*/  nsIDOMText ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  ELEMENT_NODE 129 
 int /*<<< orphan*/  IID_nsIDOMText ; 
#define  TEXT_NODE 128 
 int /*<<< orphan*/  brW ; 
 int get_node_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrW ; 
 int /*<<< orphan*/  is_elem_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMText_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMText_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wstrbuf_append_len (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  wstrbuf_append_nodetxt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wstrbuf_append_node(wstrbuf_t *buf, nsIDOMNode *node, BOOL ignore_text)
{

    switch(get_node_type(node)) {
    case TEXT_NODE: {
        nsIDOMText *nstext;
        nsAString data_str;
        const PRUnichar *data;

        if(ignore_text)
            break;

        nsIDOMNode_QueryInterface(node, &IID_nsIDOMText, (void**)&nstext);

        nsAString_Init(&data_str, NULL);
        nsIDOMText_GetData(nstext, &data_str);
        nsAString_GetData(&data_str, &data);
        wstrbuf_append_nodetxt(buf, data, strlenW(data));
        nsAString_Finish(&data_str);

        nsIDOMText_Release(nstext);

        break;
    }
    case ELEMENT_NODE:
        if(is_elem_tag(node, brW)) {
            static const WCHAR endlW[] = {'\r','\n'};
            wstrbuf_append_len(buf, endlW, 2);
        }else if(is_elem_tag(node, hrW)) {
            static const WCHAR endl2W[] = {'\r','\n','\r','\n'};
            wstrbuf_append_len(buf, endl2W, 4);
        }
    }
}