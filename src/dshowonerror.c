/************************************************************************
 * This file is part of disinfo                                        *
 *                                                                      *
 * Copyright 2012 Brent Sanders                                         *
 *                                                                      *
 * disinfo is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * disinfo is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with disinfo.  If not, see <http://www.gnu.org/licenses/>.    *
 ************************************************************************/

#include <common.h>

char *local_usage = "<command> [<param> [...]]";

char *message;

int main(int argc, char *argv[])
{
    int i;
    common_options(&argc, &argv);

    if (argc < 1) {
        die_usage("missing <command> to run!");
    }

    return dshowonerror(argc, argv);
}
