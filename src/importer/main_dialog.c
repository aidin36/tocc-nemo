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
#include <string.h>
#include <errno.h>
#include <gtk/gtk.h>
#include "utils/terminate.h"
#include "utils/memory_utils.h"
#include "utils/message_box.h"
#include "utils/file_utils.h"


struct ClickedButtonData
{
  GtkWidget* base_path_entry;
  GtkWidget* title_entry;
  GtkWidget* tags_entry;
  char** files_array;
  int array_size;
};

void save_base_path(const char* base_path)
{
  char setting_file[255];
  strcpy(setting_file, getenv("HOME"));
  int home_path_len = strlen(setting_file);
  strcpy(setting_file + home_path_len, "/.tocc-nemo.config");

  FILE* setting_file_d = fopen(setting_file,  "w");
  if (setting_file_d == NULL)
  {
    fputs("Could not open config file to write: ", stderr);
    fputs(strerror(errno), stderr);
    fputs("\n", stderr);

    tocc_nemo_show_error("Could not open config file to write.");
    tocc_nemo_terminate();
  }
  if (fputs(base_path, setting_file_d) <= 0)
  {
    fputs("Couldn't write to config file.\n", stderr);
    tocc_nemo_show_error("Couldn't write to config file.");
    tocc_nemo_terminate();
  }
  if (fclose(setting_file_d) != 0)
  {
    fputs("Could not close config file after writing to it: ", stderr);
    fputs(strerror(errno), stderr);
    fputs("\n", stderr);

    tocc_nemo_show_error("Could not close config file after writing to it.");
    tocc_nemo_terminate();
  }
}

char* load_base_path()
{
  char setting_file[255];
  strcpy(setting_file, getenv("HOME"));
  int home_path_len = strlen(setting_file);
  strcpy(setting_file + home_path_len, "/.tocc-nemo.config");

  FILE* setting_file_d = fopen(setting_file,  "r");
  if (setting_file_d == NULL)
  {
    // File doesn't exists, or anything else. Doesn't matter, we assume
    // that there wasn't any config file.
    return NULL;
  }

  // One extra char added to size, because of '\0'.
  char* buffer = allocate_memory(256 * sizeof(char));

  if (fgets(buffer, 255, setting_file_d) == NULL)
  {
    fputs("Couldn't read from config file.\n", stderr);
    tocc_nemo_show_error("Couldn't read from config file.");
    tocc_nemo_terminate();
  }
  if (fclose(setting_file_d) != 0)
  {
    fputs("Could not close config file after reading it: ", stderr);
    fputs(strerror(errno), stderr);
    fputs("\n", stderr);

    tocc_nemo_show_error("Could not close config file after reading it.");
    tocc_nemo_terminate();
  }

  return buffer;
}

void tocc_nemo_import_clicked(GtkButton* button, gpointer user_data)
{
  struct ClickedButtonData* data = (struct ClickedButtonData*)user_data;

  // Reading tags from entry's text.
  GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(data->tags_entry));

  if (gtk_entry_buffer_get_length(entry_buffer) == 0)
  {
    tocc_nemo_show_error("Please enter one tag, at least.");
    return;
  }

  const char* tags_string = gtk_entry_buffer_get_text(entry_buffer);

  // Reading base path.
  entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(data->base_path_entry));

  if (gtk_entry_buffer_get_length(entry_buffer) == 0)
  {
    tocc_nemo_show_error("Please enter the base path.");
    return;
  }

  const char* base_path_string = gtk_entry_buffer_get_text(entry_buffer);

  // Reading title.
  const char* title_string = "";
  if (data->array_size == 1)
  {
    // If there was exactly one file, user can set title of the file.
    // If not, we send title as empty string, so it will be auto-assigned.
    entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(data->title_entry));
    if (gtk_entry_buffer_get_length(entry_buffer) > 0)
    {
      title_string = gtk_entry_buffer_get_text(entry_buffer);
    }
  }

  // Importing files into Tocc.
  tocc_nemo_import_files(base_path_string,
                         data->files_array,
                         data->array_size,
                         tags_string,
                         title_string);

  // Terminating application.
  gtk_main_quit();
}


void tocc_nemo_importer_dialog_show(char** files_array, int array_size)
{
  GtkWidget* window;
  GtkWidget* label;
  GtkWidget* title_entry;
  GtkWidget* tags_entry;
  GtkWidget* base_path_entry;
  GtkWidget* main_box;
  GtkWidget* hbox;
  GtkWidget* buttons_hbox;
  GtkWidget* button;
  char* base_path;

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

  // Creating second line: Base path.
  hbox = gtk_hbox_new(FALSE, 3);
  label = gtk_label_new("Base Path:");
  base_path_entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(base_path_entry), 255);
  // Trying to read base path from configs.
  base_path = load_base_path();
  if (base_path != NULL)
  {
    gtk_entry_set_text(GTK_ENTRY(base_path_entry), base_path);
  }

  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), base_path_entry, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(main_box), hbox, FALSE, FALSE, 5);

  // Next line: Title label and Entry.
  hbox = gtk_hbox_new(FALSE, 3);
  label = gtk_label_new("Title:");
  title_entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(title_entry), 250);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), title_entry, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(main_box), hbox, FALSE, FALSE, 5);
  if (array_size == 1)
  {
    // Setting text of title entry.
    gtk_entry_set_text(GTK_ENTRY(title_entry), tocc_nemo_get_file_name(files_array[0]));
  }
  else
  {
    // Multiple files.
    gtk_entry_set_text(GTK_ENTRY(title_entry), "(Multiple Files)");
    gtk_widget_set_sensitive(GTK_WIDGET(title_entry), FALSE);
  }

  // Next line: Tags Label and Entry.
  hbox = gtk_hbox_new(FALSE, 3);
  label = gtk_label_new("Tags:");
  tags_entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(tags_entry), 512);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), tags_entry, TRUE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(main_box), hbox, FALSE, FALSE, 5);

  // Creating last line: Buttons.
  struct ClickedButtonData clicked_button_data;
  clicked_button_data.base_path_entry = base_path_entry;
  clicked_button_data.title_entry = title_entry;
  clicked_button_data.tags_entry = tags_entry;
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

  // Trying to write base path into config file.
  // Reading entry's text.
  GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(base_path_entry));

  if (gtk_entry_buffer_get_length(entry_buffer) != 0)
  {
    const char* entry_text = gtk_entry_buffer_get_text(entry_buffer);
    save_base_path(entry_text);
  }

  // Freeing resources.
  free(base_path);
  // Calling destroy on Window give me an assertion. But if I don't call this,
  // none of the widgets will free.
  gtk_widget_destroy(window);
}
