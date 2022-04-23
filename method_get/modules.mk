mod_method_get.la: mod_method_get.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_method_get.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_method_get.la
