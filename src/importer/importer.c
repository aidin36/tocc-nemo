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
#include <string.h>
#include <stdbool.h>
#include "utils/memory_utils.h"


void tocc_nemo_import_files(char** files_array, int file_array_size,
                            char* tags_string)
{
  char** tags_array;
  int tags_array_size = parse_tags(tags_string, &tags_array);

  // TODO: Do import.

  free(tags_array);
}


struct ListNode
{
  char* value;
  struct ListNode* next;
};

/*
 * Fills the `current_node', and creates a new node as the next of the
 * `current_node'.
 */
struct ListNode* make_tag(struct ListNode* current_node,
                          char* tags_string,
                          int start_index,
                          int end_index)
{
  // Filling current node.
  current_node->value = allocate_memory((end_index - start_index) * sizeof(char*));
  strncpy(current_node->value, tags_string + start_index, end_index - start_index);

  // Creating next node in the list.
  struct ListNode* result = malloc(sizeof(struct ListNode));
  current_node->next = result;
  result->value = NULL;
  result->next = NULL;

  return result;
}

/*
 * Parses the string, and extract a list of tags from it.
 */
int parse_tags(char* tags_string, char*** tags_array)
{
  int nodes_count = 0;
  int current_index = 0;
  int tag_start_index = 0;
  bool inside_quote = false;
  struct ListNode* current_node = allocate_memory(sizeof(struct ListNode));
  struct ListNode* root_node = current_node;

  while (*(tags_string + current_index))
  {
    if (*(tags_string + current_index) == '"')
    {
      if (inside_quote)
      {
        if (current_index - tag_start_index <= 1)
        {
          // Empty quote.
          tag_start_index = current_index + 1;
        }
        else
        {
          // Quote ended.
          current_node = make_tag(current_node, tags_string, tag_start_index, current_index);
          nodes_count++;
          tag_start_index = current_index + 1;
          inside_quote = false;
        }
      }
      else
      {
        if (current_index - tag_start_index <= 1)
        {
          // Start of a quote.
          tag_start_index = current_index + 1;
          inside_quote = true;
        }
        // else: It's a quote inside a tag. i.e. ab"c
      }
    }
    else if (*(tags_string + current_index) == ' ')
    {
      if (!inside_quote)
      {
        if (current_index - tag_start_index <= 1)
        {
          // Double space, or start of a new tag.
          tag_start_index = current_index + 1;
        }
        else
        {
          current_node = make_tag(current_node, tags_string, tag_start_index, current_index);
          nodes_count++;
          tag_start_index = current_index + 1;
        }
      }
    }

    current_index++;
  }

  if (current_index - tag_start_index > 1)
  {
    // There's still one more tag.
    current_node = make_tag(current_node, tags_string, tag_start_index, current_index);
    nodes_count++;
  }

  // Last node that never filled.
  free(current_node);

  // Converting linked list into a array of char pointers.
  *tags_array = allocate_memory(nodes_count * sizeof(char*));

  current_node = root_node;
  struct ListNode* previous_node;
  int i = 0;
  for (; i < nodes_count; i++)
  {
    (*tags_array)[i] = current_node->value;
    previous_node = current_node;
    current_node = current_node->next;
    free(previous_node);
  }

  // Filling size of the result into output variable.
  return nodes_count;
}
