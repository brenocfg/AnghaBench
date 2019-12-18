#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xmlParserErrors ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlDocPtr ;
typedef  int /*<<< orphan*/ * xmlCharEncodingHandlerPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_30__ {int const type; int /*<<< orphan*/ * dict; int /*<<< orphan*/ * encoding; } ;
struct TYPE_29__ {int type; struct TYPE_29__* next; struct TYPE_29__* parent; int /*<<< orphan*/ * prev; struct TYPE_29__* last; TYPE_2__* nsDef; TYPE_4__* doc; } ;
struct TYPE_28__ {struct TYPE_28__* next; int /*<<< orphan*/ * href; int /*<<< orphan*/ * prefix; } ;
struct TYPE_27__ {int input_id; scalar_t__ replaceEntities; scalar_t__ errNo; int /*<<< orphan*/ * dict; scalar_t__ wellFormed; TYPE_3__* node; int /*<<< orphan*/  loadsubset; scalar_t__ validate; int /*<<< orphan*/  instate; TYPE_4__* myDoc; int /*<<< orphan*/ * encoding; } ;

/* Variables and functions */
 int HTML_PARSE_NOIMPLIED ; 
 char NXT (int) ; 
 char RAW ; 
#define  XML_ATTRIBUTE_NODE 136 
#define  XML_CDATA_SECTION_NODE 135 
#define  XML_COMMENT_NODE 134 
#define  XML_DOCUMENT_NODE 133 
#define  XML_ELEMENT_NODE 132 
#define  XML_ENTITY_REF_NODE 131 
 int /*<<< orphan*/  XML_ERR_EXTRA_CONTENT ; 
 scalar_t__ XML_ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  XML_ERR_NOT_WELL_BALANCED ; 
 scalar_t__ XML_ERR_NO_MEMORY ; 
 scalar_t__ XML_ERR_OK ; 
 scalar_t__ XML_ERR_UNSUPPORTED_ENCODING ; 
#define  XML_HTML_DOCUMENT_NODE 130 
 int /*<<< orphan*/  XML_PARSER_CONTENT ; 
 int XML_PARSE_NODICT ; 
#define  XML_PI_NODE 129 
 int /*<<< orphan*/  XML_SKIP_IDS ; 
