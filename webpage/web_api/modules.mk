mod_web_api.la: mod_web_api.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_web_api.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_web_api.la
