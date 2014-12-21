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

#include "libtocc_wrapper/libtocc_wrapper.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <libtocc.h>

extern "C"
{
#include "utils/terminate.h"
#include "utils/message_box.h"
}


void tocc_nemo_libtocc_import(char* base_path,
                              char** files_array,
                              int files_array_size,
                              char** tags_array,
                              int tags_array_size,
                              char* title)
{
  try
  {
    libtocc::Manager libtocc_manager(base_path);

    // Creating TagsCollection from the specified array.
    libtocc::TagsCollection tags_collection(tags_array_size);
    int i = 0;
    for (; i < tags_array_size; i++)
    {
      tags_collection.add_tag(tags_array[i]);
    }

    i = 0;
    for (; i < files_array_size; i++)
    {
      libtocc_manager.import_file(files_array[i],
                                  title,
                                  "",
                                  &tags_collection);
    }
  }
  catch (std::exception& error)
  {
    std::cerr << "Failed to import files into tocc." << std::endl;
    std::cerr << error.what() << std::endl;

    // Showing error message to user.
    tocc_nemo_show_error(error.what());

    // Terminating.
    tocc_nemo_terminate();
  }
}
