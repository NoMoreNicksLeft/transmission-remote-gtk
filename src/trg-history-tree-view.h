/*
 * transmission-remote-gtk - A GTK RPC client to Transmission
 * Copyright (C) 2026  John Oyler
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

#define TRG_TYPE_HISTORY_TREE_VIEW trg_history_tree_view_get_type()
G_DECLARE_FINAL_TYPE(TrgHistoryTreeView, trg_history_tree_view, TRG, HISTORY_TREE_VIEW, GtkTreeView)

TrgHistoryTreeView *trg_history_tree_view_new(gpointer model,
                                               gpointer client,
                                               gpointer win);
