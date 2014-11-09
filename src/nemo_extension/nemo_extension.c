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

/*
 * This file implements the interface of nemo-extension.
 * It provides a menu-item for right-click menu, which opens
 * a window for importing files into Tocc.
 */

#include <stdlib.h>
#include <libnemo-extension/nemo-menu-provider.h>
#include <orbit/orb-core/corba-typecode-type.h>

#include "utils/memory_utils.h"
#include "importer/main_dialog.h"


/*
 * Extension Classes.
 */
typedef struct _ToccExtension ToccExtension;
typedef struct _ToccExtensionClass ToccExtensionClass;

struct _ToccExtension
{
  GObject parent_slot;
};

struct _ToccExtensionClass
{
  GObjectClass parent_slot;
};

/*
 * Initializer function for ToccExteionClass.
 */
static void tocc_extension_class_init(ToccExtensionClass* class)
{
}

/*
 * Initializer function for ToccExteion instance.
 */
static void tocc_extension_instance_init(ToccExtension* img)
{
}

static GType provider_types[1];
static GType tocc_extension_type;


/*
 * Calls when the menu item clicks.
 */
static void on_tocc_import_activate(NemoMenuItem* item,
                                    gpointer user_data)
{
  GList* files;
  GList* file_iterator;
  char** files_array;
  int array_index = 0;
  int files_size;

  // Getting list of selected files from item's data.
  files = g_object_get_data((GObject*)item, "tocc_extension_files");
  files_size = g_list_length(files);

  if (files_size == 0)
  {
    // No file selected. Strange, but may happen.
    return;
  }

  // Allocating memory for the array of files.
  files_array = allocate_memory(sizeof(char*) * files_size);

  for (file_iterator = files; file_iterator != NULL; file_iterator = file_iterator->next)
  {
    NemoFileInfo* file_info = NEMO_FILE_INFO(file_iterator->data);

    GFile* gfile = (GFile*)nemo_file_info_get_location(file_info);

    files_array[array_index] = g_file_get_path(gfile);
    array_index++;
  }

  // Showing the import dialog to user.
  tocc_nemo_importer_dialog_show(files_array, files_size);

  // Freeing allocated memory.
  free(files_array);
}

static void on_tocc_item_data_destroyed(gpointer data)
{
  g_list_free((GList*)data);
}

/*
 * Creates a list of items that should be appears in the Right-click Menu
 * of Nemo.
 */
GList* tocc_extension_get_file_items(NemoMenuProvider* provider,
                                     GtkWidget* window,
                                     GList* files)
{
  GList* files_iterator;

  for (files_iterator = files; files_iterator != NULL; files_iterator = files_iterator->next)
  {
    if (nemo_file_info_is_directory(files_iterator->data))
    {
      // We don't want to add this item to menu when user right-click on
      // a directory.
      return NULL;
    }
  }

  NemoMenuItem* item;
  GList* result;

  // Creating the menu item.
  item = nemo_menu_item_new("ToccExtension::import",
                            "Import to Tocc",
                            "Imports selected file(s) into Tocc File Management System.",
                             NULL /* icon name */);

  // Assigning a call-back for `activate' signal (e.g. when menu clicked).
  g_signal_connect(item, "activate", G_CALLBACK(on_tocc_import_activate), NULL);

  // Putting selected file in the item's data.
  g_object_set_data_full((GObject*)item,
                         "tocc_extension_files",
                         g_list_copy(files),
                         (GDestroyNotify)on_tocc_item_data_destroyed);

  result = g_list_append(NULL, item);

  return result;
}

GList* tocc_extension_get_background_items(NemoMenuProvider* provider,
                                           GtkWidget* window,
                                           NemoFileInfo* current_folder)
{
  // We don't want to add any background item.
  return NULL;
}

/*
 * Initializes the menu-provider interface.
 */
static void tocc_extension_menu_provider_iface_init(NemoMenuProviderIface* iface)
{
  iface->get_file_items = tocc_extension_get_file_items;
  iface->get_background_items = tocc_extension_get_background_items;
}

/*
 * Registers the Extension type.
 */
static void tocc_extension_register_type(GTypeModule *module)
{
  static const GTypeInfo info =
    {
      sizeof(ToccExtensionClass),
      (GBaseInitFunc)NULL,
      (GBaseFinalizeFunc)NULL,
      (GClassInitFunc)tocc_extension_class_init,
      NULL,
      NULL,
      sizeof(ToccExtension),
      0,
      (GInstanceInitFunc)tocc_extension_instance_init,
    };

  tocc_extension_type = g_type_module_register_type(module,
                                                    G_TYPE_OBJECT,
                                                    "ToccExtension",
                                                    &info, 0);

  static const GInterfaceInfo menu_provider_iface_info =
    {
      (GInterfaceInitFunc)tocc_extension_menu_provider_iface_init,
      NULL,
      NULL
    };

  g_type_module_add_interface(module,
                              tocc_extension_type,
                              NEMO_TYPE_MENU_PROVIDER,
                              &menu_provider_iface_info);
}

GType tocc_extension_get_type(void)
{
  return tocc_extension_type;
}

/*
 * Initializes the module. (Everything starts here!)
 * It tells Nemo what types this extension provides.
 */
void nemo_module_initialize(GTypeModule *module)
{
  tocc_extension_register_type(module);
  provider_types[0] = tocc_extension_get_type();
}

/*
 * Calls when module is destroyed.
 */
void nemo_module_shutdown(void)
{
}

void nemo_module_list_types(const GType **types,
                            int *num_types)
{
  *types = provider_types;
  *num_types = G_N_ELEMENTS(provider_types);
}


// Following three methods are un-unused. But they should be provided for
// a Nemo Extension.
G_MODULE_EXPORT const gchar* g_module_check_init (GModule *module);

const gchar* g_module_check_init (GModule *module)
{
  return NULL;
}

void g_module_unload()
{
}

// Orbit
gpointer ORBit_realloc_tcval(gpointer old,
                             CORBA_TypeCode tc,
                             guint old_num_elements,
                             guint num_elements)
{
  return NULL;
}
