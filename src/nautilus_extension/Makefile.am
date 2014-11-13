## Makefile.am -- Process this file with automake to produce Makefile.in

# Output and source files.
nautilus_extensiondir=$(NAUTILUS_EXTENSION_DIR)
nautilus_extension_LTLIBRARIES=libtocc-nautilus-extension.la
# Flags
libtocc_nautilus_extension_la_LDFLAGS = -version-info 0:0:0 $(GTK_LIBS) $(NAUTILUS_EXTENSION_LIBS)
libtocc_nautilus_extension_la_CPPFLAGS = -I.. $(GTK_CFLAGS) $(NAUTILUS_EXTENSION_CFLAGS)
# Sources
libtocc_nautilus_extension_la_SOURCES = ../utils/memory_utils.c ../utils/terminate.c ../utils/message_box.c ../importer/importer.c ../importer/main_dialog.c ../libtocc_wrapper/libtocc_wrapper.cpp nautilus_extension.c

