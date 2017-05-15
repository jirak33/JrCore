##########################
# Makefile Version 
##########################

MAKEFILE_VERSION := 2.2


##########################
# Config Options 
##########################

SHARED_LIB_TARGET ?= ""
EXCEPT_SHARED_LIB_TARGET ?= ""


##############################
# Build Paths
##############################

OUTDIR := ./_BUILD/OUTPUT
OUTDIR_LIBRARY := $(OUTDIR)/Library


##########################
# Output Files 
##########################

OUTPUT_Debug := $(OUTDIR_LIBRARY)/Debug/libJrCore.a
OUTPUT_Release := $(OUTDIR_LIBRARY)/Release/libJrCore.a
OUTPUT_Debug_UnitTest := $(OUTDIR_LIBRARY)/Debug/libJrCore.a
OUTPUT_Release_UnitTest := $(OUTDIR_LIBRARY)/Release/libJrCore.a


##########################
# List up Source Files 
##########################

SRCS_All :=
SRCS_All += utils/data_util.cpp
SRCS_All += utils/random_util.cpp
SRCS_All += utils/string_util.cpp
SRCS_All += utils/tick_util.cpp

HDRS_All :=
HDRS_All += algorithm/bubble_sort.hpp
HDRS_All += algorithm/heap_sort.hpp
HDRS_All += algorithm/insertion_sort.hpp
HDRS_All += algorithm/quick_sort.hpp
HDRS_All += algorithm/selection_sort.hpp
HDRS_All += base/stack.hpp
HDRS_All += base/type.hpp
HDRS_All += utils/data_util.hpp
HDRS_All += utils/random_util.hpp
HDRS_All += utils/string_util.hpp
HDRS_All += utils/tick_util.hpp

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

SRCS_Debug_UnitTest := $(SRCS_All)

SRCS_Release_UnitTest := $(SRCS_All)

HDRS_Debug := $(HDRS_All)

HDRS_Release := $(HDRS_All)

HDRS_Debug_UnitTest := $(HDRS_All)

HDRS_Release_UnitTest := $(HDRS_All)

SRCS_Release_UnitTest += algorithm/bubble_sort_test.cpp
SRCS_Release_UnitTest += algorithm/heap_sort_test.cpp
SRCS_Release_UnitTest += algorithm/insertion_sort_test.cpp
SRCS_Release_UnitTest += algorithm/quick_sort_test.cpp
SRCS_Release_UnitTest += algorithm/selection_sort_test.cpp

SRCS_Debug_UnitTest += algorithm/bubble_sort_test.cpp
SRCS_Debug_UnitTest += algorithm/heap_sort_test.cpp
SRCS_Debug_UnitTest += algorithm/insertion_sort_test.cpp
SRCS_Debug_UnitTest += algorithm/quick_sort_test.cpp
SRCS_Debug_UnitTest += algorithm/selection_sort_test.cpp


###########################
# List up Compile Options 
###########################

DEFINES_All :=
CFLAGS_All := --std=c++11 -Wall -Wwrite-strings -Werror=vla -Werror=return-type -isystem .
INCLUDES_All :=

DEFINES_Debug := $(DEFINES_All) -D_DEBUG
CFLAGS_Debug := $(CFLAGS_All) -g
INCLUDES_Debug := $(INCLUDES_All) 

DEFINES_Release := $(DEFINES_All) 
CFLAGS_Release := $(CFLAGS_All) -O3
INCLUDES_Release := $(INCLUDES_All) 

DEFINES_Debug_UnitTest := $(DEFINES_All) -D_DEBUG
CFLAGS_Debug_UnitTest := $(CFLAGS_All) -g -fexceptions --coverage
INCLUDES_Debug_UnitTest := $(INCLUDES_All) 

DEFINES_Release_UnitTest := $(DEFINES_All) 
CFLAGS_Release_UnitTest := $(CFLAGS_All) -O3 -fexceptions --coverage
INCLUDES_Release_UnitTest := $(INCLUDES_All) 


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

OUTDIR_Debug = $(OUTDIR)/JrCore/Debug
OBJS_Debug = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug)/%.o, $(patsubst %.cc, $(OUTDIR_Debug)/%.o, $(patsubst %.c, $(OUTDIR_Debug)/%.o, $(SRCS_Debug)))))
DEPENDS_Debug = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug)/%.d, $(patsubst %.cc, $(OUTDIR_Debug)/%.d, $(patsubst %.c, $(OUTDIR_Debug)/%.d, $(SRCS_Debug)))))
RES_Debug = $(patsubst %.rc, $(OUTDIR_Debug)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Debug)))))

