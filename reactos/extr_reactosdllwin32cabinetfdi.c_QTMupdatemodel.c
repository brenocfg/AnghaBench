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
struct QTMmodelsym {int cumfreq; size_t sym; } ;
struct QTMmodel {int shiftsleft; int entries; int* tabloc; struct QTMmodelsym* syms; } ;

/* Variables and functions */

__attribute__((used)) static void QTMupdatemodel(struct QTMmodel *model, int sym) {
  struct QTMmodelsym temp;
  int i, j;

  for (i = 0; i < sym; i++) model->syms[i].cumfreq += 8;

  if (model->syms[0].cumfreq > 3800) {
    if (--model->shiftsleft) {
      for (i = model->entries - 1; i >= 0; i--) {
        /* -1, not -2; the 0 entry saves this */
        model->syms[i].cumfreq >>= 1;
        if (model->syms[i].cumfreq <= model->syms[i+1].cumfreq) {
          model->syms[i].cumfreq = model->syms[i+1].cumfreq + 1;
        }
      }
    }
    else {
      model->shiftsleft = 50;
      for (i = 0; i < model->entries ; i++) {
        /* no -1, want to include the 0 entry */
        /* this converts cumfreqs into frequencies, then shifts right */
        model->syms[i].cumfreq -= model->syms[i+1].cumfreq;
        model->syms[i].cumfreq++; /* avoid losing things entirely */
        model->syms[i].cumfreq >>= 1;
      }

      /* now sort by frequencies, decreasing order -- this must be an
       * inplace selection sort, or a sort with the same (in)stability
       * characteristics
       */
      for (i = 0; i < model->entries - 1; i++) {
        for (j = i + 1; j < model->entries; j++) {
          if (model->syms[i].cumfreq < model->syms[j].cumfreq) {
            temp = model->syms[i];
            model->syms[i] = model->syms[j];
            model->syms[j] = temp;
          }
        }
      }

      /* then convert frequencies back to cumfreq */
      for (i = model->entries - 1; i >= 0; i--) {
        model->syms[i].cumfreq += model->syms[i+1].cumfreq;
      }
      /* then update the other part of the table */
      for (i = 0; i < model->entries; i++) {
        model->tabloc[model->syms[i].sym] = i;
      }
    }
  }
}