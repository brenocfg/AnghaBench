#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sequence {int length; double min; double max; int /*<<< orphan*/  labels; TYPE_1__* samples; } ;
struct sample {int dummy; } ;
struct TYPE_3__ {double value; char* label; } ;

/* Variables and functions */
 TYPE_1__* zrealloc (TYPE_1__*,int) ; 
 char* zstrdup (char*) ; 

void sparklineSequenceAddSample(struct sequence *seq, double value, char *label) {
    label = (label == NULL || label[0] == '\0') ? NULL : zstrdup(label);
    if (seq->length == 0) {
        seq->min = seq->max = value;
    } else {
        if (value < seq->min) seq->min = value;
        else if (value > seq->max) seq->max = value;
    }
    seq->samples = zrealloc(seq->samples,sizeof(struct sample)*(seq->length+1));
    seq->samples[seq->length].value = value;
    seq->samples[seq->length].label = label;
    seq->length++;
    if (label) seq->labels++;
}