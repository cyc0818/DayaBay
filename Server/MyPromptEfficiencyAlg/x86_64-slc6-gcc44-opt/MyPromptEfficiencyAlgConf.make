#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgConf
#
#   Generated Wed Jul 20 16:50:28 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConf_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgConf

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConf = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make
cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConf = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgConf)

ifdef cmt_MyPromptEfficiencyAlgConf_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConf = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = /tmp/CMT_MyPromptEfficiencyAlgConf$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConf = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = $(bin)MyPromptEfficiencyAlgConf.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConf = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = /tmp/CMT_MyPromptEfficiencyAlgConf$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConf = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = $(bin)MyPromptEfficiencyAlgConf.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgConf ::


ifdef READONLY
MyPromptEfficiencyAlgConf ::
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
	$(echo) 'MyPromptEfficiencyAlgConf'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgConf/
MyPromptEfficiencyAlgConf::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# File: cmt/fragments/genconfig_header
# Author: Wim Lavrijsen (WLavrijsen@lbl.gov)

# Use genconf.exe to create configurables python modules, then have the
# normal python install procedure take over.

.PHONY: MyPromptEfficiencyAlgConf MyPromptEfficiencyAlgConfclean

confpy  := MyPromptEfficiencyAlgConf.py
conflib := $(bin)$(library_prefix)MyPromptEfficiencyAlg.$(shlibsuffix)
dbpy    := MyPromptEfficiencyAlg_confDb.py
instdir := $(CMTINSTALLAREA)/python/$(package)
product := $(instdir)/$(confpy)
initpy  := $(instdir)/__init__.py


MyPromptEfficiencyAlgConf :: MyPromptEfficiencyAlgConfinstall

install :: MyPromptEfficiencyAlgConfinstall

MyPromptEfficiencyAlgConfinstall : /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/$(confpy)
	@echo "Installing /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg in /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python" ; \
	 $(install_command) --exclude="*.py?" --exclude="__init__.py" /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python ; \

/dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/$(confpy) : $(conflib) /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg
	@$(genconfig_cmd)  -o /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg -p $(package) \
	  --configurable-module=GaudiKernel.Proxy \
	  --configurable-default-name=Configurable.DefaultName \
	  --configurable-algorithm=ConfigurableAlgorithm \
	  --configurable-algtool=ConfigurableAlgTool \
	  --configurable-auditor=ConfigurableAuditor \
          --configurable-service=ConfigurableService \
	  -i ../$(tag)/$(library_prefix)MyPromptEfficiencyAlg.$(shlibsuffix) 

/dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg:
	@ if [ ! -d /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg ] ; then mkdir -p /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg ; fi ; 

MyPromptEfficiencyAlgConfclean :: MyPromptEfficiencyAlgConfuninstall
	$(cleanup_silent) $(remove_command) /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/$(confpy) /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/$(dbpy)

uninstall :: MyPromptEfficiencyAlgConfuninstall

MyPromptEfficiencyAlgConfuninstall :: 
	@$(uninstall_command) /dybfs2/users/yuchincheng/workdir/IBD/InstallArea/python
libMyPromptEfficiencyAlg_so_dependencies = ../x86_64-slc6-gcc44-opt/libMyPromptEfficiencyAlg.so
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgConfclean
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

MyPromptEfficiencyAlgConfclean ::
#-- end of cleanup_header ---------------
