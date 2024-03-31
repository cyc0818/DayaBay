#-- start of make_header -----------------

#====================================
#  Document ExamTruth_python_init
#
#   Generated Sun Jan 23 18:49:28 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruth_python_init_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_python_init_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruth_python_init

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth_python_init = /tmp/CMT_$(ExamTruth_tag)_ExamTruth_python_init.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth_python_init = $(ExamTruth_tag)_ExamTruth_python_init.make
cmt_local_tagfile_ExamTruth_python_init = $(bin)$(ExamTruth_tag)_ExamTruth_python_init.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth_python_init = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth_python_init = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth_python_init = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruth_python_init)

ifdef cmt_ExamTruth_python_init_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruth_python_init = /tmp/CMT_ExamTruth_ExamTruth_python_initsetup.make
cmt_local_ExamTruth_python_init_makefile = /tmp/CMT_ExamTruth_python_init$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth_python_init = $(bin)ExamTruth_ExamTruth_python_initsetup.make
cmt_local_ExamTruth_python_init_makefile = $(bin)ExamTruth_python_init.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruth_python_init = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_python_init_makefile = /tmp/CMT_ExamTruth_python_init$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth_python_init = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_python_init_makefile = $(bin)ExamTruth_python_init.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruth_python_init ::


ifdef READONLY
ExamTruth_python_init ::
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
	$(echo) 'ExamTruth_python_init'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruth_python_init/
ExamTruth_python_init::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of python_init_header ------

installarea = ${CMTINSTALLAREA}
install_python_dir = $(installarea)/python/ExamTruth
init_file = $(install_python_dir)/__init__.py


ExamTruth_python_init :: ExamTruth_python_initinstall

install :: ExamTruth_python_initinstall

ExamTruth_python_initinstall :: $(init_file)

$(init_file) ::
	@if [ -e $(install_python_dir) -a ! -e $(init_file) ]; then \
	  echo "Installing __init__.py file from ${GAUDIPOLICYROOT}" ; \
	  $(install_command) ${GAUDIPOLICYROOT}/cmt/fragments/__init__.py $(install_python_dir) ; \
	fi

ExamTruth_python_initclean :: ExamTruth_python_inituninstall

uninstall :: ExamTruth_python_inituninstall

ExamTruth_python_inituninstall ::
	@$(uninstall_command) $(init_file)


#-- end of python_init_header ------
#-- start of cleanup_header --------------

clean :: ExamTruth_python_initclean
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

ExamTruth_python_initclean ::
#-- end of cleanup_header ---------------
