#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  TYPE_4__* xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_12__ {scalar_t__ etype; int checked; scalar_t__* content; } ;
struct TYPE_10__ {scalar_t__ code; } ;
struct TYPE_11__ {int options; scalar_t__ errNo; unsigned long nbentities; TYPE_2__ lastError; scalar_t__ sizeentities; TYPE_1__* input; int /*<<< orphan*/  depth; } ;
struct TYPE_9__ {size_t consumed; size_t cur; size_t base; } ;

/* Variables and functions */
 scalar_t__ XML_ERR_ENTITY_LOOP ; 
 scalar_t__ XML_ERR_UNDECLARED_ENTITY ; 
 scalar_t__ XML_INTERNAL_PREDEFINED_ENTITY ; 
 size_t XML_MAX_TEXT_LENGTH ; 
 size_t XML_PARSER_BIG_ENTITY ; 
 size_t XML_PARSER_NON_LINEAR ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  XML_SUBSTITUTE_REF ; 
 scalar_t__ XML_WAR_UNDECLARED_ENTITY ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * xmlStringDecodeEntities (TYPE_3__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xmlParserEntityCheck(xmlParserCtxtPtr ctxt, size_t size,
                     xmlEntityPtr ent, size_t replacement)
{
    size_t consumed = 0;

    if ((ctxt == NULL) || (ctxt->options & XML_PARSE_HUGE))
        return (0);
    if (ctxt->lastError.code == XML_ERR_ENTITY_LOOP)
        return (1);

    /*
     * This may look absurd but is needed to detect
     * entities problems
     */
    if ((ent != NULL) && (ent->etype != XML_INTERNAL_PREDEFINED_ENTITY) &&
	(ent->content != NULL) && (ent->checked == 0) &&
	(ctxt->errNo != XML_ERR_ENTITY_LOOP)) {
	unsigned long oldnbent = ctxt->nbentities;
	xmlChar *rep;

	ent->checked = 1;

        ++ctxt->depth;
	rep = xmlStringDecodeEntities(ctxt, ent->content,
				  XML_SUBSTITUTE_REF, 0, 0, 0);
        --ctxt->depth;
	if ((rep == NULL) || (ctxt->errNo == XML_ERR_ENTITY_LOOP)) {
	    ent->content[0] = 0;
	}

	ent->checked = (ctxt->nbentities - oldnbent + 1) * 2;
	if (rep != NULL) {
	    if (xmlStrchr(rep, '<'))
		ent->checked |= 1;
	    xmlFree(rep);
	    rep = NULL;
	}
    }
    if (replacement != 0) {
	if (replacement < XML_MAX_TEXT_LENGTH)
	    return(0);

        /*
	 * If the volume of entity copy reaches 10 times the
	 * amount of parsed data and over the large text threshold
	 * then that's very likely to be an abuse.
	 */
        if (ctxt->input != NULL) {
	    consumed = ctxt->input->consumed +
	               (ctxt->input->cur - ctxt->input->base);
	}
        consumed += ctxt->sizeentities;

        if (replacement < XML_PARSER_NON_LINEAR * consumed)
	    return(0);
    } else if (size != 0) {
        /*
         * Do the check based on the replacement size of the entity
         */
        if (size < XML_PARSER_BIG_ENTITY)
	    return(0);

        /*
         * A limit on the amount of text data reasonably used
         */
        if (ctxt->input != NULL) {
            consumed = ctxt->input->consumed +
                (ctxt->input->cur - ctxt->input->base);
        }
        consumed += ctxt->sizeentities;

        if ((size < XML_PARSER_NON_LINEAR * consumed) &&
	    (ctxt->nbentities * 3 < XML_PARSER_NON_LINEAR * consumed))
            return (0);
    } else if (ent != NULL) {
        /*
         * use the number of parsed entities in the replacement
         */
        size = ent->checked / 2;

        /*
         * The amount of data parsed counting entities size only once
         */
        if (ctxt->input != NULL) {
            consumed = ctxt->input->consumed +
                (ctxt->input->cur - ctxt->input->base);
        }
        consumed += ctxt->sizeentities;

        /*
         * Check the density of entities for the amount of data
	 * knowing an entity reference will take at least 3 bytes
         */
        if (size * 3 < consumed * XML_PARSER_NON_LINEAR)
            return (0);
    } else {
        /*
         * strange we got no data for checking
         */
	if (((ctxt->lastError.code != XML_ERR_UNDECLARED_ENTITY) &&
	     (ctxt->lastError.code != XML_WAR_UNDECLARED_ENTITY)) ||
	    (ctxt->nbentities <= 10000))
	    return (0);
    }
    xmlFatalErr(ctxt, XML_ERR_ENTITY_LOOP, NULL);
    return (1);
}