# Module definition
EXTRA_DIST = mod-python-def.xml python.example.conf
SUBDIRS = doc

INCLUDES = $(compiler_options) -Wall -g -ansi $(TURBULENCE_CFLAGS) -I../../src -DCOMPILATION_DATE=`date +%s` \
	-DVERSION=\"$(VERSION)\" \
	$(AXL_CFLAGS) $(VORTEX_CFLAGS) $(EXARG_CFLAGS) $(PYTHON_CFLAGS) $(PY_VORTEX_CFLAGS)

# configure module binary
lib_LTLIBRARIES      = mod_python.la
mod_python_la_SOURCES  = mod_python.c \
		py_turbulence.c py_turbulence.h \
		py_turbulence_ctx.c py_turbulence_ctx.h
mod_python_la_LDFLAGS  = -module -ldl $(PYTHON_LIBS) $(PY_VORTEX_LIBS)

# reconfigure module installation directory
libdir = $(prefix)/lib/turbulence/modules

# configure site module installation
moddir   = $(sysconfdir)/turbulence/mods-available
mod_DATA = mod-python.xml

# configure site module configuration installation
modconfdir   = $(sysconfdir)/turbulence/python
modconf_DATA = python.example.conf

mod-python.xml mod-python.win32.xml:
	echo "<mod-turbulence location=\"$(prefix)/lib/turbulence/modules/mod_python.so\"/>" > mod-python.xml
	echo "<mod-turbulence location=\"../modules/mod_python.dll\"/>" > mod-python.win32.xml


