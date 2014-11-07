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

#ifndef TOCC_NEMO_LIBTOCC_WRAPPER_H_INCLUDED
#define TOCC_NEMO_LIBTOCC_WRAPPER_H_INCLUDED

/*
 * It contains some functions that wraps libtocc's API, so it can be
 * use in C.
 */

/*
 * Imports specified files into Tocc, and assigned the specified
 * tags into them.
 */
#ifdef __cplusplus
extern "C"
#endif
void tocc_nemo_libtocc_import(char* base_path,
                              char** files_array,
                              int files_array_size,
                              char** tags_array,
                              int tags_array_size);

#endif /* TOCC_NEMO_LIBTOCC_WRAPPER_H_INCLUDED */
