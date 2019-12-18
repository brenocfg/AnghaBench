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
struct event_base {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_set (struct event_base*,struct event*) ; 
 int /*<<< orphan*/  event_set (struct event*,int,int,void (*) (int,short,void*),void*) ; 
 struct event* malloc (int) ; 

__attribute__((used)) static inline struct event *event_new (struct event_base *base, int fd, int what, void(*callback)(int, short, void *), void *arg) {
  struct event *ev = malloc (sizeof (*ev));  
  event_set (ev, fd, what, callback, arg);
  event_base_set (base, ev);
  return ev;
}