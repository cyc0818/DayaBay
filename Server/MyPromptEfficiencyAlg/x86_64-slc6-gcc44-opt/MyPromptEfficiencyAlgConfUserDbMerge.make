#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgConfUserDbMerge
#
#   Generated Wed Jul 20 16:50:48 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgConfUserDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConfUserDbMerge_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgConfUserDbMerge

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge)

ifdef cmt_MyPromptEfficiencyAlgConfUserDbMerge_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfUserDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfUserDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfUserDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfUserDbMerge.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfUserDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfUserDbMerge.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgConfUserDbMerge ::


ifdef READONLY
MyPromptEfficiencyAlgConfUserDbMerge ::
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
	$(echo) 'MyPromptEfficiencyAlgConfUserDbMerge'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgConfUserDbMerge/
MyPromptEfficiencyAlgConfUserDbMerge::
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
 
.PHONY: MyPromptEfficiencyAlgConfUserDbMerge MyPromptEfficiencyAlgConfUserDbMergeclean

# default is already '#'
#genconfDb_comment_char := "'#'"

instdir      := ${CMTINSTALLAREA}
confDbRef    := /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/genConf/MyPromptEfficiencyAlg/MyPromptEfficiencyAlg_user_confDb.py
stampConfDb  := $(confDbRef).stamp
mergedConfDb := $(instdir)/python/$(subst .,_,$(subst -,_,$(project)))_merged_confDb.py

MyPromptEfficiencyAlgConfUserDbMerge :: $(stampConfDb) $(mergedConfDb)
	@:

.NOTPARALLEL : $(stampConfDb) $(mergedConfDb)

$(stampConfDb) $(mergedConfDb) :: $(confDbRef)
	@echo "Running merge_genconfDb  MyPromptEfficiencyAlgConfUserDbMerge"
	@touch $(mergedConfDb) 
	$(merge_genconfDb_cmd) \
          --do-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	  

MyPromptEfficiencyAlgConfUserDbMergeclean ::
	$(cleanup_silent) $(merge_genconfDb_cmd) \
          --un-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	;
	$(cleanup_silent) $(remove_command) $(stampConfDb)
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgConfUserDbMergeclean
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

MyPromptEfficiencyAlgConfUserDbMergeclean ::
#-- end of cleanup_header ---------------
