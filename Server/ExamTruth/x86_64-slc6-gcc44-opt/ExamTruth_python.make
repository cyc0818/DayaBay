#-- start of make_header -----------------

#====================================
#  Document ExamTruth_python
#
#   Generated Sun Jan 23 18:49:26 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruth_python_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_python_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruth_python

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth_python = /tmp/CMT_$(ExamTruth_tag)_ExamTruth_python.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth_python = $(ExamTruth_tag)_ExamTruth_python.make
cmt_local_tagfile_ExamTruth_python = $(bin)$(ExamTruth_tag)_ExamTruth_python.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth_python = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth_python = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth_python = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruth_python)

ifdef cmt_ExamTruth_python_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruth_python = /tmp/CMT_ExamTruth_ExamTruth_pythonsetup.make
cmt_local_ExamTruth_python_makefile = /tmp/CMT_ExamTruth_python$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth_python = $(bin)ExamTruth_ExamTruth_pythonsetup.make
cmt_local_ExamTruth_python_makefile = $(bin)ExamTruth_python.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruth_python = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_python_makefile = /tmp/CMT_ExamTruth_python$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth_python = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_python_makefile = $(bin)ExamTruth_python.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruth_python ::


ifdef READONLY
ExamTruth_python ::
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
	$(echo) 'ExamTruth_python'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruth_python/
ExamTruth_python::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of install_python_header ------


installarea = ${CMTINSTALLAREA}
install_python_dir = $(installarea)

ifneq ($(strip "$(source)"),"")
src = ../$(source)
dest = $(install_python_dir)/python
else
src = ../python
dest = $(install_python_dir)
endif

ifneq ($(strip "$(offset)"),"")
dest = $(install_python_dir)/python
endif

ExamTruth_python :: ExamTruth_pythoninstall

install :: ExamTruth_pythoninstall

ExamTruth_pythoninstall :: $(install_python_dir)
	@if [ ! "$(installarea)" = "" ] ; then\
	  echo "installation done"; \
	fi

$(install_python_dir) ::
	@if [ "$(installarea)" = "" ] ; then \
	  echo "Cannot install header files, no installation source specified"; \
	else \
	  if [ -d $(src) ] ; then \
	    echo "Installing files from $(src) to $(dest)" ; \
	    if [ "$(offset)" = "" ] ; then \
	      $(install_command) --exclude="*.py?" $(src) $(dest) ; \
	    else \
	      $(install_command) --exclude="*.py?" $(src) $(dest) --destname $(offset); \
	    fi ; \
	  else \
	    echo "no source  $(src)"; \
	  fi; \
	fi

ExamTruth_pythonclean :: ExamTruth_pythonuninstall

uninstall :: ExamTruth_pythonuninstall

ExamTruth_pythonuninstall ::
	@if test "$(installarea)" = ""; then \
	  echo "Cannot uninstall header files, no installation source specified"; \
	else \
	  echo "Uninstalling files from $(dest)"; \
	  $(uninstall_command) "$(dest)" ; \
	fi


#-- end of install_python_header ------
#-- start of cleanup_header --------------

clean :: ExamTruth_pythonclean
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

ExamTruth_pythonclean ::
#-- end of cleanup_header ---------------
