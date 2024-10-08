#-- start of make_header -----------------

#====================================
#  Document ExamTruthMergeMap
#
#   Generated Sun Jan 23 18:49:19 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruthMergeMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthMergeMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruthMergeMap

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthMergeMap = /tmp/CMT_$(ExamTruth_tag)_ExamTruthMergeMap.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthMergeMap = $(ExamTruth_tag)_ExamTruthMergeMap.make
cmt_local_tagfile_ExamTruthMergeMap = $(bin)$(ExamTruth_tag)_ExamTruthMergeMap.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthMergeMap = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthMergeMap = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthMergeMap = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruthMergeMap)

ifdef cmt_ExamTruthMergeMap_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruthMergeMap = /tmp/CMT_ExamTruth_ExamTruthMergeMapsetup.make
cmt_local_ExamTruthMergeMap_makefile = /tmp/CMT_ExamTruthMergeMap$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthMergeMap = $(bin)ExamTruth_ExamTruthMergeMapsetup.make
cmt_local_ExamTruthMergeMap_makefile = $(bin)ExamTruthMergeMap.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruthMergeMap = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthMergeMap_makefile = /tmp/CMT_ExamTruthMergeMap$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthMergeMap = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthMergeMap_makefile = $(bin)ExamTruthMergeMap.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruthMergeMap ::


ifdef READONLY
ExamTruthMergeMap ::
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
	$(echo) 'ExamTruthMergeMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruthMergeMap/
ExamTruthMergeMap::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# File: cmt/fragments/merge_rootmap_header
# Author: Sebastien Binet (binet@cern.ch)

# Makefile fragment to merge a <library>.rootmap file into a single
# <project>.rootmap file in the (lib) install area
# If no InstallArea is present the fragment is dummy


.PHONY: ExamTruthMergeMap ExamTruthMergeMapclean

# default is already '#'
#genmap_comment_char := "'#'"

rootMapRef    := ../$(tag)/ExamTruth.rootmap

ifdef CMTINSTALLAREA
rootMapDir    := ${CMTINSTALLAREA}/$(tag)/lib
mergedRootMap := $(rootMapDir)/$(project).rootmap
stampRootMap  := $(rootMapRef).stamp
else
rootMapDir    := ../$(tag)
mergedRootMap := 
stampRootMap  :=
endif

ExamTruthMergeMap :: $(stampRootMap) $(mergedRootMap)
	@:

.NOTPARALLEL : $(stampRootMap) $(mergedRootMap)

$(stampRootMap) $(mergedRootMap) :: $(rootMapRef)
	@echo "Running merge_rootmap  ExamTruthMergeMap" 
	$(merge_rootmap_cmd) --do-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap)

ExamTruthMergeMapclean ::
	$(cleanup_silent) $(merge_rootmap_cmd) --un-merge \
         --input-file $(rootMapRef) --merged-file $(mergedRootMap) ;
	$(cleanup_silent) $(remove_command) $(stampRootMap)
libExamTruth_so_dependencies = ../x86_64-slc6-gcc44-opt/libExamTruth.so
#-- start of cleanup_header --------------

clean :: ExamTruthMergeMapclean
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

ExamTruthMergeMapclean ::
#-- end of cleanup_header ---------------
