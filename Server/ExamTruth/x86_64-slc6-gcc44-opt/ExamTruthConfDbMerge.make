#-- start of make_header -----------------

#====================================
#  Document ExamTruthConfDbMerge
#
#   Generated Sun Jan 23 18:49:30 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruthConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthConfDbMerge_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruthConfDbMerge

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthConfDbMerge = /tmp/CMT_$(ExamTruth_tag)_ExamTruthConfDbMerge.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthConfDbMerge = $(ExamTruth_tag)_ExamTruthConfDbMerge.make
cmt_local_tagfile_ExamTruthConfDbMerge = $(bin)$(ExamTruth_tag)_ExamTruthConfDbMerge.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthConfDbMerge = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthConfDbMerge = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthConfDbMerge = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruthConfDbMerge)

ifdef cmt_ExamTruthConfDbMerge_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruthConfDbMerge = /tmp/CMT_ExamTruth_ExamTruthConfDbMergesetup.make
cmt_local_ExamTruthConfDbMerge_makefile = /tmp/CMT_ExamTruthConfDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthConfDbMerge = $(bin)ExamTruth_ExamTruthConfDbMergesetup.make
cmt_local_ExamTruthConfDbMerge_makefile = $(bin)ExamTruthConfDbMerge.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruthConfDbMerge = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthConfDbMerge_makefile = /tmp/CMT_ExamTruthConfDbMerge$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthConfDbMerge = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthConfDbMerge_makefile = $(bin)ExamTruthConfDbMerge.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruthConfDbMerge ::


ifdef READONLY
ExamTruthConfDbMerge ::
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
	$(echo) 'ExamTruthConfDbMerge'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruthConfDbMerge/
ExamTruthConfDbMerge::
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
 
.PHONY: ExamTruthConfDbMerge ExamTruthConfDbMergeclean

# default is already '#'
#genconfDb_comment_char := "'#'"

instdir      := ${CMTINSTALLAREA}
confDbRef    := /dybfs2/users/yuchincheng/workdir/IBD/code/ExamTruth/genConf/ExamTruth/ExamTruth_confDb.py
stampConfDb  := $(confDbRef).stamp
mergedConfDb := $(instdir)/python/$(subst .,_,$(subst -,_,$(project)))_merged_confDb.py

ExamTruthConfDbMerge :: $(stampConfDb) $(mergedConfDb)
	@:

.NOTPARALLEL : $(stampConfDb) $(mergedConfDb)

$(stampConfDb) $(mergedConfDb) :: $(confDbRef)
	@echo "Running merge_genconfDb  ExamTruthConfDbMerge"
	@touch $(mergedConfDb) 
	$(merge_genconfDb_cmd) \
          --do-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	  

ExamTruthConfDbMergeclean ::
	$(cleanup_silent) $(merge_genconfDb_cmd) \
          --un-merge \
          --input-file $(confDbRef) \
          --merged-file $(mergedConfDb)	;
	$(cleanup_silent) $(remove_command) $(stampConfDb)
libExamTruth_so_dependencies = ../x86_64-slc6-gcc44-opt/libExamTruth.so
#-- start of cleanup_header --------------

clean :: ExamTruthConfDbMergeclean
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

ExamTruthConfDbMergeclean ::
#-- end of cleanup_header ---------------
