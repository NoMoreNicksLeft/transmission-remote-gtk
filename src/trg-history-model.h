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
#include <json-glib/json-glib.h>

enum {
    HISTORYCOL_SEQ,
    HISTORYCOL_HASH,
    HISTORYCOL_ACTIVE,  /* G_TYPE_STRING: "Yes" or "No" */
    HISTORYCOL_COLUMNS
};

#define TRG_TYPE_HISTORY_MODEL trg_history_model_get_type()
G_DECLARE_FINAL_TYPE(TrgHistoryModel, trg_history_model, TRG, HISTORY_MODEL, GtkListStore)

TrgHistoryModel *trg_history_model_new(void);
void trg_history_model_update(TrgHistoryModel *model, JsonObject *t);
