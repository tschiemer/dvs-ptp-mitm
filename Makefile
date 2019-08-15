CC?=gcc
DVSDIR?=/Library/Application\ Support/Audinate/DanteVirtualSoundcard

h: help
help:
	@cat README.md

b: build
build: ptp-mitm.c
	$(CC) -o ptp-mitm ptp-mitm.c

c: clean
clean:
	$(RM) ptp-mitm

install: ptp-mitm
	install -b -o root -g admin $(DVSDIR)/ptp $(DVSDIR)/ptp-original
	$(RM) $(DVSDIR)/ptp
	install -b -o root -g admin ptp-mitm $(DVSDIR)/ptp

uninstall: $(DVSDIR)/ptp-original
	$(RM) $(DVSDIR)/ptp
	mv $(DVSDIR)/ptp-original $(DVSDIR)/ptp

dir:
	@echo $(DVSDIR)
