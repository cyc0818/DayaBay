#-- start of make_header -----------------

#====================================
#  Document ExamTruthGenConfUser
#
#   Generated Sun Jan 23 18:49:24 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruthGenConfUser_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthGenConfUser_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruthGenConfUser

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthGenConfUser = /tmp/CMT_$(ExamTruth_tag)_ExamTruthGenConfUser.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthGenConfUser = $(ExamTruth_tag)_ExamTruthGenConfUser.make
cmt_local_tagfile_ExamTruthGenConfUser = $(bin)$(ExamTruth_tag)_ExamTruthGenConfUser.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruthGenConfUser = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruthGenConfUser = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthGenConfUser = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruthGenConfUser)

ifdef cmt_ExamTruthGenConfUser_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruthGenConfUser = /tmp/CMT_ExamTruth_ExamTruthGenConfUsersetup.make
cmt_local_ExamTruthGenConfUser_makefile = /tmp/CMT_ExamTruthGenConfUser$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthGenConfUser = $(bin)ExamTruth_ExamTruthGenConfUsersetup.make
cmt_local_ExamTruthGenConfUser_makefile = $(bin)ExamTruthGenConfUser.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruthGenConfUser = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthGenConfUser_makefile = /tmp/CMT_ExamTruthGenConfUser$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruthGenConfUser = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthGenConfUser_makefile = $(bin)ExamTruthGenConfUser.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruthGenConfUser ::


ifdef READONLY
ExamTruthGenConfUser ::
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
	$(echo) 'ExamTruthGenConfUser'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruthGenConfUser/
ExamTruthGenConfUser::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# ============= call_command_header:begin =============
deps        = $(ExamTruthGenConfUser_deps)
command     = $(ExamTruthGenConfUser_command)
output      = $(ExamTruthGenConfUser_output)

.PHONY: ExamTruthGenConfUser ExamTruthGenConfUserclean

ExamTruthGenConfUser :: $(output)

ExamTruthGenConfUserclean ::
	$(cmt_uninstallarea_command) $(output)

$(output):: $(deps)
	$(command)
# ============= call_command_header:end =============
#-- start of cleanup_header --------------

clean :: ExamTruthGenConfUserclean
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

ExamTruthGenConfUserclean ::
#-- end of cleanup_header ---------------
