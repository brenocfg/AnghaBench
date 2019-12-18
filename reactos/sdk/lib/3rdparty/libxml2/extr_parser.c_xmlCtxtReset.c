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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlDictPtr ;
struct TYPE_8__ {scalar_t__ code; } ;
struct TYPE_6__ {int /*<<< orphan*/  warning; int /*<<< orphan*/  error; TYPE_2__* userData; } ;
struct TYPE_7__ {int* spaceTab; int* space; int standalone; int wellFormed; int nsWellFormed; int valid; TYPE_3__ lastError; int /*<<< orphan*/ * catalogs; int /*<<< orphan*/ * attsSpecial; int /*<<< orphan*/ * attsDefault; int /*<<< orphan*/  node_seq; scalar_t__ sizeentcopy; scalar_t__ sizeentities; scalar_t__ nbentities; int /*<<< orphan*/  charset; scalar_t__ depth; scalar_t__ errNo; scalar_t__ inSubset; scalar_t__ checkIndex; scalar_t__ nbChars; scalar_t__ record_info; TYPE_1__ vctxt; scalar_t__ disableSAX; scalar_t__ token; int /*<<< orphan*/  instate; scalar_t__ external; scalar_t__ html; scalar_t__ hasPErefs; scalar_t__ hasExternalSubset; int /*<<< orphan*/ * myDoc; int /*<<< orphan*/ * extSubSystem; int /*<<< orphan*/ * extSubURI; int /*<<< orphan*/ * directory; int /*<<< orphan*/ * encoding; int /*<<< orphan*/ * version; int /*<<< orphan*/ * name; scalar_t__ nameNr; int /*<<< orphan*/ * node; scalar_t__ nodeNr; scalar_t__ spaceNr; int /*<<< orphan*/ * input; scalar_t__ inputNr; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  DICT_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XML_CHAR_ENCODING_UTF8 ; 
 scalar_t__ XML_ERR_OK ; 
 int /*<<< orphan*/  XML_PARSER_START ; 
 int /*<<< orphan*/ * inputPop (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlCatalogFreeLocal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeInputStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlHashDefaultDeallocator ; 
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlInitNodeInfoSeq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlParserValidityError ; 
 int /*<<< orphan*/  xmlParserValidityWarning ; 
 int /*<<< orphan*/  xmlResetError (TYPE_3__*) ; 

void
xmlCtxtReset(xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr input;
    xmlDictPtr dict;

    if (ctxt == NULL)
        return;

    dict = ctxt->dict;

    while ((input = inputPop(ctxt)) != NULL) { /* Non consuming */
        xmlFreeInputStream(input);
    }
    ctxt->inputNr = 0;
    ctxt->input = NULL;

    ctxt->spaceNr = 0;
    if (ctxt->spaceTab != NULL) {
	ctxt->spaceTab[0] = -1;
	ctxt->space = &ctxt->spaceTab[0];
    } else {
        ctxt->space = NULL;
    }


    ctxt->nodeNr = 0;
    ctxt->node = NULL;

    ctxt->nameNr = 0;
    ctxt->name = NULL;

    DICT_FREE(ctxt->version);
    ctxt->version = NULL;
    DICT_FREE(ctxt->encoding);
    ctxt->encoding = NULL;
    DICT_FREE(ctxt->directory);
    ctxt->directory = NULL;
    DICT_FREE(ctxt->extSubURI);
    ctxt->extSubURI = NULL;
    DICT_FREE(ctxt->extSubSystem);
    ctxt->extSubSystem = NULL;
    if (ctxt->myDoc != NULL)
        xmlFreeDoc(ctxt->myDoc);
    ctxt->myDoc = NULL;

    ctxt->standalone = -1;
    ctxt->hasExternalSubset = 0;
    ctxt->hasPErefs = 0;
    ctxt->html = 0;
    ctxt->external = 0;
    ctxt->instate = XML_PARSER_START;
    ctxt->token = 0;

    ctxt->wellFormed = 1;
    ctxt->nsWellFormed = 1;
    ctxt->disableSAX = 0;
    ctxt->valid = 1;
#if 0
    ctxt->vctxt.userData = ctxt;
    ctxt->vctxt.error = xmlParserValidityError;
    ctxt->vctxt.warning = xmlParserValidityWarning;
#endif
    ctxt->record_info = 0;
    ctxt->nbChars = 0;
    ctxt->checkIndex = 0;
    ctxt->inSubset = 0;
    ctxt->errNo = XML_ERR_OK;
    ctxt->depth = 0;
    ctxt->charset = XML_CHAR_ENCODING_UTF8;
    ctxt->catalogs = NULL;
    ctxt->nbentities = 0;
    ctxt->sizeentities = 0;
    ctxt->sizeentcopy = 0;
    xmlInitNodeInfoSeq(&ctxt->node_seq);

    if (ctxt->attsDefault != NULL) {
        xmlHashFree(ctxt->attsDefault, xmlHashDefaultDeallocator);
        ctxt->attsDefault = NULL;
    }
    if (ctxt->attsSpecial != NULL) {
        xmlHashFree(ctxt->attsSpecial, NULL);
        ctxt->attsSpecial = NULL;
    }

#ifdef LIBXML_CATALOG_ENABLED
    if (ctxt->catalogs != NULL)
	xmlCatalogFreeLocal(ctxt->catalogs);
#endif
    if (ctxt->lastError.code != XML_ERR_OK)
        xmlResetError(&ctxt->lastError);
}