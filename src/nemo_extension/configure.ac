#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tocc-nemo-extension], [0.1.0], [aidin@t-o-c-c.com], [tocc-nemo-extension], [http://github.com/aidin36/tocc-nemo])
AC_CONFIG_SRCDIR([../importer/importer.h])
#AC_CONFIG_HEADERS([config.h])

# Initializing Libtool
LT_INIT

# Initializing Automake
# [foreign] added, so automake won't check for missing NEWS, README, etc.
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

# Checking for Gtk
PKG_CHECK_MODULES(GTK, gtk+-2.0)
# Checking for libnemo-extension
PKG_CHECK_MODULES(NEMO_EXTENSION, libnemo-extension)
# Checking for Orbit headers.
PKG_CHECK_MODULES(ORBIT, ORBit-2.0)

# Checking for libtocc.
# Setting lang to C++, because libtocc is in C++
AC_LANG_PUSH(C++)
# The fourth argument is: don't try to compile this header.
AC_CHECK_HEADER([libtocc.h], [], [AC_MSG_ERROR([Could not find libtocc.h header. Please make sure you have libtocc headers in your include path. Refer to documents for more info.])], [-])
# `libtocc_exists' function used to check for libtocc. See Tocc's documentation
# about how to check for libtocc with Autoconf.
AC_SEARCH_LIBS([libtocc_exists], [tocc], [], [AC_MSG_ERROR([Could not find libtocc library. Please make sure you have this library in your libs path. Refer to documentations for more info.])])
# Changing back the language to C
AC_LANG_POP

# Geting nemo extensions directory
AC_MSG_CHECKING([for nemo extension directory])
if test -n "$with_nemo_extension_dir"; then
  NEMO_EXTENSION_DIR=$with_nemo_extension_dir
else
  NEMO_EXTENSION_DIR=`$PKG_CONFIG --variable=extensiondir libnemo-extension`
fi
if test -z "$NEMO_EXTENSION_DIR"; then
  NEMO_EXTENSION_DIR='${exec_prefix}/lib/nemo/extension-3.0'
fi
AC_MSG_RESULT([${NEMO_EXTENSION_DIR}])
AC_SUBST(NEMO_EXTENSION_DIR)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
