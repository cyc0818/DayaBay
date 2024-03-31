#-- start of make_header -----------------

#====================================
#  Library MyPromptEfficiencyAlg
#
#   Generated Wed Jul 20 16:49:47 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlg

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlg = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make
cmt_local_tagfile_MyPromptEfficiencyAlg = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlg = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlg = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlg)

ifdef cmt_MyPromptEfficiencyAlg_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlg = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = /tmp/CMT_MyPromptEfficiencyAlg$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlg = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = $(bin)MyPromptEfficiencyAlg.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlg = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = /tmp/CMT_MyPromptEfficiencyAlg$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlg = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = $(bin)MyPromptEfficiencyAlg.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlg ::


ifdef READONLY
MyPromptEfficiencyAlg ::
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
	$(echo) 'MyPromptEfficiencyAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlg/
MyPromptEfficiencyAlg::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

MyPromptEfficiencyAlglibname   = $(bin)$(library_prefix)MyPromptEfficiencyAlg$(library_suffix)
MyPromptEfficiencyAlglib       = $(MyPromptEfficiencyAlglibname).a
MyPromptEfficiencyAlgstamp     = $(bin)MyPromptEfficiencyAlg.stamp
MyPromptEfficiencyAlgshstamp   = $(bin)MyPromptEfficiencyAlg.shstamp

MyPromptEfficiencyAlg :: dirs  MyPromptEfficiencyAlgLIB
	$(echo) "MyPromptEfficiencyAlg ok"

#-- end of libary_header ----------------
#-- start of libary ----------------------

MyPromptEfficiencyAlgLIB :: $(MyPromptEfficiencyAlglib) $(MyPromptEfficiencyAlgshstamp)
	$(echo) "MyPromptEfficiencyAlg : library ok"

$(MyPromptEfficiencyAlglib) :: $(bin)MyPromptEfficiencyAlg_load.o $(bin)MyPromptEfficiencyAlg.o $(bin)MyPromptEfficiencyAlg_entries.o
	$(lib_echo) "static library $@"
	$(lib_silent) cd $(bin); \
	  $(ar) $(MyPromptEfficiencyAlglib) $?
	$(lib_silent) $(ranlib) $(MyPromptEfficiencyAlglib)
	$(lib_silent) cat /dev/null >$(MyPromptEfficiencyAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

#
# We add one level of dependency upon the true shared library 
# (rather than simply upon the stamp file)
# this is for cases where the shared library has not been built
# while the stamp was created (error??) 
#

$(MyPromptEfficiencyAlglibname).$(shlibsuffix) :: $(MyPromptEfficiencyAlglib) requirements $(use_requirements) $(MyPromptEfficiencyAlgstamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) cd $(bin); if test "$(makecmd)"; then QUIET=; else QUIET=1; fi; QUIET=$${QUIET} $(make_shlib) "$(tags)" MyPromptEfficiencyAlg $(MyPromptEfficiencyAlg_shlibflags)

$(MyPromptEfficiencyAlgshstamp) :: $(MyPromptEfficiencyAlglibname).$(shlibsuffix)
	$(lib_silent) if test -f $(MyPromptEfficiencyAlglibname).$(shlibsuffix) ; then cat /dev/null >$(MyPromptEfficiencyAlgshstamp) ; fi

MyPromptEfficiencyAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)MyPromptEfficiencyAlg_load.o $(bin)MyPromptEfficiencyAlg.o $(bin)MyPromptEfficiencyAlg_entries.o
	$(cleanup_silent) cd $(bin); /bin/rm -rf MyPromptEfficiencyAlg_deps MyPromptEfficiencyAlg_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
MyPromptEfficiencyAlginstallname = $(library_prefix)MyPromptEfficiencyAlg$(library_suffix).$(shlibsuffix)

MyPromptEfficiencyAlg :: MyPromptEfficiencyAlginstall

install :: MyPromptEfficiencyAlginstall

