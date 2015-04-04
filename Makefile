.POSIX:
.PHONY: all clean
.SUFFIXES: .cxx .o .xcf .png .svg .rc .res .exx

-include windurrs.mk
SDL2_PKG = sdl2 SDL2_image SDL2_ttf

LIBS = $$(pkg-config --libs $(SDL2_PKG))
MY_CXXFLAGS = -Wall -std=c++0x $$(pkg-config --cflags $(SDL2_PKG))
EXEEXT = .exe
OBJ = \
	src/camera.o \
	src/game_mode.o \
	src/main.o \
	src/menu_mode.o \
	src/mode.o \
	src/object.o \
	src/planet.o \
	src/player.o \
	src/sprite.o \
	src/star_block.o \
	src/star_field.o \
	src/universe.o 
HEADERS = \
	src/camera.hxx \
	src/game_mode.hxx \
	src/main.hxx \
	src/menu_mode.hxx \
	src/mode.hxx \
	src/object.hxx \
	src/planet.hxx \
	src/player.hxx \
	src/sprite.hxx \
	src/star_block.hxx \
	src/star_field.hxx \
	src/universe.hxx 

RASTERS = \
	images/favicon.png \
	images/cursor.png \
	\
	images/astronaut/space_suit.png \
	images/planet/plain.png \
	\
	images/menu/choose_bar.png \
	images/menu/main.png \
	\
	images/star_field/star_0.png \
	images/star_field/star_1.png \
	images/star_field/star_2.png 


MY_GIMP = $${GIMP-gimp}

all: spacenomad$(EXEEXT) $(RASTERS)
spacenomad$(EXEEXT): $(OBJ) $(RES) windurrs.mk
	./ecommand.sh $(CXX) $(MY_CXXFLAGS) $(CXXFLAGS) -o '$(@)' $(OBJ) $(RES) $(LIBS)

windurrs.mk: Makefile
	echo > windurrs.mk
	n="$$(which ls)"; test "$${n##*ls}" = ".exe" && echo 'RES = main.res' >> windurrs.mk
main.res: main.rc images/favicon.ico

.cxx.o:
	./ecommand.sh $(CXX) -c $(MY_CXXFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o '$(@)' '$(<)'
.cxx.exx:
	./ecommand.sh $(CXX) -E $(MY_CXXFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o '$(@)' '$(<)'
.xcf.png:
	./p-xcf2png.sh '$(<)' '$(@)'
.svg.png:
	inkscape -e '$(@)' -d 120 '$(<)'
.rc.res:
	windres '$(<)' -O coff -o '$(@)'

$(OBJ): Makefile
$(OBJ): $(HEADERS)
$(RASTERS): p-xcf2png.sh

clean:
	rm -f $(OBJ) $(RASTERS) $(RES) testsdl$(EXEEXT)