OUTDIR_Release = $(OUTDIR)/JrCore/Release
OBJS_Release = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release)/%.o, $(patsubst %.cc, $(OUTDIR_Release)/%.o, $(patsubst %.c, $(OUTDIR_Release)/%.o, $(SRCS_Release)))))
DEPENDS_Release = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release)/%.d, $(patsubst %.cc, $(OUTDIR_Release)/%.d, $(patsubst %.c, $(OUTDIR_Release)/%.d, $(SRCS_Release)))))
RES_Release = $(patsubst %.rc, $(OUTDIR_Release)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Release)))))

OUTDIR_Debug_UnitTest = $(OUTDIR)/JrCore/Debug_UnitTest
OBJS_Debug_UnitTest = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug_UnitTest)/%.o, $(patsubst %.cc, $(OUTDIR_Debug_UnitTest)/%.o, $(patsubst %.c, $(OUTDIR_Debug_UnitTest)/%.o, $(SRCS_Debug_UnitTest)))))
DEPENDS_Debug_UnitTest = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Debug_UnitTest)/%.d, $(patsubst %.cc, $(OUTDIR_Debug_UnitTest)/%.d, $(patsubst %.c, $(OUTDIR_Debug_UnitTest)/%.d, $(SRCS_Debug_UnitTest)))))
RES_Debug_UnitTest = $(patsubst %.rc, $(OUTDIR_Debug_UnitTest)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Debug_UnitTest)))))

OUTDIR_Release_UnitTest = $(OUTDIR)/JrCore/Release_UnitTest
OBJS_Release_UnitTest = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release_UnitTest)/%.o, $(patsubst %.cc, $(OUTDIR_Release_UnitTest)/%.o, $(patsubst %.c, $(OUTDIR_Release_UnitTest)/%.o, $(SRCS_Release_UnitTest)))))
DEPENDS_Release_UnitTest = $(patsubst %.rc,, $(patsubst %.cpp, $(OUTDIR_Release_UnitTest)/%.d, $(patsubst %.cc, $(OUTDIR_Release_UnitTest)/%.d, $(patsubst %.c, $(OUTDIR_Release_UnitTest)/%.d, $(SRCS_Release_UnitTest)))))
RES_Release_UnitTest = $(patsubst %.rc, $(OUTDIR_Release_UnitTest)/%.res, $(patsubst %.cpp,, $(patsubst %.cc,, $(patsubst %.c,, $(SRCS_Release_UnitTest)))))

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

$(OUTDIR_Debug_UnitTest)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) -o $@ $<

$(OUTDIR_Debug_UnitTest)/%.o: %.cc
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) -o $@ $<

$(OUTDIR_Debug_UnitTest)/%.res: %.rc
	@$(MKDIR) $(dir $@)
	@echo "[RC ] $@"
	@$(WINDRES) -O coff -c $(INCLUDES) $(INCLUDES_Debug_UnitTest) -o $@ $<

$(OUTDIR_Debug_UnitTest)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@echo "[ C ] $@"
	@$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) -o $@ $<

$(OUTDIR_Debug_UnitTest)/%.d: %.cpp
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cpp) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) $< \

$(OUTDIR_Debug_UnitTest)/%.d: %.cc
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cc) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) $< \

$(OUTDIR_Debug_UnitTest)/%.d: %.c
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .c) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CC) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Debug_UnitTest) $(CFLAGS_Debug_UnitTest) $(INCLUDES_Debug_UnitTest) $< \

$(OUTDIR_Release_UnitTest)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) -o $@ $<

$(OUTDIR_Release_UnitTest)/%.o: %.cc
	@$(MKDIR) $(dir $@)
	@echo "[C++] $@"
	@$(CXX) -c $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) -o $@ $<

$(OUTDIR_Release_UnitTest)/%.res: %.rc
	@$(MKDIR) $(dir $@)
	@echo "[RC ] $@"
	@$(WINDRES) -O coff -c $(INCLUDES) $(INCLUDES_Release_UnitTest) -o $@ $<

$(OUTDIR_Release_UnitTest)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@echo "[ C ] $@"
	@$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) -o $@ $<

$(OUTDIR_Release_UnitTest)/%.d: %.cpp
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cpp) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) $< \

