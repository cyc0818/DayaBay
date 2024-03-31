#-- start of make_header -----------------

#====================================
#  Document ExamTruthRootMap
#
#   Generated Sun Jan 23 18:49:16 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruthRootMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthRootMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruthRootMap

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthRootMap = /tmp/CMT_$(ExamTruth_tag)_ExamTruthRootMap.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthRootMap = $(ExamTruth_tag)_ExamTruthRootMap.make
cmt_local_tagfile_ExamTruthRootMap = $(bin)$(ExamTruth_tag)_ExamTruthRootMap.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthRootMap = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthRootMap = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthRootMap = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruthRootMap)

ifdef cmt_ExamTruthRootMap_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruthRootMap = /tmp/CMT_ExamTruth_ExamTruthRootMapsetup.make
cmt_local_ExamTruthRootMap_makefile = /tmp/CMT_ExamTruthRootMap$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthRootMap = $(bin)ExamTruth_ExamTruthRootMapsetup.make
cmt_local_ExamTruthRootMap_makefile = $(bin)ExamTruthRootMap.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruthRootMap = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthRootMap_makefile = /tmp/CMT_ExamTruthRootMap$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthRootMap = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthRootMap_makefile = $(bin)ExamTruthRootMap.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruthRootMap ::


ifdef READONLY
ExamTruthRootMap ::
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
	$(echo) 'ExamTruthRootMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruthRootMap/
ExamTruthRootMap::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

##
rootmapfile = ExamTruth.rootmap
ROOTMAP_DIR = ../$(tag)
fulllibname = libExamTruth.$(shlibsuffix)

ExamTruthRootMap :: ${ROOTMAP_DIR}/$(rootmapfile)
	@:

${ROOTMAP_DIR}/$(rootmapfile) :: $(bin)$(fulllibname)
	@echo 'Generating rootmap file for $(fulllibname)'
	cd ../$(tag);$(genmap_cmd) -i $(fulllibname) -o ${ROOTMAP_DIR}/$(rootmapfile) $(ExamTruthRootMap_genmapflags)

install :: ExamTruthRootMapinstall
ExamTruthRootMapinstall :: ExamTruthRootMap

uninstall :: ExamTruthRootMapuninstall
ExamTruthRootMapuninstall :: ExamTruthRootMapclean

ExamTruthRootMapclean ::
	@echo 'Deleting $(rootmapfile)'
	@rm -f ${ROOTMAP_DIR}/$(rootmapfile)

#-- start of cleanup_header --------------

clean :: ExamTruthRootMapclean
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

ExamTruthRootMapclean ::
#-- end of cleanup_header ---------------
