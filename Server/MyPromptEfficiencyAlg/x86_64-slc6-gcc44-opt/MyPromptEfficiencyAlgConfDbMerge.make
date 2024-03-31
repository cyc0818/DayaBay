#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgConfDbMerge
#
#   Generated Wed Jul 20 16:50:42 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConfDbMerge_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgConfDbMerge

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge)

ifdef cmt_MyPromptEfficiencyAlgConfDbMerge_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfDbMerge.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfDbMerge.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgConfDbMerge ::


ifdef READONLY
MyPromptEfficiencyAlgConfDbMerge ::
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
	$(echo) 'MyPromptEfficiencyAlgConfDbMerge'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgConfDbMerge/
MyPromptEfficiencyAlgConfDbMerge::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# File: cmt/fragments/merge_genconfDb_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>_confDb.py file into a single
# <project>_merged_confDb.py file in the (python) install area
# Note that <project> is massaged to get a valid python module name 
# (ie: remove dots and dashes)
 
.PHONY: MyPromptEfficiencyAlgConfDbMerge MyPromptEfficiencyAlgConfDbMergeclean

# default is already '#'
#genconfDb_comment_char := "'#'"

instdir      := ${CMTINSTALLAREA}
confDbRef    := /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/MyPromptEfficiencyAlg_confDb.py
stampConfDb  := $(confDbRef).stamp
mergedConfDb := $(instdir)/python/$(subst .,_,$(subst -,_,$(project)))_merged_confDb.py

MyPromptEfficiencyAlgConfDbMerge :: $(stampConfDb) $(mergedConfDb)
	@:

.NOTPARALLEL : $(stampConfDb) $(mergedConfDb)

$(stampConfDb) $(mergedConfDb) :: $(confDbRef)
	@echo "Running merge_genconfDb  MyPromptEfficiencyAlgConfDbMerge"
	@touch $(mergedConfDb) 
	$(merge_genconfDb_cmd) \
          --do-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	  

MyPromptEfficiencyAlgConfDbMergeclean ::
	$(cleanup_silent) $(merge_genconfDb_cmd) \
          --un-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	;
	$(cleanup_silent) $(remove_command) $(stampConfDb)
libMyPromptEfficiencyAlg_so_dependencies = ../x86_64-slc6-gcc44-opt/libMyPromptEfficiencyAlg.so
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgConfDbMergeclean
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

MyPromptEfficiencyAlgConfDbMergeclean ::
#-- end of cleanup_header ---------------
