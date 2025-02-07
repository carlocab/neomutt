/**
 * @file
 * General purpose object for storing and parsing strings
 *
 * @authors
 * Copyright (C) 2017 Ian Zimmerman <itz@primate.net>
 * Copyright (C) 2017-2019 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_LIB_BUFFER_H
#define MUTT_LIB_BUFFER_H

#include <stddef.h>
#include <stdbool.h>

/**
 * struct Buffer - String manipulation buffer
 */
struct Buffer
{
  char *data;   ///< Pointer to data
  char *dptr;   ///< Current read/write position
  size_t dsize; ///< Length of data
};

void           mutt_buffer_alloc        (struct Buffer *buf, size_t size);
void           mutt_buffer_dealloc      (struct Buffer *buf);
void           mutt_buffer_fix_dptr     (struct Buffer *buf);
struct Buffer *mutt_buffer_init         (struct Buffer *buf);
bool           mutt_buffer_is_empty     (const struct Buffer *buf);
size_t         mutt_buffer_len          (const struct Buffer *buf);
struct Buffer  mutt_buffer_make         (size_t size);
void           mutt_buffer_reset        (struct Buffer *buf);
char *         mutt_buffer_strdup       (const struct Buffer *buf);
void           mutt_buffer_seek         (struct Buffer *buf, size_t offset);

// Functions that APPEND to a Buffer
size_t         mutt_buffer_addch        (struct Buffer *buf, char c);
size_t         mutt_buffer_addstr       (struct Buffer *buf, const char *s);
size_t         mutt_buffer_addstr_n     (struct Buffer *buf, const char *s, size_t len);
int            mutt_buffer_add_printf   (struct Buffer *buf, const char *fmt, ...);

// Functions that INSERT into a Buffer
size_t         mutt_buffer_insert       (struct Buffer *buf, size_t offset, const char *s);

// Functions that OVERWRITE a Buffer
size_t         mutt_buffer_concat_path  (struct Buffer *buf, const char *dir, const char *fname);
size_t         mutt_buffer_concatn_path (struct Buffer *dst, const char *dir, size_t dirlen, const char *fname, size_t fnamelen);
size_t         mutt_buffer_copy         (struct Buffer *dst, const struct Buffer *src);
int            mutt_buffer_printf       (struct Buffer *buf, const char *fmt, ...);
size_t         mutt_buffer_strcpy       (struct Buffer *buf, const char *s);
size_t         mutt_buffer_strcpy_n     (struct Buffer *buf, const char *s, size_t len);
size_t         mutt_buffer_substrcpy    (struct Buffer *buf, const char *beg, const char *end);

/**
 * mutt_buffer_string - Convert a buffer to a const char * "string"
 * @param buf Buffer to that is to be converted
 * @retval ptr String inside the Buffer
 *
 * This method exposes Buffer's underlying data field
 *
 * @note Returns an empty string if Buffer isn't initialised
 */
static inline const char *mutt_buffer_string(const struct Buffer *buf)
{
  if (!buf || !buf->data)
    return "";

  return buf->data;
}

#endif /* MUTT_LIB_BUFFER_H */
