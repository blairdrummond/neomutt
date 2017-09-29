/**
 * @file
 * Implementation of the notifications infrastructure
 *
 * @authors
 * Copyright (C) 2017 Pietro Cerutti <gahr@gahr.ch>
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

#include "config.h"
#include "keymap.h"
#include "lib/mapping.h"
#include "lib/memory.h"
#include "lib/message.h"
#include "lib/string2.h"
#include "mutt.h"
#include "mutt_menu.h"
#include "notifications.h"
#include "opcodes.h"
#include "queue.h"

#include <string.h>

static TAILQ_HEAD(NotificationsHead, Notification) Notifications =
  TAILQ_HEAD_INITIALIZER(Notifications);

struct Notification
{
  const char *data;
  TAILQ_ENTRY(Notification) entries;
};

static const struct Mapping NotificationsHelp[] = {
  { N_("Exit"), OP_EXIT }, { NULL, 0 },
};

static void notifications_entry(char *b, size_t blen, struct Menu *menu, int num)
{
  size_t i = 0;
  struct Notification *np;
  TAILQ_FOREACH(np, &Notifications, entries)
  {
    if (i++ == num)
    {
      break;
    }
  }
  if (!np)
  {
    return;
  }
  snprintf(b, blen, "%s", np->data);
}

void mutt_notifications_show(void)
{
  if (!mutt_has_notifications())
  {
    mutt_error(_("There are no notifications"));
    return;
  }

  size_t nof_notifications = 0;
  struct Notification *np;
  TAILQ_FOREACH(np, &Notifications, entries)
  {
    ++nof_notifications;
  }

  char helpstr[LONG_STRING];
  struct Menu *menu = mutt_new_menu(MENU_NOTIFICATIONS);
  menu->title = _("Notifications");
  menu->make_entry = notifications_entry;
  menu->help = mutt_compile_help(helpstr, sizeof(helpstr), MENU_NOTIFICATIONS,
                                 NotificationsHelp);
  menu->max = nof_notifications;
  mutt_push_current_menu(menu);

  int op = OP_NULL;
  while (true)
  {
    if (op == OP_NULL)
      op = mutt_menu_loop(menu);
    switch (op)
    {
      case OP_EXIT:
        mutt_pop_current_menu(menu);
        mutt_menu_destroy(&menu);
        return;
      default:
        break;
    }
    op = OP_NULL;
  }

  /* not reached */
}

void mutt_notifications_add(const char *s)
{
  if (!s || !*s)
    return;

  struct Notification *np;
  TAILQ_FOREACH(np, &Notifications, entries)
  {
    if (strcmp(s, np->data) == 0)
    {
      return;
    }
  }
  np = safe_calloc(1, sizeof(struct Notification));
  np->data = safe_strdup(s);
  TAILQ_INSERT_TAIL(&Notifications, np, entries);
}

bool mutt_has_notifications(void)
{
  return !TAILQ_EMPTY(&Notifications);
}