#define  XML_TEXT_NODE 128 
 int /*<<< orphan*/  __htmlParseContent (TYPE_1__*) ; 
 TYPE_1__* htmlCreateMemoryParserCtxt (char*,int) ; 
 int /*<<< orphan*/  nodePush (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  nsPop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nsPush (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlAddChild (TYPE_3__*,TYPE_3__*) ; 
 TYPE_1__* xmlCreateMemoryParserCtxt (char*,int) ; 
 int /*<<< orphan*/  xmlCtxtUseOptionsInternal (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlDetectSAX2 (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlDictFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlDictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlFindCharEncodingHandler (char const*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlFreeNodeList (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlGetNamespace (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 TYPE_3__* xmlNewComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlParseContent (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlSwitchToEncoding (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_3__*) ; 

xmlParserErrors
xmlParseInNodeContext(xmlNodePtr node, const char *data, int datalen,
                      int options, xmlNodePtr *lst) {
#ifdef SAX2
    xmlParserCtxtPtr ctxt;
    xmlDocPtr doc = NULL;
    xmlNodePtr fake, cur;
    int nsnr = 0;

    xmlParserErrors ret = XML_ERR_OK;

    /*
     * check all input parameters, grab the document
     */
    if ((lst == NULL) || (node == NULL) || (data == NULL) || (datalen < 0))
        return(XML_ERR_INTERNAL_ERROR);
    switch (node->type) {
        case XML_ELEMENT_NODE:
        case XML_ATTRIBUTE_NODE:
        case XML_TEXT_NODE:
        case XML_CDATA_SECTION_NODE:
        case XML_ENTITY_REF_NODE:
        case XML_PI_NODE:
        case XML_COMMENT_NODE:
        case XML_DOCUMENT_NODE:
        case XML_HTML_DOCUMENT_NODE:
	    break;
	default:
	    return(XML_ERR_INTERNAL_ERROR);

    }
    while ((node != NULL) && (node->type != XML_ELEMENT_NODE) &&
           (node->type != XML_DOCUMENT_NODE) &&
	   (node->type != XML_HTML_DOCUMENT_NODE))
	node = node->parent;
    if (node == NULL)
	return(XML_ERR_INTERNAL_ERROR);
    if (node->type == XML_ELEMENT_NODE)
	doc = node->doc;
    else
        doc = (xmlDocPtr) node;
    if (doc == NULL)
	return(XML_ERR_INTERNAL_ERROR);

    /*
     * allocate a context and set-up everything not related to the
     * node position in the tree
     */
    if (doc->type == XML_DOCUMENT_NODE)
	ctxt = xmlCreateMemoryParserCtxt((char *) data, datalen);
#ifdef LIBXML_HTML_ENABLED
    else if (doc->type == XML_HTML_DOCUMENT_NODE) {
	ctxt = htmlCreateMemoryParserCtxt((char *) data, datalen);
        /*
         * When parsing in context, it makes no sense to add implied
         * elements like html/body/etc...
         */
        options |= HTML_PARSE_NOIMPLIED;
    }
#endif
    else
        return(XML_ERR_INTERNAL_ERROR);

    if (ctxt == NULL)
        return(XML_ERR_NO_MEMORY);

    /*
     * Use input doc's dict if present, else assure XML_PARSE_NODICT is set.
     * We need a dictionary for xmlDetectSAX2, so if there's no doc dict
     * we must wait until the last moment to free the original one.
     */
    if (doc->dict != NULL) {
        if (ctxt->dict != NULL)
	    xmlDictFree(ctxt->dict);
	ctxt->dict = doc->dict;
    } else
        options |= XML_PARSE_NODICT;

    if (doc->encoding != NULL) {
        xmlCharEncodingHandlerPtr hdlr;

        if (ctxt->encoding != NULL)
	    xmlFree((xmlChar *) ctxt->encoding);
        ctxt->encoding = xmlStrdup((const xmlChar *) doc->encoding);

        hdlr = xmlFindCharEncodingHandler((const char *) doc->encoding);
        if (hdlr != NULL) {
            xmlSwitchToEncoding(ctxt, hdlr);
	} else {
            return(XML_ERR_UNSUPPORTED_ENCODING);
        }
    }

    xmlCtxtUseOptionsInternal(ctxt, options, NULL);
    xmlDetectSAX2(ctxt);
    ctxt->myDoc = doc;
    /* parsing in context, i.e. as within existing content */
    ctxt->input_id = 2;
    ctxt->instate = XML_PARSER_CONTENT;

    fake = xmlNewComment(NULL);
    if (fake == NULL) {
        xmlFreeParserCtxt(ctxt);
	return(XML_ERR_NO_MEMORY);
    }
    xmlAddChild(node, fake);

    if (node->type == XML_ELEMENT_NODE) {
	nodePush(ctxt, node);
	/*
	 * initialize the SAX2 namespaces stack
	 */
	cur = node;
	while ((cur != NULL) && (cur->type == XML_ELEMENT_NODE)) {
	    xmlNsPtr ns = cur->nsDef;
	    const xmlChar *iprefix, *ihref;

	    while (ns != NULL) {
		if (ctxt->dict) {
		    iprefix = xmlDictLookup(ctxt->dict, ns->prefix, -1);
		    ihref = xmlDictLookup(ctxt->dict, ns->href, -1);
		} else {
		    iprefix = ns->prefix;
		    ihref = ns->href;
		}

	        if (xmlGetNamespace(ctxt, iprefix) == NULL) {
		    nsPush(ctxt, iprefix, ihref);
		    nsnr++;
		}
		ns = ns->next;
	    }
	    cur = cur->parent;
	}
    }

    if ((ctxt->validate) || (ctxt->replaceEntities != 0)) {
	/*
	 * ID/IDREF registration will be done in xmlValidateElement below
	 */
	ctxt->loadsubset |= XML_SKIP_IDS;
    }

#ifdef LIBXML_HTML_ENABLED
    if (doc->type == XML_HTML_DOCUMENT_NODE)
        __htmlParseContent(ctxt);
    else
#endif
	xmlParseContent(ctxt);

    nsPop(ctxt, nsnr);
    if ((RAW == '<') && (NXT(1) == '/')) {
	xmlFatalErr(ctxt, XML_ERR_NOT_WELL_BALANCED, NULL);
    } else if (RAW != 0) {
	xmlFatalErr(ctxt, XML_ERR_EXTRA_CONTENT, NULL);
    }
    if ((ctxt->node != NULL) && (ctxt->node != node)) {
	xmlFatalErr(ctxt, XML_ERR_NOT_WELL_BALANCED, NULL);
	ctxt->wellFormed = 0;
    }

    if (!ctxt->wellFormed) {
        if (ctxt->errNo == 0)
	    ret = XML_ERR_INTERNAL_ERROR;
	else
	    ret = (xmlParserErrors)ctxt->errNo;
    } else {
        ret = XML_ERR_OK;
    }

    /*
     * Return the newly created nodeset after unlinking it from
     * the pseudo sibling.
     */

    cur = fake->next;
    fake->next = NULL;
    node->last = fake;

    if (cur != NULL) {
	cur->prev = NULL;
    }

    *lst = cur;

    while (cur != NULL) {
	cur->parent = NULL;
	cur = cur->next;
    }

    xmlUnlinkNode(fake);
    xmlFreeNode(fake);


    if (ret != XML_ERR_OK) {
        xmlFreeNodeList(*lst);
	*lst = NULL;
    }

    if (doc->dict != NULL)
        ctxt->dict = NULL;
    xmlFreeParserCtxt(ctxt);

    return(ret);
#else /* !SAX2 */
    return(XML_ERR_INTERNAL_ERROR);
#endif
}