mod_method_post.la: mod_method_post.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_method_post.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_method_post.la
