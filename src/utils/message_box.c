/*
 * This file is part of Tocc-nemo.
 * (see <http://www.github.com/aidin36/tocc-nemo>)
 * Copyright (C) 2014, Aidin Gharibnavaz <aidin@t-o-c-c.com>
 *
 * Tocc-nemo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tocc-nemo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tocc-nemo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils/message_box.h"

#include <gtk/gtk.h>


void tocc_nemo_show_error(const char* message)
{
  GtkWidget* message_dialog;

  message_dialog = gtk_message_dialog_new(NULL,
                                          0,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_OK,
                                          "%s",
                                          message);
  gtk_dialog_run(GTK_DIALOG(message_dialog));
  gtk_widget_destroy(message_dialog);
}
