##########################
# Makefile Version 
##########################

MAKEFILE_VERSION := 2.2


##########################
# Config Options 
##########################

SHARED_LIB_TARGET ?= ""
EXCEPT_SHARED_LIB_TARGET ?= ""


##########################
# Output Files 
##########################

OUTPUT_Debug := $(OUTDIR)/Debug/unit_testd
OUTPUT_Release := $(OUTDIR)/Release/unit_test


##########################
# List up Source Files 
##########################

SRCS_All :=
SRCS_All += ../algorithm/bubble_sort_test.cpp
SRCS_All += ../algorithm/heap_sort_test.cpp
SRCS_All += ../algorithm/insertion_sort_test.cpp
SRCS_All += ../algorithm/tim_sort_test.cpp
SRCS_All += ../algorithm/radix_sort_test.cpp
SRCS_All += ../algorithm/quick_sort_test.cpp
SRCS_All += ../algorithm/selection_sort_test.cpp
SRCS_All += app.cpp

HDRS_All :=
HDRS_All += ../algorithm/bubble_sort.hpp
HDRS_All += ../algorithm/heap_sort.hpp
HDRS_All += ../algorithm/insertion_sort.hpp
HDRS_All += ../algorithm/tim_sort.hpp
HDRS_All += ../algorithm/radix_sort.cpp
HDRS_All += ../algorithm/quick_sort.hpp
HDRS_All += ../algorithm/selection_sort.hpp

OBJS_All :=


##########################
# Makedefs include 
##########################

ifneq ($(wildcard Makedefs.private), )
include Makedefs.private
endif

ifeq ($(MAKEDEFS),)
include Makedefs
MAKEDEFS = `pwd`/Makedefs
else
include $(MAKEDEFS)
endif

MAKEFLAGS += --no-print-directory -s
SRCS_Debug := $(SRCS_All)

SRCS_Release := $(SRCS_All)

HDRS_Debug := $(HDRS_All)

HDRS_Release := $(HDRS_All)


##############################
# List up Sub Library Paths
##############################

SUBDIRS_Debug := ../Debug 
SUBDIRS_Release := ../Release


##############################
# Build Paths
##############################

OUTDIR := _BUILD/OUTPUT
OUTDIR_LIBRARY := ../$(OUTDIR)/Library


###########################
# List up Compile Options 
###########################

DEFINES_All := 
CFLAGS_All := --std=c++11 -Wall -Wextra -Wwrite-strings -Werror=vla -Werror=return-type -fexceptions --coverage
INCLUDES_All := -I./ -I../

DEFINES_Debug := $(DEFINES_All) -D_DEBUG
CFLAGS_Debug := $(CFLAGS_All) -g
INCLUDES_Debug := $(INCLUDES_All) 

DEFINES_Release := $(DEFINES_All) 
CFLAGS_Release := $(CFLAGS_All) -O3
INCLUDES_Release := $(INCLUDES_All) 


###########################
# List up Link Options 
###########################

LFLAGS_All := 
LFLAGS_Debug := $(LFLAGS_All) -L$(OUTDIR_LIBRARY)/Debug
LFLAGS_Release := $(LFLAGS_All) -L$(OUTDIR_LIBRARY)/Release
LFLAGS_Release += -s


###########################
# List up Link Libraries
###########################

LIBS_All := -lJrCore -lgtest -lpthread -lrt -lgcov
LIBS_Debug := $(LIBS_All)
LIBS_Release := $(LIBS_All)


#####################
# compile & link custorm setting
#####################

CC_CUSTOM ?= ccache $(CROSS_COMPILE)gcc
CXX_CUSTOM ?= ccache $(CROSS_COMPILE)g++
LINK_CUSTOM ?= $(CROSS_COMPILE)g++
STRIP_CUSTOM ?= $(CROSS_COMPILE)strip
AR_CUSTOM ?= $(CROSS_COMPILE)ar
WINDRES_CUSTOM ?= $(CROSS_COMPILE)windres


#####################
# compile & link
#####################

CC = $(CC_CUSTOM)
CXX = $(CXX_CUSTOM)
LINK = $(LINK_CUSTOM)
STRIP = $(STRIP_CUSTOM)
AR = $(AR_CUSTOM)
WINDRES = $(WINDRES_CUSTOM)
MAKEDEP_CC = $(CC) -MM -MP
MAKEDEP_CXX = $(CXX) -MM -MP
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

