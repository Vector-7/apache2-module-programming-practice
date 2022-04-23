mod_hello_apache.la: mod_hello_apache.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_hello_apache.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_hello_apache.la
