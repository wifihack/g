.PHONY: all lib test debug release debug_test release_test libg_d libg_gui_d libg libg_gui g_d_test g_gui_d_test g_test g_gui_test

all: lib #test

lib: debug release

test: debug_test release_test

debug: libg_d libg_gui_d

release: libg libg_gui

debug_test: g_d_test g_gui_d_test

release_test: g_test g_gui_test

libg_d:
	mkdir -p libg_d;      cd libg_d;        qmake ../libg.pro          "CONFIG+=debug"; make
	
libg_gui_d:
	mkdir -p libg_gui_d;   cd libg_gui_d;   qmake ../libg_gui.pro      "CONFIG+=debug"; make

libg:
	mkdir -p libg;         cd libg;         qmake ../libg.pro;                          make

libg_gui:
	mkdir -p libg_gui;     cd libg_gui;     qmake ../libg_gui.pro;                      make

g_d_test:
	mkdir -p g_d_test;     cd g_d_test;     qmake ../libg_test.pro     "CONFIG+=debug"; make

g_gui_d_test:
	mkdir -p g_gui_d_test; cd g_gui_d_test; qmake ../libg_gui_test.pro "CONFIG+=debug"; make

g_test:
	mkdir -p g_test;       cd g_test;       qmake ../libg_test.pro;                     make

g_gui_test:
	mkdir -p g_gui_test;   cd g_gui_test;   qmake ../libg_gui_test.pro;                 make

clean:
	rm -rf libg_d
	rm -rf libg_gui_d
	rm -rf libg
	rm -rf libg_gui
	rm -rf g_d_test
	rm -rf g_gui_d_test
	rm -rf g_test
	rm -rf g_gui_test
	rm -rf *.pro.user

distclean: clean
	rm -rf *.a
	rm -rf ../bin/g_d_test
	rm -rf ../bin/g_gui_d_test
	rm -rf ../bin/g_test
	rm -rf ../bin/g_gui_test
