/*
** RopGadget - Release v3.4.2
** Jonathan Salwan - http://twitter.com/JonathanSalwan
** http://shell-storm.org
** 2012-11-11
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ropgadget.h"

int onlymode(char *instruction)
{
  t_only_linked *tmp;
  char *org;

  org = instruction;
  tmp = only_linked;
  if (only_mode.flag == 0)
    return (1);
  while (tmp != NULL)
    {
      while (*instruction != '\0')
        {
          if (!strncmp(instruction, tmp->word, strlen(tmp->word)))
            return (1);
          instruction++;
        }
      instruction = org;
      tmp = tmp->next;
    }
  return (0);
}
