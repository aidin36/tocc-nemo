Tocc Extension for Nemo and Nautilus file browsers
==================================================

This project provides an extension for Nemo and Nautilus file browsers, to let
you use Tocc File Management more easily.

To learn more about Tocc itself, take a look at its website:

  http://t-o-c-c.com


Install Nemo Extension
======================

Requirements:

  libnemo-extension
  liborbit2
  libgtk


Usually, all you need is to install three packages called
``libnemo-extension-dev``, ``liborbit2-dev`` and ``libgtk2.0-dev``.
(Or maybe ``-devel`` instead of ``-dev``.)

Then, go to ``src/nemo-extension`` directory. Then run ``./bootstrap``,
then ``./configure``, ``make``, ``make install``.


Install Nautilus Extension
==========================

Requirements:

  libnautilus-extension
  liborbit2
  libgtk

Go to ``src/nautilus-extension``, and run `./bootstrap``,
then ``./configure``, ``make``, ``make install``.


Non-standard Extensions Directory
=================================

Sometimes, you may need to install extension somewhere else. But default, the
make script asks ``pkg-config`` that where is extension directory, and install
extension there.

If you want to provide another directory, use
``./configure --with_nemo_extension_dir=/another/dir/``, or
``./configure --with_nautilus_extension_dir=/another/dir/``, depending on which
extension you're building.

