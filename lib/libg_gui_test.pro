TEMPLATE = app
QT += widgets
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}_test
DESTDIR = $${PWD}/../bin
include(libg_files.pri)
DEFINES *= GTEST
LIBS *= -lgflags -lgtest -lgtest_main -pthread
