# All Target
OBJ=tototl
.PHONY: release install clean

all: release

release:
	(cd Release; make)

install:
	cp Release/${OBJ} /usr/bin/

clean:
	(cd Release; make clean)
