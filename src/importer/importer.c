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

#include "importer/importer.h"

//#include <stdlib.h>
//#include <pthread.h>

#include "importer/main_dialog.h"


/*
 * Shows the import dialog to the user.
 */
//void* tocc_nemo_show_import_dialog(void* arg)
//{
//  char** files_array = (char**)arg;
//
//  tocc_nemo_importer_dialog_show(files_array);
//
//  //free(files_array);
//}

void tocc_nemo_import_files(char** files_array)
{
  // Creating new thread. (We should do this, or else we will block the
  // main thread of Nemo/Nautilus.
  //pthread_t* thread_id;

  //int result = pthread_create(thread_id, NULL, tocc_nemo_show_import_dialog, files_array);
  //if (result != 0)
  //{
    //Print error and exit.
  //}

  tocc_nemo_importer_dialog_show(files_array);
}
