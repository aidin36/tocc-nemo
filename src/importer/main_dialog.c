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

#include <stdlib.h>
#include <gtk/gtk.h>


struct ClickedButtonData
{
  GtkWidget* entry;
  GtkWidget* main_window;
  char** files_array;
  int array_size;
};


void tocc_nemo_import_clicked(GtkButton* button, gpointer user_data)
{
  struct ClickedButtonData* data = (struct ClickedButtonData*)user_data;

  // Reading entry's text.
  GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(data->entry));

  if (gtk_entry_buffer_get_length(entry_buffer) == 0)
  {
    // TODO: Show an error message.
  }

  const char* entry_text = gtk_entry_buffer_get_text(entry_buffer);

  // Importing files into Tocc.
  tocc_nemo_import_files(data->files_array, data->array_size, entry_text);

  // Terminating application.
  gtk_main_quit();
}


void tocc_nemo_importer_dialog_show(char** files_array, int array_size)
{
  GtkWidget* window;
  GtkWidget* label;
  GtkWidget* entry;
  GtkWidget* main_box;
  GtkWidget* hbox;
  GtkWidget* buttons_hbox;
  GtkWidget* button;

  // Initializing Gtk with no argument.
  gtk_init(0, NULL);

  // Initializing the main window.
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Tocc File Importer");
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

  // Terminate the `gkt main' when close button clicks.
  g_signal_connect(window, "destroy",
                   G_CALLBACK(gtk_main_quit),
                   NULL);

  // Creating main VBox.
  main_box = gtk_vbox_new(FALSE, 3);
  // Adding it to the window.
  gtk_container_add(GTK_CONTAINER(window), main_box);

  // Creating a label to show the number of files.
  char label_text[70];
  sprintf(label_text,
          "You are going to import %i file(s) into Tocc Managed File System.",
          array_size);
  label = gtk_label_new(label_text);
  gtk_box_pack_start(GTK_BOX(main_box), label, FALSE, FALSE, 5);

  // Creating second line: Label and the Entry.
  hbox = gtk_hbox_new(FALSE, 3);
  label = gtk_label_new("Tags:");
  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 512);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(main_box), hbox, FALSE, FALSE, 5);

  // Creating third line: Buttons.
  struct ClickedButtonData clicked_button_data;
  clicked_button_data.entry = entry;
  clicked_button_data.files_array = files_array;
  clicked_button_data.array_size = array_size;

  hbox = gtk_hbox_new(FALSE, 3);
  buttons_hbox = gtk_hbox_new(FALSE, 3);
  // This empty hbox is added, to keep the buttons right-aligned.
  gtk_box_pack_start(GTK_BOX(buttons_hbox), hbox, TRUE, FALSE, 3);
  button = gtk_button_new_with_label("Import");
  g_signal_connect(button, "clicked",
                   G_CALLBACK(tocc_nemo_import_clicked),
                   (gpointer)&clicked_button_data);
  gtk_box_pack_start(GTK_BOX(buttons_hbox), button, FALSE, FALSE, 5);
  button = gtk_button_new_with_label("Cancel");
  // Terminates the GTK loop on click.
  g_signal_connect(button, "clicked",
                   G_CALLBACK(gtk_main_quit),
                   NULL);
  gtk_box_pack_start(GTK_BOX(buttons_hbox), button, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(main_box), buttons_hbox, FALSE, FALSE, 3);

  // Showing the window and all its widgets.
  gtk_widget_show_all(window);

  // Staring Gtk main loop.
  gtk_main();

  // Freeing resources.
  free(files_array);
  // Calling destroy on Window give me an assertion. But if I don't call this,
  // none of the widgets will free.
  gtk_widget_destroy(window);
}
