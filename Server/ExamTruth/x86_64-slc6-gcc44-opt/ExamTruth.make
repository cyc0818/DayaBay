#-- start of make_header -----------------

#====================================
#  Library ExamTruth
#
#   Generated Sun Jan 23 18:48:57 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ExamTruth_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ExamTruth

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth = /tmp/CMT_$(ExamTruth_tag)_ExamTruth.make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth = $(ExamTruth_tag)_ExamTruth.make
cmt_local_tagfile_ExamTruth = $(bin)$(ExamTruth_tag)_ExamTruth.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_ExamTruth = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_ExamTruth = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth = $(bin)$(ExamTruth_tag).make
endif

endif

-include $(cmt_local_tagfile_ExamTruth)

ifdef cmt_ExamTruth_has_target_tag

ifdef READONLY
cmt_final_setup_ExamTruth = /tmp/CMT_ExamTruth_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = /tmp/CMT_ExamTruth$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth = $(bin)ExamTruth_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = $(bin)ExamTruth.make
endif

else

ifdef READONLY
cmt_final_setup_ExamTruth = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = /tmp/CMT_ExamTruth$(cmt_lock_pid).make
else
cmt_final_setup_ExamTruth = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_makefile = $(bin)ExamTruth.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
cmt_final_setup = $(bin)ExamTruthsetup.make
endif

ExamTruth ::


ifdef READONLY
ExamTruth ::
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
	$(echo) 'ExamTruth'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ExamTruth/
ExamTruth::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of libary_header ---------------

ExamTruthlibname   = $(bin)$(library_prefix)ExamTruth$(library_suffix)
ExamTruthlib       = $(ExamTruthlibname).a
ExamTruthstamp     = $(bin)ExamTruth.stamp
ExamTruthshstamp   = $(bin)ExamTruth.shstamp

ExamTruth :: dirs  ExamTruthLIB
	$(echo) "ExamTruth ok"

#-- end of libary_header ----------------
#-- start of libary ----------------------

ExamTruthLIB :: $(ExamTruthlib) $(ExamTruthshstamp)
	$(echo) "ExamTruth : library ok"

$(ExamTruthlib) :: $(bin)XYCorr.o $(bin)ExamTruth_entries.o $(bin)EventTree.o $(bin)RZCorr.o $(bin)ExamTruth.o $(bin)ExamTruth_load.o
	$(lib_echo) "static library $@"
	$(lib_silent) cd $(bin); \
	  $(ar) $(ExamTruthlib) $?
	$(lib_silent) $(ranlib) $(ExamTruthlib)
	$(lib_silent) cat /dev/null >$(ExamTruthstamp)

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

$(ExamTruthlibname).$(shlibsuffix) :: $(ExamTruthlib) requirements $(use_requirements) $(ExamTruthstamps)
	$(lib_echo) "shared library $@"
	$(lib_silent) cd $(bin); if test "$(makecmd)"; then QUIET=; else QUIET=1; fi; QUIET=$${QUIET} $(make_shlib) "$(tags)" ExamTruth $(ExamTruth_shlibflags)

$(ExamTruthshstamp) :: $(ExamTruthlibname).$(shlibsuffix)
	$(lib_silent) if test -f $(ExamTruthlibname).$(shlibsuffix) ; then cat /dev/null >$(ExamTruthshstamp) ; fi

ExamTruthclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)XYCorr.o $(bin)ExamTruth_entries.o $(bin)EventTree.o $(bin)RZCorr.o $(bin)ExamTruth.o $(bin)ExamTruth_load.o
	$(cleanup_silent) cd $(bin); /bin/rm -rf ExamTruth_deps ExamTruth_dependencies.make

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/lib
ExamTruthinstallname = $(library_prefix)ExamTruth$(library_suffix).$(shlibsuffix)

ExamTruth :: ExamTruthinstall

install :: ExamTruthinstall

ExamTruthinstall :: $(install_dir)/$(ExamTruthinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(ExamTruthinstallname) :: $(bin)$(ExamTruthinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(ExamTruthinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##ExamTruthclean :: ExamTruthuninstall

uninstall :: ExamTruthuninstall

ExamTruthuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(ExamTruthinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#-- end of libary -----------------------
#-- start of dependency ------------------

#$(bin)ExamTruth_dependencies.make :: dirs

ifndef QUICK
$(bin)ExamTruth_dependencies.make : $(src)*.cc  $(use_requirements) $(cmt_final_setup_ExamTruth)
	$(echo) "(ExamTruth.make) Rebuilding $@"; \
	  $(build_dependencies) ExamTruth -all_sources
endif

#$(ExamTruth_dependencies)

-include $(bin)ExamTruth_dependencies.make

#-- end of dependency -------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(XYCorr_cc_dependencies)

$(bin)$(binobj)XYCorr.o : $(XYCorr_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)XYCorr.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(XYCorr_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(XYCorr_cppflags) $(XYCorr_cc_cppflags)  $(src)XYCorr.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(ExamTruth_entries_cc_dependencies)

$(bin)$(binobj)ExamTruth_entries.o : $(ExamTruth_entries_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)ExamTruth_entries.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(ExamTruth_entries_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(ExamTruth_entries_cppflags) $(ExamTruth_entries_cc_cppflags)  $(src)ExamTruth_entries.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(EventTree_cc_dependencies)

$(bin)$(binobj)EventTree.o : $(EventTree_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)EventTree.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(EventTree_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(EventTree_cppflags) $(EventTree_cc_cppflags)  $(src)EventTree.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(RZCorr_cc_dependencies)

$(bin)$(binobj)RZCorr.o : $(RZCorr_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)RZCorr.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(RZCorr_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(RZCorr_cppflags) $(RZCorr_cc_cppflags)  $(src)RZCorr.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(ExamTruth_cc_dependencies)

$(bin)$(binobj)ExamTruth.o : $(ExamTruth_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)ExamTruth.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(ExamTruth_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(ExamTruth_cppflags) $(ExamTruth_cc_cppflags)  $(src)ExamTruth.cc

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

$(bin)ExamTruth_dependencies.make : $(ExamTruth_load_cc_dependencies)

$(bin)$(binobj)ExamTruth_load.o : $(ExamTruth_load_cc_dependencies)
	$(cpp_echo) $<
	$(cpp_silent) cd $(bin); $(cppcomp) -o $(binobj)ExamTruth_load.o $(use_pp_cppflags) $(ExamTruth_pp_cppflags) $(lib_ExamTruth_pp_cppflags) $(ExamTruth_load_pp_cppflags) $(use_cppflags) $(ExamTruth_cppflags) $(lib_ExamTruth_cppflags) $(ExamTruth_load_cppflags) $(ExamTruth_load_cc_cppflags)  $(src)ExamTruth_load.cc

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: ExamTruthclean
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

ExamTruthclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(binobj)$(library_prefix)ExamTruth$(library_suffix).a $(binobj)$(library_prefix)ExamTruth$(library_suffix).s? $(binobj)ExamTruth.stamp $(binobj)ExamTruth.shstamp
#-- end of cleanup_library ---------------

