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

#ifndef TOCC_NEMO_MEMORY_UTILS_H_INCLUDED
#define TOCC_NEMO_MEMORY_UTILS_H_INCLUDED

#include <stdlib.h>

/*
 * Allocates a memory, using `malloc' func,
 * and checks for errors.
 */
void* allocate_memory(size_t size);

#endif /* TOCC_NEMO_MEMORY_UTILS_H_INCLUDED */
