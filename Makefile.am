SUBDIRS = src/plataform/linux
#ifeq ($(TARGET_CPU),x86)
# TARGET_CPU_IS_X86 := 1
#else ifeq ($(TARGET_CPU),x86_64)
#  TARGET_CPU_IS_X86 := 1
#else
#  TARGET_CPU_IS_X86 := 0

EXTRA_DIST = README THANKS TODO HACKING MAINTAINERS Resources doc .git

CLEANFILES = *~

ACLOCAL_AMFLAGS = -I m4

details:
	@echo "Building from:"
	@echo "build_cpu = $(build_cpu), build_os = $(build_os), build_vendor = $(build_vendor)"
	@echo "To:"
	@echo "host_cpu = $(host_cpu), host_os = $(host_os), host_vendor = $(host_vendor)"

license:
	if test -f /usr/share/common-licenses/GPL-2 ; then \
		echo Updating license from /usr/share/common-licenses/GPL-2 ; \
		cat /usr/share/common-licenses/GPL-2 > COPYING ; \
	else \
		echo "You need run apt-get install base-files" ; \
	fi

html-doc:
	cd doc ; \
	doxygen Doxfile ; \
	cd ../
