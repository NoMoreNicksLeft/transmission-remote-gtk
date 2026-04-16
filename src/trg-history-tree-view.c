/*
 * transmission-remote-gtk - A GTK RPC client to Transmission
 * Copyright (C) 2026  John Oyler
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "config.h"

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "trg-client.h"
#include "trg-history-model.h"
#include "trg-history-tree-view.h"
#include "trg-main-window.h"
#include "trg-tree-view.h"

struct _TrgHistoryTreeView {
    TrgTreeView parent;

    TrgClient *client;
    TrgMainWindow *win;
};

G_DEFINE_TYPE(TrgHistoryTreeView, trg_history_tree_view, TRG_TYPE_TREE_VIEW)

static void trg_history_tree_view_class_init(TrgHistoryTreeViewClass *klass)
{
}

static void trg_history_tree_view_init(TrgHistoryTreeView *self)
{
}

TrgHistoryTreeView *trg_history_tree_view_new(gpointer model,
                                               gpointer client,
                                               gpointer win)
{
    TrgClient *tc = TRG_CLIENT(client);
    GObject *obj = g_object_new(TRG_TYPE_HISTORY_TREE_VIEW,
                                "prefs", trg_client_get_prefs(tc),
                                NULL);
    TrgHistoryTreeView *self = TRG_HISTORY_TREE_VIEW(obj);
    TrgTreeView *ttv = TRG_TREE_VIEW(obj);

    self->client = tc;
    self->win = TRG_MAIN_WINDOW(win);

    trg_tree_view_reg_column(ttv, TRG_COLTYPE_NUMGTEQZERO, HISTORYCOL_SEQ,
                             _("Version"), "version", 0);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, HISTORYCOL_ACTIVE,
                             _("Active"), "active", 0);
    trg_tree_view_reg_column(ttv, TRG_COLTYPE_TEXT, HISTORYCOL_HASH,
                             _("Info Hash"), "infohash", 0);

    gtk_tree_view_set_model(GTK_TREE_VIEW(obj), GTK_TREE_MODEL(model));
    trg_tree_view_setup_columns(ttv);

    return self;
}
