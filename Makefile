CC?=gcc
DVSDIR?=/Library/Application\ Support/Audinate/DanteVirtualSoundcard

h: help
help:
	@cat help.txt

b: build
build: ptp-mitm.c
	$(CC) -o ptp-mitm ptp-mitm.c

c: clean
clean:
	$(RM) ptp-mitm

install: ptp-mitm
	mv -vn $(DVSDIR)/ptp $(DVSDIR)/ptp-original
	cp ptp-mitm $(DVSDIR)/ptp-mitm
	ln -s $(DVSDIR)/ptp-mitm $(DVSDIR)/ptp
	chown root:admin $(DVSDIR)/ptp
	chown root:admin $(DVSDIR)/ptp-mitm

uninstall: $(DVSDIR)/ptp-original
	mv -vn $(DVSDIR)/ptp $(DVSDIR)/ptp-backup
	$(RM) $(DVSDIR)/ptp-mitm
	cp -p $(DVSDIR)/ptp-original $(DVSDIR)/ptp

dir:
	@echo $(DVSDIR)
