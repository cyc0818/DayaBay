
#-- start of constituents_header ------

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

tags      = $(tag),$(CMTEXTRATAGS)

ExamTruth_tag = $(tag)

ifdef READONLY
cmt_local_tagfile = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile = $(ExamTruth_tag).make
cmt_local_tagfile = $(bin)$(ExamTruth_tag).make
endif

#-include $(cmt_local_tagfile)
include $(cmt_local_tagfile)

ifdef READONLY
cmt_local_setup = /tmp/CMT_ExamTruthsetup$(cmt_lock_pid).make
cmt_final_setup = /tmp/CMT_ExamTruthsetup.make
else
#cmt_local_setup = $(bin)ExamTruthsetup$(cmt_lock_pid).make
cmt_local_setup = $(bin)$(package)setup$$$$.make
#cmt_final_setup = $(bin)ExamTruthsetup.make
cmt_final_setup = $(bin)$(package)setup.make
endif

#--------------------------------------------------------

#cmt_lock_setup = /tmp/lock$(cmt_lock_pid).make
#cmt_temp_tag = /tmp/tag$(cmt_lock_pid).make

#first :: $(cmt_local_tagfile)
#	@echo $(cmt_local_tagfile) ok
ifndef QUICK
first :: $(cmt_final_setup) ;
else
first :: ;
endif

##	@bin=`$(cmtexe) -quiet show macro_value bin`

#$(cmt_local_tagfile) : $(cmt_lock_setup)
#	@echo "#CMT> Error: $@: No such file" >&2; exit 1
$(cmt_local_tagfile) :
	@echo "#CMT> Warning: $@: No such file" >&2; exit
#	@echo "#CMT> Info: $@: No need to rebuild file" >&2; exit

$(cmt_final_setup) : $(cmt_local_tagfile) 
	$(echo) "(constituents.make) Rebuilding $@"
	@if test ! -d $(@D); then $(mkdir) -p $(@D); fi; \
	  if test -f $(cmt_local_setup); then /bin/rm -f $(cmt_local_setup); fi; \
	  trap '/bin/rm -f $(cmt_local_setup)' 0 1 2 15; \
	  $(cmtexe) -quiet -tag=$(tags) show setup >>$(cmt_local_setup); \
	  if test ! -f $@; then \
	    mv $(cmt_local_setup) $@; \
	  else \
	    if /usr/bin/diff $(cmt_local_setup) $@ >/dev/null ; then \
	      : ; \
	    else \
	      mv $(cmt_local_setup) $@; \
	    fi; \
	  fi

#	@/bin/echo $@ ok   

config :: checkuses
	@exit 0
checkuses : ;

env.make ::
	printenv >env.make.tmp; $(cmtexe) -quiet check files env.make.tmp env.make

ifndef QUICK
all :: build_library_links
	$(echo) "(constituents.make) all done"
endif

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

build_library_links : dirs requirements
	$(echo) "(constituents.make) Rebuilding library links"; \
	if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi; \
	$(build_library_links)

.DEFAULT ::
	@echo "#CMT> Warning: $@: Using default commands" >&2; exit

#	@if test "$@" = "$(cmt_lock_setup)"; then \
	#  /bin/rm -f $(cmt_lock_setup); \
	 # touch $(cmt_lock_setup); \
	#fi

#-- end of constituents_header ------
#-- start of group ------

all_groups :: all

all :: $(all_dependencies)  $(all_pre_constituents) $(all_constituents)  $(all_post_constituents)
	$(echo) "all ok."

#	@/bin/echo " all ok."

clean :: allclean

allclean ::  $(all_constituentsclean)
	$(echo) $(all_constituentsclean)
	$(echo) "allclean ok."

#	@echo $(all_constituentsclean)
#	@/bin/echo " allclean ok."

allclean :: makefilesclean

#-- end of group ------
#-- start of group ------

all_groups :: cmt_actions

cmt_actions :: $(cmt_actions_dependencies)  $(cmt_actions_pre_constituents) $(cmt_actions_constituents)  $(cmt_actions_post_constituents)
	$(echo) "cmt_actions ok."

#	@/bin/echo " cmt_actions ok."

clean :: allclean

cmt_actionsclean ::  $(cmt_actions_constituentsclean)
	$(echo) $(cmt_actions_constituentsclean)
	$(echo) "cmt_actionsclean ok."

#	@echo $(cmt_actions_constituentsclean)
#	@/bin/echo " cmt_actionsclean ok."

cmt_actionsclean :: makefilesclean

#-- end of group ------
#-- start of constituent ------

cmt_ExamTruth_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruth = /tmp/CMT_$(ExamTruth_tag)_ExamTruth.make$(cmt_lock_pid)
cmt_final_setup_ExamTruth = /tmp/CMT_ExamTruth_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = /tmp/CMT_ExamTruth$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth = $(ExamTruth_tag)_ExamTruth.make
cmt_local_tagfile_ExamTruth = $(bin)$(ExamTruth_tag)_ExamTruth.make
cmt_final_setup_ExamTruth = $(bin)ExamTruth_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = $(bin)ExamTruth.make
endif

ExamTruth_extratags = -tag_add=target_ExamTruth

#$(cmt_local_tagfile_ExamTruth) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruth) ::
else
$(cmt_local_tagfile_ExamTruth) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruth)"
	@if test -f $(cmt_local_tagfile_ExamTruth); then /bin/rm -f $(cmt_local_tagfile_ExamTruth); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruth); \
	  if test -f $(cmt_final_setup_ExamTruth); then /bin/rm -f $(cmt_final_setup_ExamTruth); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_extratags) show setup >>$(cmt_final_setup_ExamTruth)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruth = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruth = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_makefile = /tmp/CMT_ExamTruth$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruth = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_makefile = $(bin)ExamTruth.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruth_makefile) :: $(ExamTruth_dependencies) $(cmt_local_tagfile_ExamTruth) build_library_links dirs
else
$(cmt_local_ExamTruth_makefile) :: $(cmt_local_tagfile_ExamTruth)
endif
	$(echo) "(constituents.make) Building ExamTruth.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_extratags) build constituent_makefile -out=$(cmt_local_ExamTruth_makefile) ExamTruth

ExamTruth :: $(ExamTruth_dependencies) $(cmt_local_ExamTruth_makefile)
	$(echo) "(constituents.make) Starting ExamTruth"
	@$(MAKE) -f $(cmt_local_ExamTruth_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruth
	$(echo) "(constituents.make) ExamTruth done"

clean :: ExamTruthclean

ExamTruthclean :: $(ExamTruthclean_dependencies) ##$(cmt_local_ExamTruth_makefile)
	$(echo) "(constituents.make) Starting ExamTruthclean"
	@-if test -f $(cmt_local_ExamTruth_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruth_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruth_makefile) $(bin)ExamTruth_dependencies.make

install :: ExamTruthinstall

ExamTruthinstall :: $(ExamTruth_dependencies) $(cmt_local_ExamTruth_makefile)
	$(echo) "(constituents.make) Starting install ExamTruth"
	@-$(MAKE) -f $(cmt_local_ExamTruth_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruth done"

uninstall :: ExamTruthuninstall

ExamTruthuninstall :: $(cmt_local_ExamTruth_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruth"
	@-$(MAKE) -f $(cmt_local_ExamTruth_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruth done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruth"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruth done"
endif


#-- end of constituent ------
#-- start of constituent_lock ------

cmt_ExamTruthRootMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthRootMap_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthRootMap = /tmp/CMT_$(ExamTruth_tag)_ExamTruthRootMap.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthRootMap = /tmp/CMT_ExamTruth_ExamTruthRootMapsetup.make
cmt_local_ExamTruthRootMap_makefile = /tmp/CMT_ExamTruthRootMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthRootMap = $(ExamTruth_tag)_ExamTruthRootMap.make
cmt_local_tagfile_ExamTruthRootMap = $(bin)$(ExamTruth_tag)_ExamTruthRootMap.make
cmt_final_setup_ExamTruthRootMap = $(bin)ExamTruth_ExamTruthRootMapsetup.make
cmt_local_ExamTruthRootMap_makefile = $(bin)ExamTruthRootMap.make
endif

ExamTruthRootMap_extratags = -tag_add=target_ExamTruthRootMap

#$(cmt_local_tagfile_ExamTruthRootMap) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthRootMap) ::
else
$(cmt_local_tagfile_ExamTruthRootMap) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthRootMap)"
	@if test -f $(cmt_local_tagfile_ExamTruthRootMap); then /bin/rm -f $(cmt_local_tagfile_ExamTruthRootMap); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthRootMap_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthRootMap); \
	  if test -f $(cmt_final_setup_ExamTruthRootMap); then /bin/rm -f $(cmt_final_setup_ExamTruthRootMap); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthRootMap_extratags) show setup >>$(cmt_final_setup_ExamTruthRootMap)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthRootMap = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthRootMap = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthRootMap_makefile = /tmp/CMT_ExamTruthRootMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthRootMap = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthRootMap = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthRootMap = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthRootMap_makefile = $(bin)ExamTruthRootMap.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthRootMap_makefile) :: $(ExamTruthRootMap_dependencies) $(cmt_local_tagfile_ExamTruthRootMap) build_library_links dirs
