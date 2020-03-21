
SYS		= $(shell uname -s)
PWD		= $(shell pwd)
BASE		= $(shell basename $(PWD))
MAKE		= make
TEXTBOOK	= textbook
INCLASS		= env+tools sysinfo procenv procctl procrel \
		  threads daemon advio classipc netipc advipc \
		  signal termio files ipc asm
DIRS		= $(INCLASS) $(TEXTBOOK)

DATESTR		= $(shell date "+%Y%m%d")
TEXTBOOK_TGZ	= textbook-$(DATESTR).tar.gz
INCLASS_TGZ	= inclass-$(DATESTR).tar.gz

ifeq ($(SYS),FreeBSD)
MAKE		= gmake
endif

.PHONY: textbook

all: inclass textbook

inclass:
	for d in $(INCLASS); do $(MAKE) -C $$d; done

textbook:
	for d in $(TEXTBOOK); do $(MAKE) -C $$d; done

clean:
	for d in $(DIRS); do $(MAKE) -C $$d clean; done
	
pack: clean
	find . -name core -exec rm {} \;
	rm -f $(TEXTBOOK_TGZ) $(INCLASS_TGZ)
	cd ..; tar czf $(BASE)/$(TEXTBOOK_TGZ) \
		$(BASE)/textbook/ch* $(BASE)/textbook/include \
		$(BASE)/textbook/lib $(BASE)/textbook/shell \
		$(BASE)/textbook/Make*
	cd ..; tar czf $(BASE)/$(INCLASS_TGZ) $(BASE)/Makefile \
		$(shell echo " $(INCLASS)" | sed -re 's, +, $(BASE)/,g')