$(OUTDIR_Release_UnitTest)/%.d: %.cc
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .cc) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CXX) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(CXXFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) $< \

$(OUTDIR_Release_UnitTest)/%.d: %.c
	@$(MKDIR) $(dir $@)
	@rm -f $@
	@echo "[DEP] $(@:%.d=%.o) (for .c) ..."
	echo -n $@ `dirname $@`/>> $@; \
	$(MAKEDEP_CC) -MF $@ -MT $(@:%.d=%.o) $(DEFINES) $(CFLAGS) $(INCLUDES) $(DEFINES_Release_UnitTest) $(CFLAGS_Release_UnitTest) $(INCLUDES_Release_UnitTest) $< \


#####################
# TARGET
#####################

TARGET ?= Release

ifeq ($(TARGET),Debug)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Debug)
all : build
real_build : $(OUTDIR_LIBRARY)/Debug/libJrCore.a
$(OUTDIR_LIBRARY)/Debug/libJrCore.a : $(OBJS_Debug) $(RES_Debug) $(SUBDIRS_Debug)
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
	@echo "Linking a static library $(OUTDIR)/Debug/libJrCore.a"
	@$(MKDIR) $(dir $(OUTDIR_LIBRARY)/Debug/libJrCore.a)
	@$(AR) rcs $(OUTDIR_LIBRARY)/Debug/libJrCore.a $(OBJS_Debug) $(RES_Debug)

$(SUBDIRS_Debug):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f $${OUTPUT_FILE} ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif


ifeq ($(TARGET),Release)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Release)
all : build
real_build : $(OUTDIR_LIBRARY)/Release/libJrCore.a
$(OUTDIR_LIBRARY)/Release/libJrCore.a : $(OBJS_Release) $(RES_Release) $(SUBDIRS_Release)
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
	@echo "Linking a static library $(OUTDIR_LIBRARY)/Release/libJrCore.a"
	@$(MKDIR) $(dir $(OUTDIR_LIBRARY)/Release/libJrCore.a)
	@$(AR) rcs $(OUTDIR_LIBRARY)/Release/libJrCore.a $(OBJS_Release) $(RES_Release)

$(SUBDIRS_Release):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f $${OUTPUT_FILE} ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif


ifeq ($(TARGET),Debug_UnitTest)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Debug_UnitTest)
all : build
real_build : $(OUTDIR)/Debug/libJrCore.a
$(OUTDIR)/Debug/libJrCore.a : $(OBJS_Debug_UnitTest) $(RES_Debug_UnitTest) $(SUBDIRS_Debug_UnitTest)
	@echo "---------------------------------------------------------------"
	@echo "DEFINES : $(strip $(DEFINES))"
	@echo "DEFINES_Debug_UnitTest : $(strip $(DEFINES_Debug_UnitTest))"
	@echo "CFLAGS : $(strip $(CFLAGS))"
	@echo "CFLAGS_Debug_UnitTest : $(strip $(CFLAGS_Debug_UnitTest))"
	@echo "CXXFLAGS : $(strip $(CXXFLAGS))"
	@echo "CXXFLAGS_Debug_UnitTest : $(strip $(CXXFLAGS_Debug_UnitTest))"
	@echo "LFLAGS : $(strip $(LFLAGS))"
	@echo "LFLAGS_Debug_UnitTest : $(strip $(LFLAGS_Debug_UnitTest))"
	@echo "INCLUDES : $(strip $(INCLUDES))"
	@echo "INCLUDES_Debug_UnitTest : $(strip $(INCLUDES_Debug_UnitTest))"
	@echo "---------------------------------------------------------------"
	@echo "Linking a static library $(OUTDIR)/Debug/libJrCore.a"
	@$(MKDIR) $(dir $(OUTDIR)/Debug/libJrCore.a)
	@$(AR) rcs $(OUTDIR)/Debug/libJrCore.a $(OBJS_Debug_UnitTest) $(RES_Debug_UnitTest)

$(SUBDIRS_Debug_UnitTest):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f $${OUTPUT_FILE} ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif

