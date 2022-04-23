mod_get_header.la: mod_get_header.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_get_header.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_get_header.la
