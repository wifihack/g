TEMPLATE = lib
QT -= gui
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}
CONFIG += staticlib
DESTDIR = $${PWD}
include(libg_files.pri)
