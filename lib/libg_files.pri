SOURCES += \
  $${PWD}/../src/base/*.cpp \
#  $${PWD}/../src/base/event/*.cpp \ # gilgil temp 2015.10.25
  $${PWD}/../src/base/prop/*.cpp \
#  $${PWD}/../src/net/*.cpp \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/procinfo/*.cpp \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/stacktrace/*.cpp \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/timediff/*.cpp # gilgil temp 2015.10.25
  $${PWD}/../src/net/*.cpp \
  $${PWD}/../src/net/capture/*.cpp

HEADERS += \
  $${PWD}/../src/base/*.h \
#  $${PWD}/../src/base/event/*.h \ # gilgil temp 2015.10.25
  $${PWD}/../src/base/prop/*.h \
#  $${PWD}/../src/net/*.h \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/procinfo/*.h \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/stacktrace/*.h \ # gilgil temp 2015.10.25
#  $${PWD}/../src/sys/timediff/*.h # gilgil temp 2015.10.25
  $${PWD}/../src/net/*.h \
  $${PWD}/../src/net/capture/*.h
