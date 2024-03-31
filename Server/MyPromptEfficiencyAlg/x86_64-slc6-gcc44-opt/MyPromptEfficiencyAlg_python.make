#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlg_python
#
#   Generated Wed Jul 20 16:50:38 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlg_python_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlg_python_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlg_python

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make
cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlg_python)

ifdef cmt_MyPromptEfficiencyAlg_python_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlg_python = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_pythonsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlg_python = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_pythonsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = $(bin)MyPromptEfficiencyAlg_python.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlg_python = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlg_python = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = $(bin)MyPromptEfficiencyAlg_python.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlg_python ::


ifdef READONLY
MyPromptEfficiencyAlg_python ::
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
	$(echo) 'MyPromptEfficiencyAlg_python'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlg_python/
MyPromptEfficiencyAlg_python::
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

MyPromptEfficiencyAlg_python :: MyPromptEfficiencyAlg_pythoninstall

install :: MyPromptEfficiencyAlg_pythoninstall

MyPromptEfficiencyAlg_pythoninstall :: $(install_python_dir)
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

MyPromptEfficiencyAlg_pythonclean :: MyPromptEfficiencyAlg_pythonuninstall

uninstall :: MyPromptEfficiencyAlg_pythonuninstall

MyPromptEfficiencyAlg_pythonuninstall ::
	@if test "$(installarea)" = ""; then \
	  echo "Cannot uninstall header files, no installation source specified"; \
	else \
	  echo "Uninstalling files from $(dest)"; \
	  $(uninstall_command) "$(dest)" ; \
	fi


#-- end of install_python_header ------
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlg_pythonclean
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

MyPromptEfficiencyAlg_pythonclean ::
#-- end of cleanup_header ---------------
