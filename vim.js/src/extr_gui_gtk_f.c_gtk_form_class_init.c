#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  forall; int /*<<< orphan*/  remove; } ;
struct TYPE_3__ {int /*<<< orphan*/  expose_event; int /*<<< orphan*/  size_allocate; int /*<<< orphan*/  size_request; int /*<<< orphan*/  map; int /*<<< orphan*/  unrealize; int /*<<< orphan*/  realize; } ;
typedef  TYPE_1__ GtkWidgetClass ;
typedef  int /*<<< orphan*/  GtkFormClass ;
typedef  TYPE_2__ GtkContainerClass ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_container_get_type () ; 
 int /*<<< orphan*/  gtk_form_expose ; 
 int /*<<< orphan*/  gtk_form_forall ; 
 int /*<<< orphan*/  gtk_form_map ; 
 int /*<<< orphan*/  gtk_form_realize ; 
 int /*<<< orphan*/  gtk_form_remove ; 
 int /*<<< orphan*/  gtk_form_size_allocate ; 
 int /*<<< orphan*/  gtk_form_size_request ; 
 int /*<<< orphan*/  gtk_form_unrealize ; 
 int /*<<< orphan*/  gtk_type_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_class ; 

__attribute__((used)) static void
gtk_form_class_init(GtkFormClass *klass)
{
    GtkWidgetClass *widget_class;
    GtkContainerClass *container_class;

    widget_class = (GtkWidgetClass *) klass;
    container_class = (GtkContainerClass *) klass;

    parent_class = gtk_type_class(gtk_container_get_type());

    widget_class->realize = gtk_form_realize;
    widget_class->unrealize = gtk_form_unrealize;
    widget_class->map = gtk_form_map;
    widget_class->size_request = gtk_form_size_request;
    widget_class->size_allocate = gtk_form_size_allocate;
    widget_class->expose_event = gtk_form_expose;

    container_class->remove = gtk_form_remove;
    container_class->forall = gtk_form_forall;
}