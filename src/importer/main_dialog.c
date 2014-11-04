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

#include "importer/main_dialog.h"

#include <gtk/gtk.h>


void tocc_nemo_importer_dialog_show(char** files)
{
  GtkWidget* window;
  GtkWidget* label;

  // Initializing Gtk with no argument.
  gtk_init(0, NULL);

  // Initializing the main window.
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Tocc File Importer");

  // Terminate the `gkt main' when close button clicks.
  g_signal_connect(window, "destroy",
                   G_CALLBACK(gtk_main_quit),
                   NULL);


  // Creating a label to show the file path.
  label = gtk_label_new(files[0]);
  // Adding label to the window.
  gtk_container_add(GTK_CONTAINER(window), label);

  // Showing the window and all its widgets.
  gtk_widget_show_all(window);

  // Staring Gtk main loop.
  gtk_main();
}