MyPromptEfficiencyAlginstall :: $(install_dir)/$(MyPromptEfficiencyAlginstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(MyPromptEfficiencyAlginstallname) :: $(bin)$(MyPromptEfficiencyAlginstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(MyPromptEfficiencyAlginstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##MyPromptEfficiencyAlgclean :: MyPromptEfficiencyAlguninstall

uninstall :: MyPromptEfficiencyAlguninstall

MyPromptEfficiencyAlguninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(MyPromptEfficiencyAlginstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of libary -----------------------
#-- start of dependency ------------------

#$(bin)MyPromptEfficiencyAlg_dependencies.make :: dirs

ifndef QUICK
$(bin)MyPromptEfficiencyAlg_dependencies.make : $(src)*.cc  $(use_requirements) $(cmt_final_setup_MyPromptEfficiencyAlg)
	$(echo) "(MyPromptEfficiencyAlg.make) Rebuilding $@"; \
	  $(build_dependencies) MyPromptEfficiencyAlg -all_sources
endif

#$(MyPromptEfficiencyAlg_dependencies)

-include $(bin)MyPromptEfficiencyAlg_dependencies.make

#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)MyPromptEfficiencyAlg_dependencies.make : $(MyPromptEfficiencyAlg_load_cc_dependencies)

$(bin)$(binobj)MyPromptEfficiencyAlg_load.o : $(MyPromptEfficiencyAlg_load_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)MyPromptEfficiencyAlg_load.o $(use_pp_cppflags) $(MyPromptEfficiencyAlg_pp_cppflags) $(lib_MyPromptEfficiencyAlg_pp_cppflags) $(MyPromptEfficiencyAlg_load_pp_cppflags) $(use_cppflags) $(MyPromptEfficiencyAlg_cppflags) $(lib_MyPromptEfficiencyAlg_cppflags) $(MyPromptEfficiencyAlg_load_cppflags) $(MyPromptEfficiencyAlg_load_cc_cppflags)  $(src)MyPromptEfficiencyAlg_load.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)MyPromptEfficiencyAlg_dependencies.make : $(MyPromptEfficiencyAlg_cc_dependencies)

$(bin)$(binobj)MyPromptEfficiencyAlg.o : $(MyPromptEfficiencyAlg_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)MyPromptEfficiencyAlg.o $(use_pp_cppflags) $(MyPromptEfficiencyAlg_pp_cppflags) $(lib_MyPromptEfficiencyAlg_pp_cppflags) $(MyPromptEfficiencyAlg_pp_cppflags) $(use_cppflags) $(MyPromptEfficiencyAlg_cppflags) $(lib_MyPromptEfficiencyAlg_cppflags) $(MyPromptEfficiencyAlg_cppflags) $(MyPromptEfficiencyAlg_cc_cppflags)  $(src)MyPromptEfficiencyAlg.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)MyPromptEfficiencyAlg_dependencies.make : $(MyPromptEfficiencyAlg_entries_cc_dependencies)

$(bin)$(binobj)MyPromptEfficiencyAlg_entries.o : $(MyPromptEfficiencyAlg_entries_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)MyPromptEfficiencyAlg_entries.o $(use_pp_cppflags) $(MyPromptEfficiencyAlg_pp_cppflags) $(lib_MyPromptEfficiencyAlg_pp_cppflags) $(MyPromptEfficiencyAlg_entries_pp_cppflags) $(use_cppflags) $(MyPromptEfficiencyAlg_cppflags) $(lib_MyPromptEfficiencyAlg_cppflags) $(MyPromptEfficiencyAlg_entries_cppflags) $(MyPromptEfficiencyAlg_entries_cc_cppflags)  $(src)MyPromptEfficiencyAlg_entries.cc

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgclean
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

MyPromptEfficiencyAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)MyPromptEfficiencyAlg$(library_suffix).a $(binobj)$(library_prefix)MyPromptEfficiencyAlg$(library_suffix).s? $(binobj)MyPromptEfficiencyAlg.stamp $(binobj)MyPromptEfficiencyAlg.shstamp
#-- end of cleanup_library ---------------