ifeq ($(TARGET),Release_UnitTest)
.PHONY : depinfo cscope tags sources real_build appclean clean prescript prebuild build rebuild $(SUBDIRS_Release_UnitTest)
all : build
real_build : $(OUTDIR)/Release/libJrCore.a
$(OUTDIR)/Release/libJrCore.a : $(OBJS_Release_UnitTest) $(RES_Release_UnitTest) $(SUBDIRS_Release_UnitTest)
	@echo "---------------------------------------------------------------"
	@echo "DEFINES : $(strip $(DEFINES))"
	@echo "DEFINES_Release_UnitTest : $(strip $(DEFINES_Release_UnitTest))"
	@echo "CFLAGS : $(strip $(CFLAGS))"
	@echo "CFLAGS_Release_UnitTest : $(strip $(CFLAGS_Release_UnitTest))"
	@echo "CXXFLAGS : $(strip $(CXXFLAGS))"
	@echo "CXXFLAGS_Release_UnitTest : $(strip $(CXXFLAGS_Release_UnitTest))"
	@echo "LFLAGS : $(strip $(LFLAGS))"
	@echo "LFLAGS_Release_UnitTest : $(strip $(LFLAGS_Release_UnitTest))"
	@echo "INCLUDES : $(strip $(INCLUDES))"
	@echo "INCLUDES_Release_UnitTest : $(strip $(INCLUDES_Release_UnitTest))"
	@echo "---------------------------------------------------------------"
	@echo "Linking a static library $(OUTDIR)/Release/libJrCore.a"
	@$(MKDIR) $(dir $(OUTDIR)/Release/libJrCore.a)
	@$(AR) rcs $(OUTDIR)/Release/libJrCore.a $(OBJS_Release_UnitTest) $(RES_Release_UnitTest)

$(SUBDIRS_Release_UnitTest):
	@(echo "building sub-project `dirname $@` (`basename $@`)"; \
		OUTPUT_FILE=`$(MAKE) -C \`dirname $@\` print_output TARGET=\`basename $@\` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS)`; \
		if [ "$(LIB_USE_CACHE)" == "yes" ] && [ -f $${OUTPUT_FILE} ]; then \
			echo "use cache"; \
		else \
			set -e; $(MAKE) -C `dirname $@` build TARGET=`basename $@` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
		fi)
endif

appclean : 
	$(RM) $(OBJS_$(TARGET))
	$(RM) $(RES_$(TARGET))
ifeq ($(TARGET),Debug)
	$(RM) $(OUTDIR)/Debug/libJrCore.a
endif
ifeq ($(TARGET),Release)
	$(RM) $(OUTDIR)/Release/libJrCore.a
endif
ifeq ($(TARGET),Debug_UnitTest)
	$(RM) $(OUTDIR)/Debug/libJrCore.a
endif
ifeq ($(TARGET),Release_UnitTest)
	$(RM) $(OUTDIR)/Release/libJrCore.a
endif


clean : 
	$(RM) $(OBJS_$(TARGET))
	$(RM) $(RES_$(TARGET))
ifeq ($(TARGET),Debug)
	@for D in $(SUBDIRS_Debug); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Debug/libJrCore.a
endif
ifeq ($(TARGET),Release)
	@for D in $(SUBDIRS_Release); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Release/libJrCore.a
endif
ifeq ($(TARGET),Debug_UnitTest)
	@for D in $(SUBDIRS_Debug_UnitTest); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Debug/libJrCore.a
endif
ifeq ($(TARGET),Release_UnitTest)
	@for D in $(SUBDIRS_Release_UnitTest); do \
		echo "clean sub-project `dirname $$D` (`basename $$D`)"; \
		$(MAKE) -C `dirname $$D` clean TARGET=`basename $$D` OUTDIR="$(OUTDIR_LIBRARY)" MAKEDEFS=$(MAKEDEFS); \
	done
	$(RM) $(OUTDIR)/Release/libJrCore.a
endif

prescript : 
ifeq ($(TARGET),Debug)
endif
ifeq ($(TARGET),Release)
endif
ifeq ($(TARGET),Debug_UnitTest)
endif
ifeq ($(TARGET),Release_UnitTest)
endif

prebuild : prescript
	@$(MAKE) real_build TARGET=$(TARGET) MAKEDEFS=$(MAKEDEFS)

build : prebuild
ifeq ($(TARGET),Debug)
endif
ifeq ($(TARGET),Release)
endif
ifeq ($(TARGET),Debug_UnitTest)
endif
ifeq ($(TARGET),Release_UnitTest)
endif

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
ifeq ($(TARGET), Debug_UnitTest)
-include $(DEPENDS_Debug_UnitTest)
endif
ifeq ($(TARGET), Release_UnitTest)
-include $(DEPENDS_Release_UnitTest)
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



