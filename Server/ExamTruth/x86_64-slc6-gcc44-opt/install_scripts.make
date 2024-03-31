#-- start of make_header -----------------

#====================================
#  Document install_scripts
#
#   Generated Sun Jan 23 18:49:32 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_install_scripts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_install_scripts_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_install_scripts

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_install_scripts = /tmp/CMT_$(ExamTruth_tag)_install_scripts.make$(cmt_lock_pid)
else
#cmt_local_tagfile_install_scripts = $(ExamTruth_tag)_install_scripts.make
cmt_local_tagfile_install_scripts = $(bin)$(ExamTruth_tag)_install_scripts.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_install_scripts = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_install_scripts = $(ExamTruth_tag).make
cmt_local_tagfile_install_scripts = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_install_scripts)

ifdef cmt_install_scripts_has_target_tag

ifdef READONLY
cmt_final_setup_install_scripts = /tmp/CMT_ExamTruth_install_scriptssetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
cmt_final_setup_install_scripts = $(bin)ExamTruth_install_scriptssetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make
endif

else

ifdef READONLY
cmt_final_setup_install_scripts = /tmp/CMT_ExamTruthsetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
cmt_final_setup_install_scripts = $(bin)ExamTruthsetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

install_scripts ::


ifdef READONLY
install_scripts ::
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
	$(echo) 'install_scripts'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = install_scripts/
install_scripts::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of install_scripts_header ------


installarea = ${CMTINSTALLAREA}
install_scripts_dir = $(installarea)/.

install_scripts :: install_scriptsinstall

install :: install_scriptsinstall

install_scriptsinstall :: $(install_scripts_dir)
	@if [ ! "$(installarea)" = "" ]; then\
	  echo "installation done"; \
	fi

$(install_scripts_dir) ::
	@if [ "$(installarea)" = "" ]; then \
	  echo "Cannot install header files, no installation source specified"; \
	else \
      src=../scripts ; \
	  dest=$(install_scripts_dir) ; \
	  if [ -d $$src ]; then \
	     echo "Installing files from source $$src to $$dest"; \
	     $(install_command) --exclude="*.py?" $$src $$dest ;\
	     chmod -R +x $$dest ; \
	  else \
	     echo "no source  $$src"; \
	  fi; \
	fi

install_scriptsclean :: install_scriptsuninstall

uninstall :: install_scriptsuninstall

install_scriptsuninstall ::
	@if test "$(installarea)" = ""; then \
	  echo "Cannot uninstall header files, no installation source specified"; \
	else \
      dest=$(install_scripts_dir) ; \
	  echo "Uninstalling files from $$dest"; \
	  $(uninstall_command) "$${dest}" ; \
	fi


#-- end of install_more_includes_header ------
#-- start of cleanup_header --------------

clean :: install_scriptsclean
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

install_scriptsclean ::
#-- end of cleanup_header ---------------
