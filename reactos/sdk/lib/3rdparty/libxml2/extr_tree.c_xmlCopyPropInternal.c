#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_34__ {TYPE_2__* children; TYPE_3__* doc; TYPE_2__* parent; TYPE_2__* last; TYPE_1__* ns; int /*<<< orphan*/  name; } ;
struct TYPE_33__ {int /*<<< orphan*/ * ids; } ;
struct TYPE_32__ {scalar_t__ type; TYPE_3__* doc; struct TYPE_32__* next; struct TYPE_32__* parent; } ;
struct TYPE_31__ {int /*<<< orphan*/  href; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xmlAddID (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlIsID (TYPE_3__*,TYPE_2__*,TYPE_4__*) ; 
 TYPE_4__* xmlNewDocProp (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* xmlNewNs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xmlNewReconciliedNs (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlNodeListGetString (TYPE_3__*,TYPE_2__*,int) ; 
 TYPE_1__* xmlSearchNs (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlStaticCopyNodeList (TYPE_2__*,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlAttrPtr
xmlCopyPropInternal(xmlDocPtr doc, xmlNodePtr target, xmlAttrPtr cur) {
    xmlAttrPtr ret;

    if (cur == NULL) return(NULL);
    if ((target != NULL) && (target->type != XML_ELEMENT_NODE))
        return(NULL);
    if (target != NULL)
	ret = xmlNewDocProp(target->doc, cur->name, NULL);
    else if (doc != NULL)
	ret = xmlNewDocProp(doc, cur->name, NULL);
    else if (cur->parent != NULL)
	ret = xmlNewDocProp(cur->parent->doc, cur->name, NULL);
    else if (cur->children != NULL)
	ret = xmlNewDocProp(cur->children->doc, cur->name, NULL);
    else
	ret = xmlNewDocProp(NULL, cur->name, NULL);
    if (ret == NULL) return(NULL);
    ret->parent = target;

    if ((cur->ns != NULL) && (target != NULL)) {
      xmlNsPtr ns;

      ns = xmlSearchNs(target->doc, target, cur->ns->prefix);
      if (ns == NULL) {
        /*
         * Humm, we are copying an element whose namespace is defined
         * out of the new tree scope. Search it in the original tree
         * and add it at the top of the new tree
         */
        ns = xmlSearchNs(cur->doc, cur->parent, cur->ns->prefix);
        if (ns != NULL) {
          xmlNodePtr root = target;
          xmlNodePtr pred = NULL;

          while (root->parent != NULL) {
            pred = root;
            root = root->parent;
          }
          if (root == (xmlNodePtr) target->doc) {
            /* correct possibly cycling above the document elt */
            root = pred;
          }
          ret->ns = xmlNewNs(root, ns->href, ns->prefix);
        }
      } else {
        /*
         * we have to find something appropriate here since
         * we cant be sure, that the namespce we found is identified
         * by the prefix
         */
        if (xmlStrEqual(ns->href, cur->ns->href)) {
          /* this is the nice case */
          ret->ns = ns;
        } else {
          /*
           * we are in trouble: we need a new reconcilied namespace.
           * This is expensive
           */
          ret->ns = xmlNewReconciliedNs(target->doc, target, cur->ns);
        }
      }

    } else
        ret->ns = NULL;

    if (cur->children != NULL) {
	xmlNodePtr tmp;

	ret->children = xmlStaticCopyNodeList(cur->children, ret->doc, (xmlNodePtr) ret);
	ret->last = NULL;
	tmp = ret->children;
	while (tmp != NULL) {
	    /* tmp->parent = (xmlNodePtr)ret; */
	    if (tmp->next == NULL)
	        ret->last = tmp;
	    tmp = tmp->next;
	}
    }
    /*
     * Try to handle IDs
     */
    if ((target!= NULL) && (cur!= NULL) &&
	(target->doc != NULL) && (cur->doc != NULL) &&
	(cur->doc->ids != NULL) && (cur->parent != NULL)) {
	if (xmlIsID(cur->doc, cur->parent, cur)) {
	    xmlChar *id;

	    id = xmlNodeListGetString(cur->doc, cur->children, 1);
	    if (id != NULL) {
		xmlAddID(NULL, target->doc, id, ret);
		xmlFree(id);
	    }
	}
    }
    return(ret);
}