BDLIB = $(top_srcdir)/src/libbdlib.a
BDLIB_UNITS = $(top_srcdir)/src/libbdlib_units.a

depcomp = /bin/sh $(top_srcdir)/build/autotools/depcomp

%.o : %.cpp
#	@echo -e "[+] Compiling: \033[1m$*\033[0m"
	@echo -e "[CC]	$<"
ifeq ($(CCDEPMODE),gcc3)
	if $(CXX) -MT '$@' -MD -MP -MF '.deps/$*.TPo' $(CXXFLAGS) -c $< -o $@; then \
	mv '.deps/$*.TPo' '.deps/$*.Po'; \
	else rm -f '.deps/$*.Tpo'; exit 1; \
	fi
else
	source='$<' object='$@' depfile='.deps/$*.Po' tmpdepfile='.deps/$*.TPo' depmode=$(CCDEPMODE) $(depcomp) \
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

%.o : %.c
#	@echo -e "[+] Compiling: \033[1m$*\033[0m"
	@echo -e "[CC]	$<"
ifeq ($(CCDEPMODE),gcc3)
	if $(CXX) -MT '$@' -MD -MP -MF '.deps/$*.TPo' $(CXXFLAGS) -c $< -o $@; then \
	mv '.deps/$*.TPo' '.deps/$*.Po'; \
	else rm -f '.deps/$*.Tpo'; exit 1; \
	fi
else
	source='$<' object='$@' depfile='.deps/$*.Po' tmpdepfile='.deps/$*.TPo' depmode=$(CCDEPMODE) $(depcomp) \
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif
