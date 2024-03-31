#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgGenConfUser
#
#   Generated Wed Jul 20 16:50:35 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgGenConfUser_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgGenConfUser_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgGenConfUser

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser)

ifdef cmt_MyPromptEfficiencyAlgGenConfUser_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgGenConfUsersetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = /tmp/CMT_MyPromptEfficiencyAlgGenConfUser$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgGenConfUsersetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = $(bin)MyPromptEfficiencyAlgGenConfUser.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = /tmp/CMT_MyPromptEfficiencyAlgGenConfUser$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = $(bin)MyPromptEfficiencyAlgGenConfUser.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgGenConfUser ::


ifdef READONLY
MyPromptEfficiencyAlgGenConfUser ::
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
	$(echo) 'MyPromptEfficiencyAlgGenConfUser'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgGenConfUser/
MyPromptEfficiencyAlgGenConfUser::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

# ============= call_command_header:begin =============
deps        = $(MyPromptEfficiencyAlgGenConfUser_deps)
command     = $(MyPromptEfficiencyAlgGenConfUser_command)
output      = $(MyPromptEfficiencyAlgGenConfUser_output)

.PHONY: MyPromptEfficiencyAlgGenConfUser MyPromptEfficiencyAlgGenConfUserclean

MyPromptEfficiencyAlgGenConfUser :: $(output)

MyPromptEfficiencyAlgGenConfUserclean ::
	$(cmt_uninstallarea_command) $(output)

$(output):: $(deps)
	$(command)
# ============= call_command_header:end =============
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgGenConfUserclean
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

MyPromptEfficiencyAlgGenConfUserclean ::
#-- end of cleanup_header ---------------
