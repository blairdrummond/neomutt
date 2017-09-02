/**
 * @file
 * Constants/structs for handling (lists of) regular expressions
 *
 * @authors
 * Copyright (C) 1996-2000 Michael R. Elkins <me@mutt.org>
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

/*
 * A (more) generic interface to regular expression matching
 */

#ifndef _MUTT_REGEX_H
#define _MUTT_REGEX_H

#include "config/regex2.h"
#include "where.h"

WHERE struct Regex Mask;
WHERE struct Regex QuoteRegexp;
WHERE struct Regex ReplyRegexp;
WHERE struct Regex Smileys;
WHERE struct Regex GecosMask;

#endif /* _MUTT_REGEX_H */
