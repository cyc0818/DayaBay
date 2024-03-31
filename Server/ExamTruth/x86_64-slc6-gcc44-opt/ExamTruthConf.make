#-- start of make_header -----------------

#====================================
#  Document ExamTruthConf
#
#   Generated Sun Jan 23 18:49:21 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruthConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthConf_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruthConf

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthConf = /tmp/CMT_$(ExamTruth_tag)_ExamTruthConf.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthConf = $(ExamTruth_tag)_ExamTruthConf.make
cmt_local_tagfile_ExamTruthConf = $(bin)$(ExamTruth_tag)_ExamTruthConf.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthConf = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthConf = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthConf = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruthConf)

ifdef cmt_ExamTruthConf_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruthConf = /tmp/CMT_ExamTruth_ExamTruthConfsetup.make
cmt_local_ExamTruthConf_makefile = /tmp/CMT_ExamTruthConf$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthConf = $(bin)ExamTruth_ExamTruthConfsetup.make
cmt_local_ExamTruthConf_makefile = $(bin)ExamTruthConf.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruthConf = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthConf_makefile = /tmp/CMT_ExamTruthConf$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthConf = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthConf_makefile = $(bin)ExamTruthConf.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruthConf ::


ifdef READONLY
ExamTruthConf ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'ExamTruthConf'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruthConf/
ExamTruthConf::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# File: cmt/fragments/genconfig_header
# Author: Wim Lavrijsen (WLavrijsen@lbl.gov)

# Use genconf.exe to create configurables python modules, then have the
# normal python install procedure take over.

.PHONY: ExamTruthConf ExamTruthConfclean

confpy  := ExamTruthConf.py
conflib := $(bin)$(library_prefix)ExamTruth.$(shlibsuffix)
dbpy    := ExamTruth_confDb.py
instdir := $(CMTINSTALLAREA)/python/$(package)
product := $(instdir)/$(confpy)
initpy  := $(instdir)/__init__.py


ExamTruthConf :: ExamTruthConfinstall

install :: ExamTruthConfinstall

ExamTruthConfinstall : /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth/$(confpy)
	@echo "Installing /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth in /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python" ; \
	 $(install_command) --exclude="*.py?" --exclude="__init__.py" /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python ; \

/dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth/$(confpy) : $(conflib) /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth
	@$(genconfig_cmd)  -o /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth -p $(package) \
	  --configurable-module=GaudiKernel.Proxy \
	  --configurable-default-name=Configurable.DefaultName \
	  --configurable-algorithm=ConfigurableAlgorithm \
	  --configurable-algtool=ConfigurableAlgTool \
	  --configurable-auditor=ConfigurableAuditor \
          --configurable-service=ConfigurableService \
	  -i ../$(tag)/$(library_prefix)ExamTruth.$(shlibsuffix) 

/dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth:
	@ if [ ! -d /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth ] ; then mkdir -p /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth ; fi ; 

ExamTruthConfclean :: ExamTruthConfuninstall
	$(cleanup_silent) $(remove_command) /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth/$(confpy) /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth/$(dbpy)

uninstall :: ExamTruthConfuninstall

ExamTruthConfuninstall :: 
	@$(uninstall_command) /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python
libExamTruth_so_dependencies = ../x86_64-slc6-gcc44-opt/libExamTruth.so
#-- start of cleanup_header --------------

clean :: ExamTruthConfclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	@echo "#CMT> PEDANTIC MODE >> No rule for target $@" >&2
	@if test `expr index $@ '.'` != 0 ; \
	then  echo "#CMT> PEDANTIC MODE >> $@ seems to be a missing file, please check" >&2; exit -1 ;\
	else echo "#CMT> PEDANTIC MODE >>  $@ seems to be a fake target due to some pattern. Just ignore it." >&2 ; exit 0; fi; 		
endif

ExamTruthConfclean ::
#-- end of cleanup_header ---------------