else
$(cmt_local_ExamTruthRootMap_makefile) :: $(cmt_local_tagfile_ExamTruthRootMap)
endif
	$(echo) "(constituents.make) Building ExamTruthRootMap.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthRootMap_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthRootMap_makefile) ExamTruthRootMap

ExamTruthRootMap :: $(ExamTruthRootMap_dependencies) $(cmt_local_ExamTruthRootMap_makefile)
	$(echo) "(constituents.make) Creating ExamTruthRootMap${lock_suffix} and Starting ExamTruthRootMap"
	@{ ${lock_command} ExamTruthRootMap${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthRootMap${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthRootMap; \
	  retval=$$?; ${unlock_command} ExamTruthRootMap${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthRootMap done"

clean :: ExamTruthRootMapclean

ExamTruthRootMapclean :: $(ExamTruthRootMapclean_dependencies) ##$(cmt_local_ExamTruthRootMap_makefile)
	$(echo) "(constituents.make) Starting ExamTruthRootMapclean"
	@-if test -f $(cmt_local_ExamTruthRootMap_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthRootMapclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthRootMap_makefile) $(bin)ExamTruthRootMap_dependencies.make

install :: ExamTruthRootMapinstall

ExamTruthRootMapinstall :: $(ExamTruthRootMap_dependencies) $(cmt_local_ExamTruthRootMap_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthRootMap"
	@-$(MAKE) -f $(cmt_local_ExamTruthRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthRootMap done"

uninstall :: ExamTruthRootMapuninstall

ExamTruthRootMapuninstall :: $(cmt_local_ExamTruthRootMap_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthRootMap"
	@-$(MAKE) -f $(cmt_local_ExamTruthRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthRootMap done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthRootMap"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthRootMap done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruthMergeMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthMergeMap_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthMergeMap = /tmp/CMT_$(ExamTruth_tag)_ExamTruthMergeMap.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthMergeMap = /tmp/CMT_ExamTruth_ExamTruthMergeMapsetup.make
cmt_local_ExamTruthMergeMap_makefile = /tmp/CMT_ExamTruthMergeMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthMergeMap = $(ExamTruth_tag)_ExamTruthMergeMap.make
cmt_local_tagfile_ExamTruthMergeMap = $(bin)$(ExamTruth_tag)_ExamTruthMergeMap.make
cmt_final_setup_ExamTruthMergeMap = $(bin)ExamTruth_ExamTruthMergeMapsetup.make
cmt_local_ExamTruthMergeMap_makefile = $(bin)ExamTruthMergeMap.make
endif

ExamTruthMergeMap_extratags = -tag_add=target_ExamTruthMergeMap

#$(cmt_local_tagfile_ExamTruthMergeMap) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthMergeMap) ::
else
$(cmt_local_tagfile_ExamTruthMergeMap) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthMergeMap)"
	@if test -f $(cmt_local_tagfile_ExamTruthMergeMap); then /bin/rm -f $(cmt_local_tagfile_ExamTruthMergeMap); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthMergeMap_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthMergeMap); \
	  if test -f $(cmt_final_setup_ExamTruthMergeMap); then /bin/rm -f $(cmt_final_setup_ExamTruthMergeMap); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthMergeMap_extratags) show setup >>$(cmt_final_setup_ExamTruthMergeMap)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthMergeMap = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthMergeMap = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthMergeMap_makefile = /tmp/CMT_ExamTruthMergeMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthMergeMap = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthMergeMap = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthMergeMap = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthMergeMap_makefile = $(bin)ExamTruthMergeMap.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthMergeMap_makefile) :: $(ExamTruthMergeMap_dependencies) $(cmt_local_tagfile_ExamTruthMergeMap) build_library_links dirs
else
$(cmt_local_ExamTruthMergeMap_makefile) :: $(cmt_local_tagfile_ExamTruthMergeMap)
endif
	$(echo) "(constituents.make) Building ExamTruthMergeMap.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthMergeMap_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthMergeMap_makefile) ExamTruthMergeMap

ExamTruthMergeMap :: $(ExamTruthMergeMap_dependencies) $(cmt_local_ExamTruthMergeMap_makefile)
	$(echo) "(constituents.make) Creating ExamTruthMergeMap${lock_suffix} and Starting ExamTruthMergeMap"
	@{ ${lock_command} ExamTruthMergeMap${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthMergeMap${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthMergeMap; \
	  retval=$$?; ${unlock_command} ExamTruthMergeMap${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthMergeMap done"

clean :: ExamTruthMergeMapclean

ExamTruthMergeMapclean :: $(ExamTruthMergeMapclean_dependencies) ##$(cmt_local_ExamTruthMergeMap_makefile)
	$(echo) "(constituents.make) Starting ExamTruthMergeMapclean"
	@-if test -f $(cmt_local_ExamTruthMergeMap_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthMergeMapclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthMergeMap_makefile) $(bin)ExamTruthMergeMap_dependencies.make

install :: ExamTruthMergeMapinstall

ExamTruthMergeMapinstall :: $(ExamTruthMergeMap_dependencies) $(cmt_local_ExamTruthMergeMap_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthMergeMap"
	@-$(MAKE) -f $(cmt_local_ExamTruthMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthMergeMap done"

uninstall :: ExamTruthMergeMapuninstall

ExamTruthMergeMapuninstall :: $(cmt_local_ExamTruthMergeMap_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthMergeMap"
	@-$(MAKE) -f $(cmt_local_ExamTruthMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthMergeMap done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthMergeMap"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthMergeMap done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruthConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthConf_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthConf = /tmp/CMT_$(ExamTruth_tag)_ExamTruthConf.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConf = /tmp/CMT_ExamTruth_ExamTruthConfsetup.make
cmt_local_ExamTruthConf_makefile = /tmp/CMT_ExamTruthConf$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConf = $(ExamTruth_tag)_ExamTruthConf.make
cmt_local_tagfile_ExamTruthConf = $(bin)$(ExamTruth_tag)_ExamTruthConf.make
cmt_final_setup_ExamTruthConf = $(bin)ExamTruth_ExamTruthConfsetup.make
cmt_local_ExamTruthConf_makefile = $(bin)ExamTruthConf.make
endif

ExamTruthConf_extratags = -tag_add=target_ExamTruthConf

#$(cmt_local_tagfile_ExamTruthConf) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthConf) ::
else
$(cmt_local_tagfile_ExamTruthConf) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthConf)"
	@if test -f $(cmt_local_tagfile_ExamTruthConf); then /bin/rm -f $(cmt_local_tagfile_ExamTruthConf); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConf_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthConf); \
	  if test -f $(cmt_final_setup_ExamTruthConf); then /bin/rm -f $(cmt_final_setup_ExamTruthConf); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConf_extratags) show setup >>$(cmt_final_setup_ExamTruthConf)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthConf = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConf = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthConf_makefile = /tmp/CMT_ExamTruthConf$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConf = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthConf = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthConf = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthConf_makefile = $(bin)ExamTruthConf.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthConf_makefile) :: $(ExamTruthConf_dependencies) $(cmt_local_tagfile_ExamTruthConf) build_library_links dirs
else
$(cmt_local_ExamTruthConf_makefile) :: $(cmt_local_tagfile_ExamTruthConf)
endif
	$(echo) "(constituents.make) Building ExamTruthConf.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConf_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthConf_makefile) ExamTruthConf

ExamTruthConf :: $(ExamTruthConf_dependencies) $(cmt_local_ExamTruthConf_makefile)
	$(echo) "(constituents.make) Creating ExamTruthConf${lock_suffix} and Starting ExamTruthConf"
	@{ ${lock_command} ExamTruthConf${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthConf${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthConf_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConf; \
	  retval=$$?; ${unlock_command} ExamTruthConf${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthConf done"

clean :: ExamTruthConfclean

ExamTruthConfclean :: $(ExamTruthConfclean_dependencies) ##$(cmt_local_ExamTruthConf_makefile)
	$(echo) "(constituents.make) Starting ExamTruthConfclean"
	@-if test -f $(cmt_local_ExamTruthConf_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthConf_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConfclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthConf_makefile) $(bin)ExamTruthConf_dependencies.make

install :: ExamTruthConfinstall

ExamTruthConfinstall :: $(ExamTruthConf_dependencies) $(cmt_local_ExamTruthConf_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthConf"
	@-$(MAKE) -f $(cmt_local_ExamTruthConf_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthConf done"

uninstall :: ExamTruthConfuninstall

ExamTruthConfuninstall :: $(cmt_local_ExamTruthConf_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthConf"
	@-$(MAKE) -f $(cmt_local_ExamTruthConf_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthConf done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthConf"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthConf done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruth_python_init_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_python_init_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruth_python_init = /tmp/CMT_$(ExamTruth_tag)_ExamTruth_python_init.make$(cmt_lock_pid)
cmt_final_setup_ExamTruth_python_init = /tmp/CMT_ExamTruth_ExamTruth_python_initsetup.make
cmt_local_ExamTruth_python_init_makefile = /tmp/CMT_ExamTruth_python_init$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth_python_init = $(ExamTruth_tag)_ExamTruth_python_init.make
cmt_local_tagfile_ExamTruth_python_init = $(bin)$(ExamTruth_tag)_ExamTruth_python_init.make
cmt_final_setup_ExamTruth_python_init = $(bin)ExamTruth_ExamTruth_python_initsetup.make
cmt_local_ExamTruth_python_init_makefile = $(bin)ExamTruth_python_init.make
endif

ExamTruth_python_init_extratags = -tag_add=target_ExamTruth_python_init

#$(cmt_local_tagfile_ExamTruth_python_init) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruth_python_init) ::
else
$(cmt_local_tagfile_ExamTruth_python_init) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruth_python_init)"
	@if test -f $(cmt_local_tagfile_ExamTruth_python_init); then /bin/rm -f $(cmt_local_tagfile_ExamTruth_python_init); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_init_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruth_python_init); \
	  if test -f $(cmt_final_setup_ExamTruth_python_init); then /bin/rm -f $(cmt_final_setup_ExamTruth_python_init); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_init_extratags) show setup >>$(cmt_final_setup_ExamTruth_python_init)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruth_python_init = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruth_python_init = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_python_init_makefile = /tmp/CMT_ExamTruth_python_init$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth_python_init = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth_python_init = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruth_python_init = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_python_init_makefile = $(bin)ExamTruth_python_init.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruth_python_init_makefile) :: $(ExamTruth_python_init_dependencies) $(cmt_local_tagfile_ExamTruth_python_init) build_library_links dirs
else
$(cmt_local_ExamTruth_python_init_makefile) :: $(cmt_local_tagfile_ExamTruth_python_init)
endif
	$(echo) "(constituents.make) Building ExamTruth_python_init.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_init_extratags) build constituent_makefile -out=$(cmt_local_ExamTruth_python_init_makefile) ExamTruth_python_init

ExamTruth_python_init :: $(ExamTruth_python_init_dependencies) $(cmt_local_ExamTruth_python_init_makefile)
	$(echo) "(constituents.make) Creating ExamTruth_python_init${lock_suffix} and Starting ExamTruth_python_init"
	@{ ${lock_command} ExamTruth_python_init${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruth_python_init${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruth_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruth_python_init; \
	  retval=$$?; ${unlock_command} ExamTruth_python_init${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruth_python_init done"

clean :: ExamTruth_python_initclean

ExamTruth_python_initclean :: $(ExamTruth_python_initclean_dependencies) ##$(cmt_local_ExamTruth_python_init_makefile)
	$(echo) "(constituents.make) Starting ExamTruth_python_initclean"
	@-if test -f $(cmt_local_ExamTruth_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruth_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruth_python_initclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruth_python_init_makefile) $(bin)ExamTruth_python_init_dependencies.make

install :: ExamTruth_python_initinstall

ExamTruth_python_initinstall :: $(ExamTruth_python_init_dependencies) $(cmt_local_ExamTruth_python_init_makefile)
	$(echo) "(constituents.make) Starting install ExamTruth_python_init"
	@-$(MAKE) -f $(cmt_local_ExamTruth_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruth_python_init done"

uninstall :: ExamTruth_python_inituninstall

ExamTruth_python_inituninstall :: $(cmt_local_ExamTruth_python_init_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruth_python_init"
	@-$(MAKE) -f $(cmt_local_ExamTruth_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruth_python_init done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruth_python_init"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruth_python_init done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruthConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthConfDbMerge_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthConfDbMerge = /tmp/CMT_$(ExamTruth_tag)_ExamTruthConfDbMerge.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConfDbMerge = /tmp/CMT_ExamTruth_ExamTruthConfDbMergesetup.make
cmt_local_ExamTruthConfDbMerge_makefile = /tmp/CMT_ExamTruthConfDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConfDbMerge = $(ExamTruth_tag)_ExamTruthConfDbMerge.make
cmt_local_tagfile_ExamTruthConfDbMerge = $(bin)$(ExamTruth_tag)_ExamTruthConfDbMerge.make
cmt_final_setup_ExamTruthConfDbMerge = $(bin)ExamTruth_ExamTruthConfDbMergesetup.make
cmt_local_ExamTruthConfDbMerge_makefile = $(bin)ExamTruthConfDbMerge.make
endif

ExamTruthConfDbMerge_extratags = -tag_add=target_ExamTruthConfDbMerge

#$(cmt_local_tagfile_ExamTruthConfDbMerge) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthConfDbMerge) ::
else
$(cmt_local_tagfile_ExamTruthConfDbMerge) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthConfDbMerge)"
	@if test -f $(cmt_local_tagfile_ExamTruthConfDbMerge); then /bin/rm -f $(cmt_local_tagfile_ExamTruthConfDbMerge); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfDbMerge_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthConfDbMerge); \
	  if test -f $(cmt_final_setup_ExamTruthConfDbMerge); then /bin/rm -f $(cmt_final_setup_ExamTruthConfDbMerge); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfDbMerge_extratags) show setup >>$(cmt_final_setup_ExamTruthConfDbMerge)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthConfDbMerge = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConfDbMerge = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthConfDbMerge_makefile = /tmp/CMT_ExamTruthConfDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConfDbMerge = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthConfDbMerge = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthConfDbMerge = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthConfDbMerge_makefile = $(bin)ExamTruthConfDbMerge.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthConfDbMerge_makefile) :: $(ExamTruthConfDbMerge_dependencies) $(cmt_local_tagfile_ExamTruthConfDbMerge) build_library_links dirs
else
$(cmt_local_ExamTruthConfDbMerge_makefile) :: $(cmt_local_tagfile_ExamTruthConfDbMerge)
endif
	$(echo) "(constituents.make) Building ExamTruthConfDbMerge.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfDbMerge_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthConfDbMerge_makefile) ExamTruthConfDbMerge

ExamTruthConfDbMerge :: $(ExamTruthConfDbMerge_dependencies) $(cmt_local_ExamTruthConfDbMerge_makefile)
	$(echo) "(constituents.make) Creating ExamTruthConfDbMerge${lock_suffix} and Starting ExamTruthConfDbMerge"
	@{ ${lock_command} ExamTruthConfDbMerge${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthConfDbMerge${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConfDbMerge; \
	  retval=$$?; ${unlock_command} ExamTruthConfDbMerge${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthConfDbMerge done"

clean :: ExamTruthConfDbMergeclean

ExamTruthConfDbMergeclean :: $(ExamTruthConfDbMergeclean_dependencies) ##$(cmt_local_ExamTruthConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting ExamTruthConfDbMergeclean"
	@-if test -f $(cmt_local_ExamTruthConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConfDbMergeclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthConfDbMerge_makefile) $(bin)ExamTruthConfDbMerge_dependencies.make

install :: ExamTruthConfDbMergeinstall

ExamTruthConfDbMergeinstall :: $(ExamTruthConfDbMerge_dependencies) $(cmt_local_ExamTruthConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthConfDbMerge"
	@-$(MAKE) -f $(cmt_local_ExamTruthConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthConfDbMerge done"

uninstall :: ExamTruthConfDbMergeuninstall

ExamTruthConfDbMergeuninstall :: $(cmt_local_ExamTruthConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthConfDbMerge"
	@-$(MAKE) -f $(cmt_local_ExamTruthConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthConfDbMerge done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthConfDbMerge"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthConfDbMerge done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_install_scripts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_install_scripts_has_target_tag

ifdef READONLY
cmt_local_tagfile_install_scripts = /tmp/CMT_$(ExamTruth_tag)_install_scripts.make$(cmt_lock_pid)
cmt_final_setup_install_scripts = /tmp/CMT_ExamTruth_install_scriptssetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
#cmt_local_tagfile_install_scripts = $(ExamTruth_tag)_install_scripts.make
cmt_local_tagfile_install_scripts = $(bin)$(ExamTruth_tag)_install_scripts.make
cmt_final_setup_install_scripts = $(bin)ExamTruth_install_scriptssetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make
endif

install_scripts_extratags = -tag_add=target_install_scripts

#$(cmt_local_tagfile_install_scripts) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_install_scripts) ::
else
$(cmt_local_tagfile_install_scripts) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_install_scripts)"
	@if test -f $(cmt_local_tagfile_install_scripts); then /bin/rm -f $(cmt_local_tagfile_install_scripts); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(install_scripts_extratags) build tag_makefile >>$(cmt_local_tagfile_install_scripts); \
	  if test -f $(cmt_final_setup_install_scripts); then /bin/rm -f $(cmt_final_setup_install_scripts); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(install_scripts_extratags) show setup >>$(cmt_final_setup_install_scripts)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_install_scripts = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_install_scripts = /tmp/CMT_ExamTruthsetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
#cmt_local_tagfile_install_scripts = $(ExamTruth_tag).make
cmt_local_tagfile_install_scripts = $(bin)$(ExamTruth_tag).make
cmt_final_setup_install_scripts = $(bin)ExamTruthsetup.make
cmt_local_install_scripts_makefile = $(bin)install_scripts.make
endif

endif

ifndef QUICK
$(cmt_local_install_scripts_makefile) :: $(install_scripts_dependencies) $(cmt_local_tagfile_install_scripts) build_library_links dirs
else
$(cmt_local_install_scripts_makefile) :: $(cmt_local_tagfile_install_scripts)
endif
	$(echo) "(constituents.make) Building install_scripts.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(install_scripts_extratags) build constituent_makefile -out=$(cmt_local_install_scripts_makefile) install_scripts

install_scripts :: $(install_scripts_dependencies) $(cmt_local_install_scripts_makefile)
	$(echo) "(constituents.make) Creating install_scripts${lock_suffix} and Starting install_scripts"
	@{ ${lock_command} install_scripts${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} install_scripts${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_install_scripts_makefile) cmt_lock_pid=$${cmt_lock_pid} install_scripts; \
	  retval=$$?; ${unlock_command} install_scripts${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) install_scripts done"

clean :: install_scriptsclean

install_scriptsclean :: $(install_scriptsclean_dependencies) ##$(cmt_local_install_scripts_makefile)
	$(echo) "(constituents.make) Starting install_scriptsclean"
	@-if test -f $(cmt_local_install_scripts_makefile); then \
	  $(MAKE) -f $(cmt_local_install_scripts_makefile) cmt_lock_pid=$${cmt_lock_pid} install_scriptsclean; \
	fi

##	  /bin/rm -f $(cmt_local_install_scripts_makefile) $(bin)install_scripts_dependencies.make

install :: install_scriptsinstall

install_scriptsinstall :: $(install_scripts_dependencies) $(cmt_local_install_scripts_makefile)
	$(echo) "(constituents.make) Starting install install_scripts"
	@-$(MAKE) -f $(cmt_local_install_scripts_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install install_scripts done"

uninstall :: install_scriptsuninstall

install_scriptsuninstall :: $(cmt_local_install_scripts_makefile)
	$(echo) "(constituents.make) Starting uninstall install_scripts"
	@-$(MAKE) -f $(cmt_local_install_scripts_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall install_scripts done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ install_scripts"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ install_scripts done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruth_python_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruth_python_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruth_python = /tmp/CMT_$(ExamTruth_tag)_ExamTruth_python.make$(cmt_lock_pid)
cmt_final_setup_ExamTruth_python = /tmp/CMT_ExamTruth_ExamTruth_pythonsetup.make
cmt_local_ExamTruth_python_makefile = /tmp/CMT_ExamTruth_python$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth_python = $(ExamTruth_tag)_ExamTruth_python.make
cmt_local_tagfile_ExamTruth_python = $(bin)$(ExamTruth_tag)_ExamTruth_python.make
cmt_final_setup_ExamTruth_python = $(bin)ExamTruth_ExamTruth_pythonsetup.make
cmt_local_ExamTruth_python_makefile = $(bin)ExamTruth_python.make
endif

ExamTruth_python_extratags = -tag_add=target_ExamTruth_python

#$(cmt_local_tagfile_ExamTruth_python) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruth_python) ::
else
$(cmt_local_tagfile_ExamTruth_python) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruth_python)"
	@if test -f $(cmt_local_tagfile_ExamTruth_python); then /bin/rm -f $(cmt_local_tagfile_ExamTruth_python); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruth_python); \
	  if test -f $(cmt_final_setup_ExamTruth_python); then /bin/rm -f $(cmt_final_setup_ExamTruth_python); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_extratags) show setup >>$(cmt_final_setup_ExamTruth_python)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruth_python = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruth_python = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruth_python_makefile = /tmp/CMT_ExamTruth_python$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruth_python = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruth_python = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruth_python = $(bin)ExamTruthsetup.make
cmt_local_ExamTruth_python_makefile = $(bin)ExamTruth_python.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruth_python_makefile) :: $(ExamTruth_python_dependencies) $(cmt_local_tagfile_ExamTruth_python) build_library_links dirs
else
$(cmt_local_ExamTruth_python_makefile) :: $(cmt_local_tagfile_ExamTruth_python)
endif
	$(echo) "(constituents.make) Building ExamTruth_python.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruth_python_extratags) build constituent_makefile -out=$(cmt_local_ExamTruth_python_makefile) ExamTruth_python

ExamTruth_python :: $(ExamTruth_python_dependencies) $(cmt_local_ExamTruth_python_makefile)
	$(echo) "(constituents.make) Creating ExamTruth_python${lock_suffix} and Starting ExamTruth_python"
	@{ ${lock_command} ExamTruth_python${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruth_python${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruth_python_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruth_python; \
	  retval=$$?; ${unlock_command} ExamTruth_python${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruth_python done"

clean :: ExamTruth_pythonclean

ExamTruth_pythonclean :: $(ExamTruth_pythonclean_dependencies) ##$(cmt_local_ExamTruth_python_makefile)
	$(echo) "(constituents.make) Starting ExamTruth_pythonclean"
	@-if test -f $(cmt_local_ExamTruth_python_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruth_python_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruth_pythonclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruth_python_makefile) $(bin)ExamTruth_python_dependencies.make

install :: ExamTruth_pythoninstall

ExamTruth_pythoninstall :: $(ExamTruth_python_dependencies) $(cmt_local_ExamTruth_python_makefile)
	$(echo) "(constituents.make) Starting install ExamTruth_python"
	@-$(MAKE) -f $(cmt_local_ExamTruth_python_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruth_python done"

uninstall :: ExamTruth_pythonuninstall

ExamTruth_pythonuninstall :: $(cmt_local_ExamTruth_python_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruth_python"
	@-$(MAKE) -f $(cmt_local_ExamTruth_python_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruth_python done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruth_python"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruth_python done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruthGenConfUser_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthGenConfUser_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthGenConfUser = /tmp/CMT_$(ExamTruth_tag)_ExamTruthGenConfUser.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthGenConfUser = /tmp/CMT_ExamTruth_ExamTruthGenConfUsersetup.make
cmt_local_ExamTruthGenConfUser_makefile = /tmp/CMT_ExamTruthGenConfUser$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthGenConfUser = $(ExamTruth_tag)_ExamTruthGenConfUser.make
cmt_local_tagfile_ExamTruthGenConfUser = $(bin)$(ExamTruth_tag)_ExamTruthGenConfUser.make
cmt_final_setup_ExamTruthGenConfUser = $(bin)ExamTruth_ExamTruthGenConfUsersetup.make
cmt_local_ExamTruthGenConfUser_makefile = $(bin)ExamTruthGenConfUser.make
endif

ExamTruthGenConfUser_extratags = -tag_add=target_ExamTruthGenConfUser

#$(cmt_local_tagfile_ExamTruthGenConfUser) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthGenConfUser) ::
else
$(cmt_local_tagfile_ExamTruthGenConfUser) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthGenConfUser)"
	@if test -f $(cmt_local_tagfile_ExamTruthGenConfUser); then /bin/rm -f $(cmt_local_tagfile_ExamTruthGenConfUser); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthGenConfUser_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthGenConfUser); \
	  if test -f $(cmt_final_setup_ExamTruthGenConfUser); then /bin/rm -f $(cmt_final_setup_ExamTruthGenConfUser); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthGenConfUser_extratags) show setup >>$(cmt_final_setup_ExamTruthGenConfUser)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthGenConfUser = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthGenConfUser = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthGenConfUser_makefile = /tmp/CMT_ExamTruthGenConfUser$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthGenConfUser = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthGenConfUser = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthGenConfUser = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthGenConfUser_makefile = $(bin)ExamTruthGenConfUser.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthGenConfUser_makefile) :: $(ExamTruthGenConfUser_dependencies) $(cmt_local_tagfile_ExamTruthGenConfUser) build_library_links dirs
else
$(cmt_local_ExamTruthGenConfUser_makefile) :: $(cmt_local_tagfile_ExamTruthGenConfUser)
endif
	$(echo) "(constituents.make) Building ExamTruthGenConfUser.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthGenConfUser_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthGenConfUser_makefile) ExamTruthGenConfUser

ExamTruthGenConfUser :: $(ExamTruthGenConfUser_dependencies) $(cmt_local_ExamTruthGenConfUser_makefile)
	$(echo) "(constituents.make) Creating ExamTruthGenConfUser${lock_suffix} and Starting ExamTruthGenConfUser"
	@{ ${lock_command} ExamTruthGenConfUser${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthGenConfUser${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthGenConfUser; \
	  retval=$$?; ${unlock_command} ExamTruthGenConfUser${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthGenConfUser done"

clean :: ExamTruthGenConfUserclean

ExamTruthGenConfUserclean :: $(ExamTruthGenConfUserclean_dependencies) ##$(cmt_local_ExamTruthGenConfUser_makefile)
	$(echo) "(constituents.make) Starting ExamTruthGenConfUserclean"
	@-if test -f $(cmt_local_ExamTruthGenConfUser_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthGenConfUserclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthGenConfUser_makefile) $(bin)ExamTruthGenConfUser_dependencies.make

install :: ExamTruthGenConfUserinstall

ExamTruthGenConfUserinstall :: $(ExamTruthGenConfUser_dependencies) $(cmt_local_ExamTruthGenConfUser_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthGenConfUser"
	@-$(MAKE) -f $(cmt_local_ExamTruthGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthGenConfUser done"

uninstall :: ExamTruthGenConfUseruninstall

ExamTruthGenConfUseruninstall :: $(cmt_local_ExamTruthGenConfUser_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthGenConfUser"
	@-$(MAKE) -f $(cmt_local_ExamTruthGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthGenConfUser done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthGenConfUser"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthGenConfUser done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_ExamTruthConfUserDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ExamTruthConfUserDbMerge_has_target_tag

ifdef READONLY
cmt_local_tagfile_ExamTruthConfUserDbMerge = /tmp/CMT_$(ExamTruth_tag)_ExamTruthConfUserDbMerge.make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConfUserDbMerge = /tmp/CMT_ExamTruth_ExamTruthConfUserDbMergesetup.make
cmt_local_ExamTruthConfUserDbMerge_makefile = /tmp/CMT_ExamTruthConfUserDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConfUserDbMerge = $(ExamTruth_tag)_ExamTruthConfUserDbMerge.make
cmt_local_tagfile_ExamTruthConfUserDbMerge = $(bin)$(ExamTruth_tag)_ExamTruthConfUserDbMerge.make
cmt_final_setup_ExamTruthConfUserDbMerge = $(bin)ExamTruth_ExamTruthConfUserDbMergesetup.make
cmt_local_ExamTruthConfUserDbMerge_makefile = $(bin)ExamTruthConfUserDbMerge.make
endif

ExamTruthConfUserDbMerge_extratags = -tag_add=target_ExamTruthConfUserDbMerge

#$(cmt_local_tagfile_ExamTruthConfUserDbMerge) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_ExamTruthConfUserDbMerge) ::
else
$(cmt_local_tagfile_ExamTruthConfUserDbMerge) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_ExamTruthConfUserDbMerge)"
	@if test -f $(cmt_local_tagfile_ExamTruthConfUserDbMerge); then /bin/rm -f $(cmt_local_tagfile_ExamTruthConfUserDbMerge); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfUserDbMerge_extratags) build tag_makefile >>$(cmt_local_tagfile_ExamTruthConfUserDbMerge); \
	  if test -f $(cmt_final_setup_ExamTruthConfUserDbMerge); then /bin/rm -f $(cmt_final_setup_ExamTruthConfUserDbMerge); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfUserDbMerge_extratags) show setup >>$(cmt_final_setup_ExamTruthConfUserDbMerge)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_ExamTruthConfUserDbMerge = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_ExamTruthConfUserDbMerge = /tmp/CMT_ExamTruthsetup.make
cmt_local_ExamTruthConfUserDbMerge_makefile = /tmp/CMT_ExamTruthConfUserDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_ExamTruthConfUserDbMerge = $(ExamTruth_tag).make
cmt_local_tagfile_ExamTruthConfUserDbMerge = $(bin)$(ExamTruth_tag).make
cmt_final_setup_ExamTruthConfUserDbMerge = $(bin)ExamTruthsetup.make
cmt_local_ExamTruthConfUserDbMerge_makefile = $(bin)ExamTruthConfUserDbMerge.make
endif

endif

ifndef QUICK
$(cmt_local_ExamTruthConfUserDbMerge_makefile) :: $(ExamTruthConfUserDbMerge_dependencies) $(cmt_local_tagfile_ExamTruthConfUserDbMerge) build_library_links dirs
else
$(cmt_local_ExamTruthConfUserDbMerge_makefile) :: $(cmt_local_tagfile_ExamTruthConfUserDbMerge)
endif
	$(echo) "(constituents.make) Building ExamTruthConfUserDbMerge.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(ExamTruthConfUserDbMerge_extratags) build constituent_makefile -out=$(cmt_local_ExamTruthConfUserDbMerge_makefile) ExamTruthConfUserDbMerge

ExamTruthConfUserDbMerge :: $(ExamTruthConfUserDbMerge_dependencies) $(cmt_local_ExamTruthConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Creating ExamTruthConfUserDbMerge${lock_suffix} and Starting ExamTruthConfUserDbMerge"
	@{ ${lock_command} ExamTruthConfUserDbMerge${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} ExamTruthConfUserDbMerge${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_ExamTruthConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConfUserDbMerge; \
	  retval=$$?; ${unlock_command} ExamTruthConfUserDbMerge${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) ExamTruthConfUserDbMerge done"

clean :: ExamTruthConfUserDbMergeclean

ExamTruthConfUserDbMergeclean :: $(ExamTruthConfUserDbMergeclean_dependencies) ##$(cmt_local_ExamTruthConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting ExamTruthConfUserDbMergeclean"
	@-if test -f $(cmt_local_ExamTruthConfUserDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_ExamTruthConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} ExamTruthConfUserDbMergeclean; \
	fi

##	  /bin/rm -f $(cmt_local_ExamTruthConfUserDbMerge_makefile) $(bin)ExamTruthConfUserDbMerge_dependencies.make

install :: ExamTruthConfUserDbMergeinstall

ExamTruthConfUserDbMergeinstall :: $(ExamTruthConfUserDbMerge_dependencies) $(cmt_local_ExamTruthConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting install ExamTruthConfUserDbMerge"
	@-$(MAKE) -f $(cmt_local_ExamTruthConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install ExamTruthConfUserDbMerge done"

uninstall :: ExamTruthConfUserDbMergeuninstall

ExamTruthConfUserDbMergeuninstall :: $(cmt_local_ExamTruthConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting uninstall ExamTruthConfUserDbMerge"
	@-$(MAKE) -f $(cmt_local_ExamTruthConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall ExamTruthConfUserDbMerge done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ ExamTruthConfUserDbMerge"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ ExamTruthConfUserDbMerge done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_make_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_make_has_target_tag

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(ExamTruth_tag)_make.make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_ExamTruth_makesetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(ExamTruth_tag)_make.make
cmt_local_tagfile_make = $(bin)$(ExamTruth_tag)_make.make
cmt_final_setup_make = $(bin)ExamTruth_makesetup.make
cmt_local_make_makefile = $(bin)make.make
endif

make_extratags = -tag_add=target_make

#$(cmt_local_tagfile_make) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_make) ::
else
$(cmt_local_tagfile_make) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_make)"
	@if test -f $(cmt_local_tagfile_make); then /bin/rm -f $(cmt_local_tagfile_make); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(make_extratags) build tag_makefile >>$(cmt_local_tagfile_make); \
	  if test -f $(cmt_final_setup_make); then /bin/rm -f $(cmt_final_setup_make); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(make_extratags) show setup >>$(cmt_final_setup_make)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_ExamTruthsetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(ExamTruth_tag).make
cmt_local_tagfile_make = $(bin)$(ExamTruth_tag).make
cmt_final_setup_make = $(bin)ExamTruthsetup.make
cmt_local_make_makefile = $(bin)make.make
endif

endif

ifndef QUICK
$(cmt_local_make_makefile) :: $(make_dependencies) $(cmt_local_tagfile_make) build_library_links dirs
else
$(cmt_local_make_makefile) :: $(cmt_local_tagfile_make)
endif
	$(echo) "(constituents.make) Building make.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(make_extratags) build constituent_makefile -out=$(cmt_local_make_makefile) make

make :: $(make_dependencies) $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Creating make${lock_suffix} and Starting make"
	@{ ${lock_command} make${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} make${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} make; \
	  retval=$$?; ${unlock_command} make${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) make done"

clean :: makeclean

makeclean :: $(makeclean_dependencies) ##$(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting makeclean"
	@-if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} makeclean; \
	fi

##	  /bin/rm -f $(cmt_local_make_makefile) $(bin)make_dependencies.make

install :: makeinstall

makeinstall :: $(make_dependencies) $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting install make"
	@-$(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install make done"

uninstall :: makeuninstall

makeuninstall :: $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting uninstall make"
	@-$(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall make done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ make"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ make done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_doxygen_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_doxygen_has_target_tag

ifdef READONLY
cmt_local_tagfile_doxygen = /tmp/CMT_$(ExamTruth_tag)_doxygen.make$(cmt_lock_pid)
cmt_final_setup_doxygen = /tmp/CMT_ExamTruth_doxygensetup.make
cmt_local_doxygen_makefile = /tmp/CMT_doxygen$(cmt_lock_pid).make
else
#cmt_local_tagfile_doxygen = $(ExamTruth_tag)_doxygen.make
cmt_local_tagfile_doxygen = $(bin)$(ExamTruth_tag)_doxygen.make
cmt_final_setup_doxygen = $(bin)ExamTruth_doxygensetup.make
cmt_local_doxygen_makefile = $(bin)doxygen.make
endif

doxygen_extratags = -tag_add=target_doxygen

#$(cmt_local_tagfile_doxygen) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_doxygen) ::
else
$(cmt_local_tagfile_doxygen) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_doxygen)"
	@if test -f $(cmt_local_tagfile_doxygen); then /bin/rm -f $(cmt_local_tagfile_doxygen); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(doxygen_extratags) build tag_makefile >>$(cmt_local_tagfile_doxygen); \
	  if test -f $(cmt_final_setup_doxygen); then /bin/rm -f $(cmt_final_setup_doxygen); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(doxygen_extratags) show setup >>$(cmt_final_setup_doxygen)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_doxygen = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_doxygen = /tmp/CMT_ExamTruthsetup.make
cmt_local_doxygen_makefile = /tmp/CMT_doxygen$(cmt_lock_pid).make
else
#cmt_local_tagfile_doxygen = $(ExamTruth_tag).make
cmt_local_tagfile_doxygen = $(bin)$(ExamTruth_tag).make
cmt_final_setup_doxygen = $(bin)ExamTruthsetup.make
cmt_local_doxygen_makefile = $(bin)doxygen.make
endif

endif

ifndef QUICK
$(cmt_local_doxygen_makefile) :: $(doxygen_dependencies) $(cmt_local_tagfile_doxygen) build_library_links dirs
else
$(cmt_local_doxygen_makefile) :: $(cmt_local_tagfile_doxygen)
endif
	$(echo) "(constituents.make) Building doxygen.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(doxygen_extratags) build constituent_makefile -out=$(cmt_local_doxygen_makefile) doxygen

doxygen :: $(doxygen_dependencies) $(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Creating doxygen${lock_suffix} and Starting doxygen"
	@{ ${lock_command} doxygen${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} doxygen${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) cmt_lock_pid=$${cmt_lock_pid} doxygen; \
	  retval=$$?; ${unlock_command} doxygen${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) doxygen done"

clean :: doxygenclean

doxygenclean :: $(doxygenclean_dependencies) ##$(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting doxygenclean"
	@-if test -f $(cmt_local_doxygen_makefile); then \
	  $(MAKE) -f $(cmt_local_doxygen_makefile) cmt_lock_pid=$${cmt_lock_pid} doxygenclean; \
	fi

##	  /bin/rm -f $(cmt_local_doxygen_makefile) $(bin)doxygen_dependencies.make

install :: doxygeninstall

doxygeninstall :: $(doxygen_dependencies) $(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting install doxygen"
	@-$(MAKE) -f $(cmt_local_doxygen_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install doxygen done"

uninstall :: doxygenuninstall

doxygenuninstall :: $(cmt_local_doxygen_makefile)
	$(echo) "(constituents.make) Starting uninstall doxygen"
	@-$(MAKE) -f $(cmt_local_doxygen_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall doxygen done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ doxygen"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ doxygen done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_CompilePython_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_CompilePython_has_target_tag

ifdef READONLY
cmt_local_tagfile_CompilePython = /tmp/CMT_$(ExamTruth_tag)_CompilePython.make$(cmt_lock_pid)
cmt_final_setup_CompilePython = /tmp/CMT_ExamTruth_CompilePythonsetup.make
cmt_local_CompilePython_makefile = /tmp/CMT_CompilePython$(cmt_lock_pid).make
else
#cmt_local_tagfile_CompilePython = $(ExamTruth_tag)_CompilePython.make
cmt_local_tagfile_CompilePython = $(bin)$(ExamTruth_tag)_CompilePython.make
cmt_final_setup_CompilePython = $(bin)ExamTruth_CompilePythonsetup.make
cmt_local_CompilePython_makefile = $(bin)CompilePython.make
endif

CompilePython_extratags = -tag_add=target_CompilePython

#$(cmt_local_tagfile_CompilePython) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_CompilePython) ::
else
$(cmt_local_tagfile_CompilePython) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_CompilePython)"
	@if test -f $(cmt_local_tagfile_CompilePython); then /bin/rm -f $(cmt_local_tagfile_CompilePython); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(CompilePython_extratags) build tag_makefile >>$(cmt_local_tagfile_CompilePython); \
	  if test -f $(cmt_final_setup_CompilePython); then /bin/rm -f $(cmt_final_setup_CompilePython); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(CompilePython_extratags) show setup >>$(cmt_final_setup_CompilePython)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_CompilePython = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_CompilePython = /tmp/CMT_ExamTruthsetup.make
cmt_local_CompilePython_makefile = /tmp/CMT_CompilePython$(cmt_lock_pid).make
else
#cmt_local_tagfile_CompilePython = $(ExamTruth_tag).make
cmt_local_tagfile_CompilePython = $(bin)$(ExamTruth_tag).make
cmt_final_setup_CompilePython = $(bin)ExamTruthsetup.make
cmt_local_CompilePython_makefile = $(bin)CompilePython.make
endif

endif

ifndef QUICK
$(cmt_local_CompilePython_makefile) :: $(CompilePython_dependencies) $(cmt_local_tagfile_CompilePython) build_library_links dirs
else
$(cmt_local_CompilePython_makefile) :: $(cmt_local_tagfile_CompilePython)
endif
	$(echo) "(constituents.make) Building CompilePython.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(CompilePython_extratags) build constituent_makefile -out=$(cmt_local_CompilePython_makefile) CompilePython

CompilePython :: $(CompilePython_dependencies) $(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Creating CompilePython${lock_suffix} and Starting CompilePython"
	@{ ${lock_command} CompilePython${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} CompilePython${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) cmt_lock_pid=$${cmt_lock_pid} CompilePython; \
	  retval=$$?; ${unlock_command} CompilePython${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) CompilePython done"

clean :: CompilePythonclean

CompilePythonclean :: $(CompilePythonclean_dependencies) ##$(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting CompilePythonclean"
	@-if test -f $(cmt_local_CompilePython_makefile); then \
	  $(MAKE) -f $(cmt_local_CompilePython_makefile) cmt_lock_pid=$${cmt_lock_pid} CompilePythonclean; \
	fi

##	  /bin/rm -f $(cmt_local_CompilePython_makefile) $(bin)CompilePython_dependencies.make

install :: CompilePythoninstall

CompilePythoninstall :: $(CompilePython_dependencies) $(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting install CompilePython"
	@-$(MAKE) -f $(cmt_local_CompilePython_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install CompilePython done"

uninstall :: CompilePythonuninstall

CompilePythonuninstall :: $(cmt_local_CompilePython_makefile)
	$(echo) "(constituents.make) Starting uninstall CompilePython"
	@-$(MAKE) -f $(cmt_local_CompilePython_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall CompilePython done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ CompilePython"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ CompilePython done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_qmtest_run_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_qmtest_run_has_target_tag

ifdef READONLY
cmt_local_tagfile_qmtest_run = /tmp/CMT_$(ExamTruth_tag)_qmtest_run.make$(cmt_lock_pid)
cmt_final_setup_qmtest_run = /tmp/CMT_ExamTruth_qmtest_runsetup.make
cmt_local_qmtest_run_makefile = /tmp/CMT_qmtest_run$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_run = $(ExamTruth_tag)_qmtest_run.make
cmt_local_tagfile_qmtest_run = $(bin)$(ExamTruth_tag)_qmtest_run.make
cmt_final_setup_qmtest_run = $(bin)ExamTruth_qmtest_runsetup.make
cmt_local_qmtest_run_makefile = $(bin)qmtest_run.make
endif

qmtest_run_extratags = -tag_add=target_qmtest_run

#$(cmt_local_tagfile_qmtest_run) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_qmtest_run) ::
else
$(cmt_local_tagfile_qmtest_run) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_qmtest_run)"
	@if test -f $(cmt_local_tagfile_qmtest_run); then /bin/rm -f $(cmt_local_tagfile_qmtest_run); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_run_extratags) build tag_makefile >>$(cmt_local_tagfile_qmtest_run); \
	  if test -f $(cmt_final_setup_qmtest_run); then /bin/rm -f $(cmt_final_setup_qmtest_run); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_run_extratags) show setup >>$(cmt_final_setup_qmtest_run)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_qmtest_run = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_qmtest_run = /tmp/CMT_ExamTruthsetup.make
cmt_local_qmtest_run_makefile = /tmp/CMT_qmtest_run$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_run = $(ExamTruth_tag).make
cmt_local_tagfile_qmtest_run = $(bin)$(ExamTruth_tag).make
cmt_final_setup_qmtest_run = $(bin)ExamTruthsetup.make
cmt_local_qmtest_run_makefile = $(bin)qmtest_run.make
endif

endif

ifndef QUICK
$(cmt_local_qmtest_run_makefile) :: $(qmtest_run_dependencies) $(cmt_local_tagfile_qmtest_run) build_library_links dirs
else
$(cmt_local_qmtest_run_makefile) :: $(cmt_local_tagfile_qmtest_run)
endif
	$(echo) "(constituents.make) Building qmtest_run.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_run_extratags) build constituent_makefile -out=$(cmt_local_qmtest_run_makefile) qmtest_run

qmtest_run :: $(qmtest_run_dependencies) $(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Creating qmtest_run${lock_suffix} and Starting qmtest_run"
	@{ ${lock_command} qmtest_run${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} qmtest_run${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) cmt_lock_pid=$${cmt_lock_pid} qmtest_run; \
	  retval=$$?; ${unlock_command} qmtest_run${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) qmtest_run done"

clean :: qmtest_runclean

qmtest_runclean :: $(qmtest_runclean_dependencies) ##$(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting qmtest_runclean"
	@-if test -f $(cmt_local_qmtest_run_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_run_makefile) cmt_lock_pid=$${cmt_lock_pid} qmtest_runclean; \
	fi

##	  /bin/rm -f $(cmt_local_qmtest_run_makefile) $(bin)qmtest_run_dependencies.make

install :: qmtest_runinstall

qmtest_runinstall :: $(qmtest_run_dependencies) $(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting install qmtest_run"
	@-$(MAKE) -f $(cmt_local_qmtest_run_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install qmtest_run done"

uninstall :: qmtest_rununinstall

qmtest_rununinstall :: $(cmt_local_qmtest_run_makefile)
	$(echo) "(constituents.make) Starting uninstall qmtest_run"
	@-$(MAKE) -f $(cmt_local_qmtest_run_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall qmtest_run done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ qmtest_run"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ qmtest_run done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_qmtest_summarize_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_qmtest_summarize_has_target_tag

ifdef READONLY
cmt_local_tagfile_qmtest_summarize = /tmp/CMT_$(ExamTruth_tag)_qmtest_summarize.make$(cmt_lock_pid)
cmt_final_setup_qmtest_summarize = /tmp/CMT_ExamTruth_qmtest_summarizesetup.make
cmt_local_qmtest_summarize_makefile = /tmp/CMT_qmtest_summarize$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_summarize = $(ExamTruth_tag)_qmtest_summarize.make
cmt_local_tagfile_qmtest_summarize = $(bin)$(ExamTruth_tag)_qmtest_summarize.make
cmt_final_setup_qmtest_summarize = $(bin)ExamTruth_qmtest_summarizesetup.make
cmt_local_qmtest_summarize_makefile = $(bin)qmtest_summarize.make
endif

qmtest_summarize_extratags = -tag_add=target_qmtest_summarize

#$(cmt_local_tagfile_qmtest_summarize) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_qmtest_summarize) ::
else
$(cmt_local_tagfile_qmtest_summarize) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_qmtest_summarize)"
	@if test -f $(cmt_local_tagfile_qmtest_summarize); then /bin/rm -f $(cmt_local_tagfile_qmtest_summarize); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_summarize_extratags) build tag_makefile >>$(cmt_local_tagfile_qmtest_summarize); \
	  if test -f $(cmt_final_setup_qmtest_summarize); then /bin/rm -f $(cmt_final_setup_qmtest_summarize); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_summarize_extratags) show setup >>$(cmt_final_setup_qmtest_summarize)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_qmtest_summarize = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_qmtest_summarize = /tmp/CMT_ExamTruthsetup.make
cmt_local_qmtest_summarize_makefile = /tmp/CMT_qmtest_summarize$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_summarize = $(ExamTruth_tag).make
cmt_local_tagfile_qmtest_summarize = $(bin)$(ExamTruth_tag).make
cmt_final_setup_qmtest_summarize = $(bin)ExamTruthsetup.make
cmt_local_qmtest_summarize_makefile = $(bin)qmtest_summarize.make
endif

endif

ifndef QUICK
$(cmt_local_qmtest_summarize_makefile) :: $(qmtest_summarize_dependencies) $(cmt_local_tagfile_qmtest_summarize) build_library_links dirs
else
$(cmt_local_qmtest_summarize_makefile) :: $(cmt_local_tagfile_qmtest_summarize)
endif
	$(echo) "(constituents.make) Building qmtest_summarize.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(qmtest_summarize_extratags) build constituent_makefile -out=$(cmt_local_qmtest_summarize_makefile) qmtest_summarize

qmtest_summarize :: $(qmtest_summarize_dependencies) $(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Creating qmtest_summarize${lock_suffix} and Starting qmtest_summarize"
	@{ ${lock_command} qmtest_summarize${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} qmtest_summarize${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) cmt_lock_pid=$${cmt_lock_pid} qmtest_summarize; \
	  retval=$$?; ${unlock_command} qmtest_summarize${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) qmtest_summarize done"

clean :: qmtest_summarizeclean

qmtest_summarizeclean :: $(qmtest_summarizeclean_dependencies) ##$(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting qmtest_summarizeclean"
	@-if test -f $(cmt_local_qmtest_summarize_makefile); then \
	  $(MAKE) -f $(cmt_local_qmtest_summarize_makefile) cmt_lock_pid=$${cmt_lock_pid} qmtest_summarizeclean; \
	fi

##	  /bin/rm -f $(cmt_local_qmtest_summarize_makefile) $(bin)qmtest_summarize_dependencies.make

install :: qmtest_summarizeinstall

qmtest_summarizeinstall :: $(qmtest_summarize_dependencies) $(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting install qmtest_summarize"
	@-$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install qmtest_summarize done"

uninstall :: qmtest_summarizeuninstall

qmtest_summarizeuninstall :: $(cmt_local_qmtest_summarize_makefile)
	$(echo) "(constituents.make) Starting uninstall qmtest_summarize"
	@-$(MAKE) -f $(cmt_local_qmtest_summarize_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall qmtest_summarize done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ qmtest_summarize"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ qmtest_summarize done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_TestPackage_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_TestPackage_has_target_tag

ifdef READONLY
cmt_local_tagfile_TestPackage = /tmp/CMT_$(ExamTruth_tag)_TestPackage.make$(cmt_lock_pid)
cmt_final_setup_TestPackage = /tmp/CMT_ExamTruth_TestPackagesetup.make
cmt_local_TestPackage_makefile = /tmp/CMT_TestPackage$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestPackage = $(ExamTruth_tag)_TestPackage.make
cmt_local_tagfile_TestPackage = $(bin)$(ExamTruth_tag)_TestPackage.make
cmt_final_setup_TestPackage = $(bin)ExamTruth_TestPackagesetup.make
cmt_local_TestPackage_makefile = $(bin)TestPackage.make
endif

TestPackage_extratags = -tag_add=target_TestPackage

#$(cmt_local_tagfile_TestPackage) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_TestPackage) ::
else
$(cmt_local_tagfile_TestPackage) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_TestPackage)"
	@if test -f $(cmt_local_tagfile_TestPackage); then /bin/rm -f $(cmt_local_tagfile_TestPackage); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestPackage_extratags) build tag_makefile >>$(cmt_local_tagfile_TestPackage); \
	  if test -f $(cmt_final_setup_TestPackage); then /bin/rm -f $(cmt_final_setup_TestPackage); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestPackage_extratags) show setup >>$(cmt_final_setup_TestPackage)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_TestPackage = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_TestPackage = /tmp/CMT_ExamTruthsetup.make
cmt_local_TestPackage_makefile = /tmp/CMT_TestPackage$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestPackage = $(ExamTruth_tag).make
cmt_local_tagfile_TestPackage = $(bin)$(ExamTruth_tag).make
cmt_final_setup_TestPackage = $(bin)ExamTruthsetup.make
cmt_local_TestPackage_makefile = $(bin)TestPackage.make
endif

endif

ifndef QUICK
$(cmt_local_TestPackage_makefile) :: $(TestPackage_dependencies) $(cmt_local_tagfile_TestPackage) build_library_links dirs
else
$(cmt_local_TestPackage_makefile) :: $(cmt_local_tagfile_TestPackage)
endif
	$(echo) "(constituents.make) Building TestPackage.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestPackage_extratags) build constituent_makefile -out=$(cmt_local_TestPackage_makefile) TestPackage

TestPackage :: $(TestPackage_dependencies) $(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Creating TestPackage${lock_suffix} and Starting TestPackage"
	@{ ${lock_command} TestPackage${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} TestPackage${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) cmt_lock_pid=$${cmt_lock_pid} TestPackage; \
	  retval=$$?; ${unlock_command} TestPackage${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) TestPackage done"

clean :: TestPackageclean

TestPackageclean :: $(TestPackageclean_dependencies) ##$(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting TestPackageclean"
	@-if test -f $(cmt_local_TestPackage_makefile); then \
	  $(MAKE) -f $(cmt_local_TestPackage_makefile) cmt_lock_pid=$${cmt_lock_pid} TestPackageclean; \
	fi

##	  /bin/rm -f $(cmt_local_TestPackage_makefile) $(bin)TestPackage_dependencies.make

install :: TestPackageinstall

TestPackageinstall :: $(TestPackage_dependencies) $(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting install TestPackage"
	@-$(MAKE) -f $(cmt_local_TestPackage_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install TestPackage done"

uninstall :: TestPackageuninstall

TestPackageuninstall :: $(cmt_local_TestPackage_makefile)
	$(echo) "(constituents.make) Starting uninstall TestPackage"
	@-$(MAKE) -f $(cmt_local_TestPackage_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall TestPackage done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ TestPackage"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ TestPackage done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_TestProject_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_TestProject_has_target_tag

ifdef READONLY
cmt_local_tagfile_TestProject = /tmp/CMT_$(ExamTruth_tag)_TestProject.make$(cmt_lock_pid)
cmt_final_setup_TestProject = /tmp/CMT_ExamTruth_TestProjectsetup.make
cmt_local_TestProject_makefile = /tmp/CMT_TestProject$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestProject = $(ExamTruth_tag)_TestProject.make
cmt_local_tagfile_TestProject = $(bin)$(ExamTruth_tag)_TestProject.make
cmt_final_setup_TestProject = $(bin)ExamTruth_TestProjectsetup.make
cmt_local_TestProject_makefile = $(bin)TestProject.make
endif

TestProject_extratags = -tag_add=target_TestProject

#$(cmt_local_tagfile_TestProject) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_TestProject) ::
else
$(cmt_local_tagfile_TestProject) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_TestProject)"
	@if test -f $(cmt_local_tagfile_TestProject); then /bin/rm -f $(cmt_local_tagfile_TestProject); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestProject_extratags) build tag_makefile >>$(cmt_local_tagfile_TestProject); \
	  if test -f $(cmt_final_setup_TestProject); then /bin/rm -f $(cmt_final_setup_TestProject); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestProject_extratags) show setup >>$(cmt_final_setup_TestProject)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_TestProject = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_TestProject = /tmp/CMT_ExamTruthsetup.make
cmt_local_TestProject_makefile = /tmp/CMT_TestProject$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestProject = $(ExamTruth_tag).make
cmt_local_tagfile_TestProject = $(bin)$(ExamTruth_tag).make
cmt_final_setup_TestProject = $(bin)ExamTruthsetup.make
cmt_local_TestProject_makefile = $(bin)TestProject.make
endif

endif

ifndef QUICK
$(cmt_local_TestProject_makefile) :: $(TestProject_dependencies) $(cmt_local_tagfile_TestProject) build_library_links dirs
else
$(cmt_local_TestProject_makefile) :: $(cmt_local_tagfile_TestProject)
endif
	$(echo) "(constituents.make) Building TestProject.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(TestProject_extratags) build constituent_makefile -out=$(cmt_local_TestProject_makefile) TestProject

TestProject :: $(TestProject_dependencies) $(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Creating TestProject${lock_suffix} and Starting TestProject"
	@{ ${lock_command} TestProject${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} TestProject${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) cmt_lock_pid=$${cmt_lock_pid} TestProject; \
	  retval=$$?; ${unlock_command} TestProject${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) TestProject done"

clean :: TestProjectclean

TestProjectclean :: $(TestProjectclean_dependencies) ##$(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting TestProjectclean"
	@-if test -f $(cmt_local_TestProject_makefile); then \
	  $(MAKE) -f $(cmt_local_TestProject_makefile) cmt_lock_pid=$${cmt_lock_pid} TestProjectclean; \
	fi

##	  /bin/rm -f $(cmt_local_TestProject_makefile) $(bin)TestProject_dependencies.make

install :: TestProjectinstall

TestProjectinstall :: $(TestProject_dependencies) $(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting install TestProject"
	@-$(MAKE) -f $(cmt_local_TestProject_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install TestProject done"

uninstall :: TestProjectuninstall

TestProjectuninstall :: $(cmt_local_TestProject_makefile)
	$(echo) "(constituents.make) Starting uninstall TestProject"
	@-$(MAKE) -f $(cmt_local_TestProject_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall TestProject done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ TestProject"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ TestProject done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_new_rootsys_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_new_rootsys_has_target_tag

ifdef READONLY
cmt_local_tagfile_new_rootsys = /tmp/CMT_$(ExamTruth_tag)_new_rootsys.make$(cmt_lock_pid)
cmt_final_setup_new_rootsys = /tmp/CMT_ExamTruth_new_rootsyssetup.make
cmt_local_new_rootsys_makefile = /tmp/CMT_new_rootsys$(cmt_lock_pid).make
else
#cmt_local_tagfile_new_rootsys = $(ExamTruth_tag)_new_rootsys.make
cmt_local_tagfile_new_rootsys = $(bin)$(ExamTruth_tag)_new_rootsys.make
cmt_final_setup_new_rootsys = $(bin)ExamTruth_new_rootsyssetup.make
cmt_local_new_rootsys_makefile = $(bin)new_rootsys.make
endif

new_rootsys_extratags = -tag_add=target_new_rootsys

#$(cmt_local_tagfile_new_rootsys) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_new_rootsys) ::
else
$(cmt_local_tagfile_new_rootsys) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_new_rootsys)"
	@if test -f $(cmt_local_tagfile_new_rootsys); then /bin/rm -f $(cmt_local_tagfile_new_rootsys); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(new_rootsys_extratags) build tag_makefile >>$(cmt_local_tagfile_new_rootsys); \
	  if test -f $(cmt_final_setup_new_rootsys); then /bin/rm -f $(cmt_final_setup_new_rootsys); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(new_rootsys_extratags) show setup >>$(cmt_final_setup_new_rootsys)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_new_rootsys = /tmp/CMT_$(ExamTruth_tag).make$(cmt_lock_pid)
cmt_final_setup_new_rootsys = /tmp/CMT_ExamTruthsetup.make
cmt_local_new_rootsys_makefile = /tmp/CMT_new_rootsys$(cmt_lock_pid).make
else
#cmt_local_tagfile_new_rootsys = $(ExamTruth_tag).make
cmt_local_tagfile_new_rootsys = $(bin)$(ExamTruth_tag).make
cmt_final_setup_new_rootsys = $(bin)ExamTruthsetup.make
cmt_local_new_rootsys_makefile = $(bin)new_rootsys.make
endif

endif

ifndef QUICK
$(cmt_local_new_rootsys_makefile) :: $(new_rootsys_dependencies) $(cmt_local_tagfile_new_rootsys) build_library_links dirs
else
$(cmt_local_new_rootsys_makefile) :: $(cmt_local_tagfile_new_rootsys)
endif
	$(echo) "(constituents.make) Building new_rootsys.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(new_rootsys_extratags) build constituent_makefile -out=$(cmt_local_new_rootsys_makefile) new_rootsys

new_rootsys :: $(new_rootsys_dependencies) $(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Creating new_rootsys${lock_suffix} and Starting new_rootsys"
	@{ ${lock_command} new_rootsys${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} new_rootsys${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) cmt_lock_pid=$${cmt_lock_pid} new_rootsys; \
	  retval=$$?; ${unlock_command} new_rootsys${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) new_rootsys done"

clean :: new_rootsysclean

new_rootsysclean :: $(new_rootsysclean_dependencies) ##$(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting new_rootsysclean"
	@-if test -f $(cmt_local_new_rootsys_makefile); then \
	  $(MAKE) -f $(cmt_local_new_rootsys_makefile) cmt_lock_pid=$${cmt_lock_pid} new_rootsysclean; \
	fi

##	  /bin/rm -f $(cmt_local_new_rootsys_makefile) $(bin)new_rootsys_dependencies.make

install :: new_rootsysinstall

new_rootsysinstall :: $(new_rootsys_dependencies) $(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting install new_rootsys"
	@-$(MAKE) -f $(cmt_local_new_rootsys_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install new_rootsys done"

uninstall :: new_rootsysuninstall

new_rootsysuninstall :: $(cmt_local_new_rootsys_makefile)
	$(echo) "(constituents.make) Starting uninstall new_rootsys"
	@-$(MAKE) -f $(cmt_local_new_rootsys_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall new_rootsys done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ new_rootsys"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ new_rootsys done"
endif


#-- end of constituent_lock ------
#-- start of constituents_trailer ------

clean :: remove_library_links

remove_library_links ::
	$(echo) "Removing library links"; \
	  $(remove_library_links)

makefilesclean ::

###	@/bin/rm -f checkuses

###	/bin/rm -f *.make*

clean :: makefilesclean

binclean :: clean
	$(echo) "Removing binary directory $(bin)"
	@if test ! "$(bin)" = "./"; then \
	  /bin/rm -rf $(bin); \
	fi

#-- end of constituents_trailer ------
