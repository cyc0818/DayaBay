#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgMergeMap
#
#   Generated Wed Jul 20 16:50:24 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgMergeMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgMergeMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgMergeMap

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap)

ifdef cmt_MyPromptEfficiencyAlgMergeMap_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgMergeMapsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgMergeMap$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgMergeMapsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = $(bin)MyPromptEfficiencyAlgMergeMap.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgMergeMap$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = $(bin)MyPromptEfficiencyAlgMergeMap.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgMergeMap ::


ifdef READONLY
MyPromptEfficiencyAlgMergeMap ::
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
	$(echo) 'MyPromptEfficiencyAlgMergeMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgMergeMap/
MyPromptEfficiencyAlgMergeMap::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# File: cmt/fragments/merge_rootmap_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>.rootmap file into a single
# <project>.rootmap file in the (lib) install area
# If no InstallArea is present the fragment is dummy


.PHONY: MyPromptEfficiencyAlgMergeMap MyPromptEfficiencyAlgMergeMapclean

# default is already '#'
#genmap_comment_char := "'#'"

rootMapRef    := ../$(tag)/MyPromptEfficiencyAlg.rootmap

ifdef CMTINSTALLAREA
rootMapDir    := ${CMTINSTALLAREA}/$(tag)/lib
mergedRootMap := $(rootMapDir)/$(project).rootmap
stampRootMap  := $(rootMapRef).stamp
else
rootMapDir    := ../$(tag)
mergedRootMap := 
stampRootMap  :=
endif

MyPromptEfficiencyAlgMergeMap :: $(stampRootMap) $(mergedRootMap)
	@:

.NOTPARALLEL : $(stampRootMap) $(mergedRootMap)

$(stampRootMap) $(mergedRootMap) :: $(rootMapRef)
	@echo "Running merge_rootmap  MyPromptEfficiencyAlgMergeMap" 
	$(merge_rootmap_cmd) --do-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap)

MyPromptEfficiencyAlgMergeMapclean ::
	$(cleanup_silent) $(merge_rootmap_cmd) --un-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap) ;
	$(cleanup_silent) $(remove_command) $(stampRootMap)
libMyPromptEfficiencyAlg_so_dependencies = ../x86_64-slc6-gcc44-opt/libMyPromptEfficiencyAlg.so
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgMergeMapclean
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

MyPromptEfficiencyAlgMergeMapclean ::
#-- end of cleanup_header ---------------
