// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VIEWS_WIDGET_GTK_VIEWS_FIXED_H_
#define VIEWS_WIDGET_GTK_VIEWS_FIXED_H_

#include <gdk/gdk.h>
#include <gtk/gtkfixed.h>

// GtkViewsFixed is a subclass of GtkFixed that can give child widgets their
// current size rather than their requested size. This behavior is controlled
// by gtk_views_fixed_set_use_allocated_size; the default is to use the
// Widget's requested size.

G_BEGIN_DECLS

#define GTK_TYPE_VIEWS_FIXED        (gtk_views_fixed_get_type ())
#define GTK_VIEWS_FIXED(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_VIEWS_FIXED, GtkViewsFixed))
#define GTK_VIEWS_FIXED_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_VIEWS_FIXED, GtkViewsFixedClass))
#define GTK_IS_VIEWS_FIXED(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VIEWS_FIXED))
#define GTK_IS_VIEWS_FIXED_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VIEWS_FIXED))
#define GTK_VIEWS_FIXED_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VIEWS_FIXED, GtkViewsFixed))

typedef struct _GtkViewsFixed        GtkViewsFixed;
typedef struct _GtkViewsFixedClass   GtkViewsFixedClass;

struct _GtkViewsFixed {
  GtkFixed fixed;
};

struct _GtkViewsFixedClass {
  GtkFixedClass parent_class;
};

GtkWidget* gtk_views_fixed_new();

GType gtk_views_fixed_get_type();

void gtk_views_fixed_set_use_allocated_size(GtkWidget* widget, bool value);

G_END_DECLS

#endif  // VIEWS_WIDGET_GTK_VIEWS_FIXED_H
