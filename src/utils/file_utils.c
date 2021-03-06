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

#include "utils/file_utils.h"

#include <string.h>


const char* tocc_nemo_get_file_name(const char* path)
{
  char* result = strrchr(path, '/');

  if (result == NULL)
  {
    // No slash found in the path. Probably, it's one single file.
    return path;
  }

  // +1 added, because the `result' contain '/' at its beginning.
  // We don't want that slash.
  return result + 1;
}