OUTDIR_Debug = $(OUTDIR)/unit_test/Debug
OBJS_Debug = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug)/%.o, $(patsubst %.cc, $(OUTDIR_Debug)/%.o, $(patsubst %.c, $(OUTDIR_Debug)/%.o, $(SRCS_Debug)))))
DEPENDS_Debug = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug)/%.d, $(patsubst %.cc, $(OUTDIR_Debug)/%.d, $(patsubst %.c, $(OUTDIR_Debug)/%.d, $(SRCS_Debug)))))
RES_Debug = $(patsubst %.rc, $(OUTDIR_Debug)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Debug)))))

OUTDIR_Release = $(OUTDIR)/unit_test/Release
OBJS_Release = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release)/%.o, $(patsubst %.cc, $(OUTDIR_Release)/%.o, $(patsubst %.c, $(OUTDIR_Release)/%.o, $(SRCS_Release)))))
DEPENDS_Release = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release)/%.d, $(patsubst %.cc, $(OUTDIR_Release)/%.d, $(patsubst %.c, $(OUTDIR_Release)/%.d, $(SRCS_Release)))))
RES_Release = $(patsubst %.rc, $(OUTDIR_Release)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Release)))))

.SUFFIXES: .c .cc .cpp .o .d .res .rc

$(OUTDIR_Debug)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) -o $@ $<

$(OUTDIR_Debug)/%.o: %.cc
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) -o $@ $<

$(OUTDIR_Debug)/%.res: %.rc
	@$(MKDIR) $(dir $@)
	@echo "[RC ] $@"
	@$(WINDRES) -O coff -c $(INCLUDES) $(INCLUDES_Debug) -o $@ $<

$(OUTDIR_Debug)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@echo "[ C ] $@"
	@$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) -o $@ $<

$(OUTDIR_Debug)/%.d: %.cpp
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cpp) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) $< \

$(OUTDIR_Debug)/%.d: %.cc
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cc) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) $< \

$(OUTDIR_Debug)/%.d: %.c
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .c) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CC) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Debug) $(CFLAGS_Debug) $(INCLUDES_Debug) $< \

$(OUTDIR_Release)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) -o $@ $<

$(OUTDIR_Release)/%.o: %.cc
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) -o $@ $<

$(OUTDIR_Release)/%.res: %.rc
	@$(MKDIR) $(dir $@)
	@echo "[RC ] $@"
	@$(WINDRES) -O coff -c $(INCLUDES) $(INCLUDES_Release) -o $@ $<

$(OUTDIR_Release)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@echo "[ C ] $@"
	@$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) -o $@ $<

$(OUTDIR_Release)/%.d: %.cpp
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cpp) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) $< \

$(OUTDIR_Release)/%.d: %.cc
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cc) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) $< \

$(OUTDIR_Release)/%.d: %.c
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .c) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CC) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Release) $(CFLAGS_Release) $(INCLUDES_Release) $< \

#####################
# TARGET
#####################

TARGET ?= Release

ifeq ($(TARGET),Debug)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Debug)
all : build
real_build : $(OUTDIR)/Debug/unit_testd
$(OUTDIR)/Debug/unit_testd : $(OBJS_Debug) $(RES_Debug) $(SUBDIRS_Debug)
	@echo "---------------------------------------------------------------"
	@echo "DEFINES : $(strip $(DEFINES))"
	@echo "DEFINES_Debug : $(strip $(DEFINES_Debug))"
	@echo "CFLAGS : $(strip $(CFLAGS))"
	@echo "CFLAGS_Debug : $(strip $(CFLAGS_Debug))"
	@echo "CXXFLAGS : $(strip $(CXXFLAGS))"
	@echo "CXXFLAGS_Debug : $(strip $(CXXFLAGS_Debug))"
	@echo "LFLAGS : $(strip $(LFLAGS))"
	@echo "LFLAGS_Debug : $(strip $(LFLAGS_Debug))"
	@echo "INCLUDES : $(strip $(INCLUDES))"
	@echo "INCLUDES_Debug : $(strip $(INCLUDES_Debug))"
	@echo "---------------------------------------------------------------"
	@echo "Linking a execution file $(OUTDIR)/Debug/unit_testd"
	@$(MKDIR) $(dir $(OUTDIR)/Debug/unit_testd)
	@$(LINK) -o $(OUTDIR)/Debug/unit_testd $(OBJS_Debug) $(RES_Debug) $(LFLAGS) $(LFLAGS_Debug) $(LIBS_Debug) $(OBJS_All)

$(SUBDIRS_Debug):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f "$${OUTPUT_FILE}" ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif

