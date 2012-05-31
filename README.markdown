edisinfo
========

This is a thin wrapper around
[OpenRC](http://www.gentoo.org/proj/en/base/openrc/)'s
message-printing tools in
[libeinfo](http://git.overlays.gentoo.org/gitweb/?p=proj/openrc.git;a=tree;f=src/libeinfo).
This provides not only optional color success/failure indication, but
also helps provide a more consistent message style between programs.

Shell scripts currently lack such a mechanism, resulting in most
having to reinvent the wheel for basic stuff such as error
messages. As a very small set of C wrapper programs, edisinfo should
be a fast, universal tool that can be dropped in as a replacement for
various `echo` based constructs.

Installing
----------

Just clone the repository and build it in standard GNU-autotools style:

    git clone git@github.com:pdkl95/edisinfo.git
    cd edisinfo
    ./configure
    make
    sudo make install

The cross-platform compatability tool
[gnulib](http://www.gnu.org/software/gnulib/)
is used, so it should (hopefully) build trivially
on any vaguely modern platform.


Copyright
---------

Copyright 2012 Brent Sanders

edisinfo is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

edisinfo is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with edisinfo.  If not, see <http://www.gnu.org/licenses/>.

