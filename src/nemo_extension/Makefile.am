## Makefile.am -- Process this file with automake to produce Makefile.in

# Output and source files.
#lib_LTLIBRARIES = libtocc-nemo-extension.la
nemo_extensiondir=$(NEMO_EXTENSION_DIR)
nemo_extension_LTLIBRARIES=libtocc-nemo-extension.la
# Flags
libtocc_nemo_extension_la_LDFLAGS = -version-info 0:0:0 $(GTK_LIBS) $(NEMO_EXTENSION_LIBS)
libtocc_nemo_extension_la_CPPFLAGS = -I.. $(GTK_CFLAGS) $(ORBIT_CFLAGS) $(NEMO_EXTENSION_CFLAGS)
# Sources
libtocc_nemo_extension_la_SOURCES = ../utils/memory_utils.c ../utils/terminate.c ../utils/message_box.c ../importer/importer.c ../importer/main_dialog.c ../libtocc_wrapper/libtocc_wrapper.cpp nemo_extension.c

# Install action
#install:
#	test -z $(NEMO_EXTENSION_DIR) || mkdir -p -- $(NEMO_EXTENSION_DIR)
#	cp .libs/libtocc_nemo_extension.so