ifeq ($(TARGET),Release)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Release)
all : build
real_build : $(OUTDIR)/Release/unit_test
$(OUTDIR)/Release/unit_test : $(OBJS_Release) $(RES_Release) $(SUBDIRS_Release)
	@echo "---------------------------------------------------------------"
	@echo "DEFINES : $(strip $(DEFINES))"
	@echo "DEFINES_Release : $(strip $(DEFINES_Release))"
	@echo "CFLAGS : $(strip $(CFLAGS))"
	@echo "CFLAGS_Release : $(strip $(CFLAGS_Release))"
	@echo "CXXFLAGS : $(strip $(CXXFLAGS))"
	@echo "CXXFLAGS_Release : $(strip $(CXXFLAGS_Release))"
	@echo "LFLAGS : $(strip $(LFLAGS))"
	@echo "LFLAGS_Release : $(strip $(LFLAGS_Release))"
	@echo "INCLUDES : $(strip $(INCLUDES))"
	@echo "INCLUDES_Release : $(strip $(INCLUDES_Release))"
	@echo "---------------------------------------------------------------"
	@echo "Linking a execution file $(OUTDIR)/Release/unit_test"
	@$(MKDIR) $(dir $(OUTDIR)/Release/unit_test)
	@$(LINK) -o $(OUTDIR)/Release/unit_test $(OBJS_Release) $(RES_Release) $(LFLAGS) $(LFLAGS_Release) $(LIBS_Release) $(OBJS_All)
	@cp -f $(OUTDIR)/Release/unit_test $(OUTDIR)/Release/unit_test.debug
	@$(STRIP) -d $(OUTDIR)/Release/unit_test

$(SUBDIRS_Release):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f "$${OUTPUT_FILE}" ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif

appclean : 
	$(RM) $(OBJS_$(TARGET))
	$(RM) $(RES_$(TARGET))
ifeq ($(TARGET),Debug)
	$(RM) $(OUTDIR)/Debug/unit_testd
endif
ifeq ($(TARGET),Release)
	$(RM) $(OUTDIR)/Release/unit_test
endif


clean : 
	$(RM) $(OBJS_$(TARGET))
	$(RM) $(RES_$(TARGET))
ifeq ($(TARGET),Debug)
	@for D in $(SUBDIRS_Debug); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Debug/unit_testd
endif
ifeq ($(TARGET),Release)
	@for D in $(SUBDIRS_Release); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Release/unit_test
endif

prescript : 
ifeq ($(TARGET),Debug)
endif
ifeq ($(TARGET),Release)
endif

prebuild : prescript
	@$(MAKE) real_build TARGET=$(TARGET) MAKEDEFS=$(MAKEDEFS)

build : prebuild

rebuild : cleanoutput
	+$(MAKE) build TARGET=$(TARGET) MAKEDEFS=$(MAKEDEFS)

Makedefs :
	@echo "use $@ for specifying CFLAGS, DEFINES, INCLUDES, or CROSS_COMPILE setting"
	@echo "generates an empty file"
	@touch $@
	@echo -e "CFLAGS = \nCXXFLAGS = \nDEFINES = \nINCLUDES = \nCROSS_COMPILE = " > $@


cleanoutput : 
	@for D in $(SUBDIRS_$(TARGET)); do \
		echo "clean output dir `dirname $$D`"; \
		CWD=`pwd`;DIR=`dirname $$D`;cd $$DIR;rm -rf `basename $$D`;cd $$CWD; \
	done

USE_DEPENDS ?= yes
ifneq ($(USE_DEPENDS), no)
ifeq ($(filter $(MAKECMDGOALS), appclean clean cleanoutput tags sources cscope Makedefs prebuild),)
ifeq ($(TARGET), Debug)
-include $(DEPENDS_Debug)
endif
ifeq ($(TARGET), Release)
-include $(DEPENDS_Release)
endif
endif
endif

sources : 
	@echo "$(SRCS_All) $(HDRS_All)"

tags : 
	@SRCS="$(SRCS_All) $(HDRS_All)"; \
	for D in $(SUBDIRS_$(TARGET)); do \
		DIR=`dirname $$D`; \
		LIB_SRCS=`make -C $$DIR sources -s`; \
		for S in $$LIB_SRCS; do \
			SRCS="$$SRCS $$DIR/$$S"; \
		done; \
	done; \
	ctags $$SRCS

cscope : 
	@SRCS="$(SRCS_All) $(HDRS_All)"; \
	for D in $(SUBDIRS_$(TARGET)); do \
		DIR=`dirname $$D`; \
		LIB_SRCS=`make -C $$DIR sources -s`; \
		for S in $$LIB_SRCS; do \
			SRCS="$$SRCS $$DIR/$$S"; \
		done; \
	done; \
	ls $$SRCS | xargs -i readlink -f {} > cscope.files; \
	cscope -b -i cscope.files

depinfo : $(DEPENDS_$(TARGET))
	@(cd $(OUTDIR_$(TARGET)) && find . -name "*.d" | xargs wc -l | sed '$$d' | sort)

print_output : 
	@echo $(OUTPUT_$(TARGET))


