# All Target
OBJ=tototl

all: release

release:
	(cd Release; make)

install:
	cp Release/${OBJ} /usr/bin/

clean:
	(cd Release; make clean)
