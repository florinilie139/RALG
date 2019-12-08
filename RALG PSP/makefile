TARGET = RALG
OBJS = main.o

PSP_FW_VERSION=620

INCDIR = 
CFLAGS = -G4 -Wall -O2 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
STDLIBS= -losl -lpng -lz \
         -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -ljpeg
LIBS=$(STDLIBS)$(YOURLIBS)

EXTRA_TARGETS = EBOOT.PBP
PSP_LARGE_MEMORY = 1
PSP_EBOOT_ICON = icon.png
PSP_EBOOT_UNKPNG = PIC0.PNG
PSP_EBOOT_PIC1 = PIC1.png
PSP_EBOOT_TITLE = REALLY Annoying level game

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak