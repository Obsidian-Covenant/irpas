# IRPAS Makefile

DESTDIR =
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

CLIBS= -lpcap -ltirpc
CFLAGS+=-Wall -g -Wunused -Wmissing-prototypes -I/usr/include/tirpc -I.
LDFLAGS+= -L.
CC=gcc
RM=rm
CP=cp
TAR=tar
AR= ar rcs

RELEASE=IRPASrelease
RELVER=`grep "Version" IRPAS.version | awk '{print $$4}'`

OBJECTS= packets.o cdp.o igrp.o ass_v1.o irdp.o irdpresponder.o \
	itrace.o tctrace.o protos.o netmask.o file2cable.o dfkaa.o netenum.o \
	hsrp.o icmp_redirect.o timestamp.o dhcpx.o enum.o libpackets.a
TARGETS=cdp igrp ass irdp irdpresponder itrace tctrace protos \
	netmask file2cable dfkaa netenum hsrp icmp_redirect timestamp dhcpx

# Installed binaries (what actually gets produced)
PROGRAMS=irpas-cdp irpas-igrp irpas-ass irpas-irdp irpas-irdpresponder \
	irpas-itrace irpas-tctrace irpas-protos irpas-netmask irpas-file2cable \
	irpas-dfkaa irpas-netenum irpas-hsrp irpas-icmp_redirect \
	irpas-timestamp irpas-dhcpx

all: ${TARGETS}

# programs
dhcpx: dhcpx.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-dhcpx dhcpx.o -lpackets -lpcap
dhcpx.o: dhcpx.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c dhcpx.c

dfkaa: dfkaa.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-dfkaa dfkaa.o -lpackets
dfkaa.o: dfkaa.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c dfkaa.c

netenum: netenum.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-netenum netenum.o -lpackets
netenum.o: netenum.c packets.h protocols.h enum.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c netenum.c

hsrp: hsrp.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-hsrp hsrp.o -lpackets
hsrp.o: hsrp.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c hsrp.c

file2cable: file2cable.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-file2cable file2cable.o -lpackets
file2cable.o: file2cable.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c file2cable.c

cdp: cdp.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-cdp cdp.o -lpackets
cdp.o: cdp.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c cdp.c

igrp: igrp.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-igrp igrp.o -lpackets
igrp.o: igrp.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c igrp.c

timestamp: timestamp.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-timestamp timestamp.o -lpackets
timestamp.o: timestamp.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c timestamp.c

netmask: netmask.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-netmask netmask.o -lpackets
netmask.o: netmask.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c netmask.c

itrace: itrace.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-itrace itrace.o -lpackets
itrace.o: itrace.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c itrace.c

tctrace: tctrace.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-tctrace tctrace.o -lpackets
tctrace.o: tctrace.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c tctrace.c

protos: protos.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-protos protos.o -lpackets
protos.o: protos.c packets.h protocols.h protocol-numbers.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c protos.c

irdp: irdp.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-irdp irdp.o -lpackets
irdp.o: irdp.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c irdp.c

irdpresponder: irdpresponder.o libpackets.a
	${CC} ${LDFLAGS} -o irpas-irdpresponder irdpresponder.o -lpackets ${CLIBS}
irdpresponder.o: irdpresponder.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c irdpresponder.c

icmp_redirect.o: icmp_redirect.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c icmp_redirect.c
icmp_redirect: icmp_redirect.o libpackets.a 
	${CC} ${LDFLAGS} -o irpas-icmp_redirect icmp_redirect.o -lpackets ${CLIBS}

ass_v1.o: ass_v1.c packets.h protocols.h 
	${CC} ${CFLAGS} ${CPPFLAGS} -c ass_v1.c
ass: ass_v1.o libpackets.a 
	${CC} ${LDFLAGS} -o irpas-ass ass_v1.o -lpackets ${CLIBS}
assS: ass_v1.o libpackets.a
	${CC} ${CFLAGS} ${CPPFLAGS} -o irpas-assS ass_v1.o -lpackets ${CLIBS} -static

libpackets.a: packets.o enum.o 
	$(AR) libpackets.a packets.o enum.o
packets.o: packets.c  protocols.h
	$(CC) ${CFLAGS} ${CPPFLAGS} -c packets.c
enum.o: enum.h enum.c 
	$(CC) $(CFLAGS) ${CPPFLAGS} -c enum.c

install:
	mkdir -p $(DESTDIR)$(BINDIR)
	install ${PROGRAMS} $(DESTDIR)${BINDIR}

uninstall:
	${RM} -f $(addprefix $(DESTDIR)${BINDIR},${PROGRAMS})

clean:
	${RM} -f ${OBJECTS} ${PROGRAMS} *.orig
