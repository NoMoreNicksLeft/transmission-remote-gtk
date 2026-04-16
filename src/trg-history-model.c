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

#include <gtk/gtk.h>
#include <json-glib/json-glib.h>

#include "protocol-constants.h"
#include "torrent.h"
#include "trg-history-model.h"

struct _TrgHistoryModel {
    GtkListStore parent;
};

G_DEFINE_TYPE(TrgHistoryModel, trg_history_model, GTK_TYPE_LIST_STORE)

static void trg_history_model_class_init(TrgHistoryModelClass *klass)
{
}

static void trg_history_model_init(TrgHistoryModel *self)
{
    GType column_types[HISTORYCOL_COLUMNS] = {
        G_TYPE_INT64,   /* HISTORYCOL_SEQ */
        G_TYPE_STRING,  /* HISTORYCOL_HASH */
        G_TYPE_STRING,  /* HISTORYCOL_ACTIVE */
    };

    gtk_list_store_set_column_types(GTK_LIST_STORE(self), HISTORYCOL_COLUMNS, column_types);
}

TrgHistoryModel *trg_history_model_new(void)
{
    return g_object_new(TRG_TYPE_HISTORY_MODEL, NULL);
}

void trg_history_model_update(TrgHistoryModel *model, JsonObject *t)
{
    GtkListStore *store = GTK_LIST_STORE(model);
    GtkTreeIter iter;

    gtk_list_store_clear(store);

    if (!t || !torrent_has_btpk(t))
        return;

    JsonArray *history = torrent_get_btpk_history(t);
    if (!history)
        return;

    guint len = json_array_get_length(history);
    for (guint i = 0; i < len; i++) {
        JsonObject *entry = json_array_get_object_element(history, i);
        if (!entry)
            continue;

        gint64 seq = -1;
        const gchar *hash = NULL;
        const gchar *active_str = NULL;

        if (json_object_has_member(entry, FIELD_BTPK_SEQ))
            seq = json_object_get_int_member(entry, FIELD_BTPK_SEQ);
        if (json_object_has_member(entry, FIELD_HASH_STRING))
            hash = json_object_get_string_member(entry, FIELD_HASH_STRING);
        if (json_object_has_member(entry, "status"))
            active_str = json_object_get_boolean_member(entry, "status") ? "Yes" : "No";
        else
            active_str = "No";

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           HISTORYCOL_SEQ, seq,
                           HISTORYCOL_HASH, hash ? hash : "",
                           HISTORYCOL_ACTIVE, active_str,
                           -1);
    }
}
