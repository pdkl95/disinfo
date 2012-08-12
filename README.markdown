disinfo - Shell Tools for Printing/UI
=====================================

Purpose and Goals
-----------------


Shell scripts currently lack such a mechanism, resulting in most
having to reinvent the wheel for basic stuff such as error
messages. As a very small set of C wrapper programs, disinfo should
be a fast, universal tool that can be dropped in as a replacement for
various `echo` based constructs.

Installing
----------

Just clone the repository and build it in standard GNU-autotools style:

    git clone https://github.com/pdkl95/disinfo.git
    cd disinfo
    ./configure
    make
    sudo make install

The cross-platform compatability tool
[gnulib](http://www.gnu.org/software/gnulib/)
is used, so it should (hopefully) build trivially
on any vaguely modern platform.


Usage
-----

Origins
-------

This started out as `edisinfo`, a thin wrapper around
[OpenRC](http://www.gentoo.org/proj/en/base/openrc/)'s
message-printing tools in
[libeinfo](http://git.overlays.gentoo.org/gitweb/?p=proj/openrc.git;a=tree;f=src/libeinfo).
This provided not only optional color success/failure indication, but
also helps provide a more consistent message style between programs.
Having seen it used extensively in [Gentoo](http://www.gentoo.org)'s
various system-level scripts, I eventually started using it for
various minor sysadmin stuff.

Unfortunately, I quickly found out those particular helper tools
were tied fairly strongly to OpenRC, and, finally annoyed with
compatability issues on any other platform, simply re-implementing
it in a stand-alone form seemed the like a good idea.

While the OpenRC library was used directly in the beginnning, that
was intended only as a temporary prototyping step. Currently,
it doesn't link against anything besides libc, in a hope
to keep the tools very small, simple, and fast. If anything
really fancy is neessary, it would make more sense to just use
any of the
[huge](http://ruby-lang.org)
[list](http://www.perl.org)
of
[other](http://www.tcl.tk)
[common](http://www.python.org)
[languages](http://www.zsh.org)
and
[tools](http://code.google.com/p/yad)
[out](http://boxes.thomasjensen.com)
[there](http://caca.zoy.org/wiki/toilet).


Copyright
---------

Copyright 2012 Brent Sanders

disinfo is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

disinfo is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with disinfo.  If not, see <http://www.gnu.org/licenses/>.

