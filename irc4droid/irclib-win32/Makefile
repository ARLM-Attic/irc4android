
CC = i686-w64-mingw32-gcc
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
STRIP = i686-w64-mingw32-strip

#INCS =  -I"D:/MinGW/include"
INCS = 
#LIBS =  -LD:\MinGW\lib -lopengl32 -lglu32 -lglaux -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 
LIBS =  -lws2_32 -lopengl32 -lglu32 -lglaux -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lwinmm

.PHONY: all shared static debug clean compile dist build

all: debug

#static: compile
#	$(AR) r libms3d.a ms3d.o bmp.o quaternion.o matrix.o vector.o
#	ranlib libms3d.a

debug: compile
	$(CC) tcp-client.c $(LIBS) -o tcp-client.exe
	$(STRIP) tcp-client.exe
	./tcp-client.exe

clean:
	rm -f *.o *.a *.exe

compile:
	$(CC) $(INCS) -c tcp-client.c -o tcp-client.o
	
dist:
	cp ms3d.h ../include/ms3d.h
	cp libms3d.a ../lib/libms3d.a
	tar -cf  ../dist/libms3d.tar ../include/ms3d.h ../lib/libms3d.a
	gzip -9 ../dist/libms3d.tar

build: 
	
#tar -cf  ../test.tar && \

#gzip -9  $(RELEASE_DIR)/$(RELEASE_FILE).tar
