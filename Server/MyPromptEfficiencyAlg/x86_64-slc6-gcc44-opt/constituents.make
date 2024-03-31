
#-- start of constituents_header ------

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

#-include $(cmt_local_tagfile)
include $(cmt_local_tagfile)

ifdef READONLY
cmt_local_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup$(cmt_lock_pid).make
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
#cmt_local_setup = $(bin)MyPromptEfficiencyAlgsetup$(cmt_lock_pid).make
cmt_local_setup = $(bin)$(package)setup$$$$.make
#cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
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

cmt_MyPromptEfficiencyAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlg_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = /tmp/CMT_MyPromptEfficiencyAlg$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make
cmt_local_tagfile_MyPromptEfficiencyAlg = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg.make
cmt_final_setup_MyPromptEfficiencyAlg = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = $(bin)MyPromptEfficiencyAlg.make
endif

MyPromptEfficiencyAlg_extratags = -tag_add=target_MyPromptEfficiencyAlg

#$(cmt_local_tagfile_MyPromptEfficiencyAlg) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlg) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlg) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlg)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlg); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlg); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlg); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlg); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlg); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlg)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = /tmp/CMT_MyPromptEfficiencyAlg$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlg = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlg = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_makefile = $(bin)MyPromptEfficiencyAlg.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlg_makefile) :: $(MyPromptEfficiencyAlg_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlg) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlg_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlg)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlg.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlg_makefile) MyPromptEfficiencyAlg

MyPromptEfficiencyAlg :: $(MyPromptEfficiencyAlg_dependencies) $(cmt_local_MyPromptEfficiencyAlg_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlg"
	@$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlg
	$(echo) "(constituents.make) MyPromptEfficiencyAlg done"

clean :: MyPromptEfficiencyAlgclean

MyPromptEfficiencyAlgclean :: $(MyPromptEfficiencyAlgclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlg_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlg_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlg_makefile) $(bin)MyPromptEfficiencyAlg_dependencies.make

install :: MyPromptEfficiencyAlginstall

MyPromptEfficiencyAlginstall :: $(MyPromptEfficiencyAlg_dependencies) $(cmt_local_MyPromptEfficiencyAlg_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlg"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlg done"

uninstall :: MyPromptEfficiencyAlguninstall

MyPromptEfficiencyAlguninstall :: $(cmt_local_MyPromptEfficiencyAlg_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlg"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlg done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlg"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlg done"
endif


#-- end of constituent ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgRootMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgRootMap_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgRootMap = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgRootMapsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgRootMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make
cmt_final_setup_MyPromptEfficiencyAlgRootMap = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgRootMapsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = $(bin)MyPromptEfficiencyAlgRootMap.make
endif

MyPromptEfficiencyAlgRootMap_extratags = -tag_add=target_MyPromptEfficiencyAlgRootMap

#$(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgRootMap_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgRootMap); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgRootMap); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgRootMap_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgRootMap)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgRootMap = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgRootMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgRootMap = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = $(bin)MyPromptEfficiencyAlgRootMap.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) :: $(MyPromptEfficiencyAlgRootMap_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgRootMap.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgRootMap_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) MyPromptEfficiencyAlgRootMap

MyPromptEfficiencyAlgRootMap :: $(MyPromptEfficiencyAlgRootMap_dependencies) $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgRootMap${lock_suffix} and Starting MyPromptEfficiencyAlgRootMap"
	@{ ${lock_command} MyPromptEfficiencyAlgRootMap${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgRootMap${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgRootMap; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgRootMap${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgRootMap done"

clean :: MyPromptEfficiencyAlgRootMapclean

MyPromptEfficiencyAlgRootMapclean :: $(MyPromptEfficiencyAlgRootMapclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgRootMap_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgRootMapclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgRootMapclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) $(bin)MyPromptEfficiencyAlgRootMap_dependencies.make

install :: MyPromptEfficiencyAlgRootMapinstall

MyPromptEfficiencyAlgRootMapinstall :: $(MyPromptEfficiencyAlgRootMap_dependencies) $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgRootMap"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgRootMap done"

uninstall :: MyPromptEfficiencyAlgRootMapuninstall

MyPromptEfficiencyAlgRootMapuninstall :: $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgRootMap"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgRootMap_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgRootMap done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgRootMap"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgRootMap done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgMergeMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgMergeMap_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgMergeMapsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgMergeMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgMergeMap.make
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgMergeMapsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = $(bin)MyPromptEfficiencyAlgMergeMap.make
endif

MyPromptEfficiencyAlgMergeMap_extratags = -tag_add=target_MyPromptEfficiencyAlgMergeMap

#$(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgMergeMap_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgMergeMap); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgMergeMap); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgMergeMap_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgMergeMap)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgMergeMap$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgMergeMap = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgMergeMap_makefile = $(bin)MyPromptEfficiencyAlgMergeMap.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) :: $(MyPromptEfficiencyAlgMergeMap_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgMergeMap)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgMergeMap.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgMergeMap_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) MyPromptEfficiencyAlgMergeMap

MyPromptEfficiencyAlgMergeMap :: $(MyPromptEfficiencyAlgMergeMap_dependencies) $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgMergeMap${lock_suffix} and Starting MyPromptEfficiencyAlgMergeMap"
	@{ ${lock_command} MyPromptEfficiencyAlgMergeMap${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgMergeMap${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgMergeMap; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgMergeMap${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgMergeMap done"

clean :: MyPromptEfficiencyAlgMergeMapclean

MyPromptEfficiencyAlgMergeMapclean :: $(MyPromptEfficiencyAlgMergeMapclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgMergeMapclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgMergeMapclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) $(bin)MyPromptEfficiencyAlgMergeMap_dependencies.make

install :: MyPromptEfficiencyAlgMergeMapinstall

MyPromptEfficiencyAlgMergeMapinstall :: $(MyPromptEfficiencyAlgMergeMap_dependencies) $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgMergeMap"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgMergeMap done"

uninstall :: MyPromptEfficiencyAlgMergeMapuninstall

MyPromptEfficiencyAlgMergeMapuninstall :: $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgMergeMap"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgMergeMap_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgMergeMap done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgMergeMap"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgMergeMap done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgConf_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConf_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConf = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConf = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = /tmp/CMT_MyPromptEfficiencyAlgConf$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make
cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConf.make
cmt_final_setup_MyPromptEfficiencyAlgConf = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = $(bin)MyPromptEfficiencyAlgConf.make
endif

MyPromptEfficiencyAlgConf_extratags = -tag_add=target_MyPromptEfficiencyAlgConf

#$(cmt_local_tagfile_MyPromptEfficiencyAlgConf) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgConf) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgConf) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgConf)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConf); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConf); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConf_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgConf); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgConf); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgConf); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConf_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgConf)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConf = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConf = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = /tmp/CMT_MyPromptEfficiencyAlgConf$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConf = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgConf = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConf_makefile = $(bin)MyPromptEfficiencyAlgConf.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgConf_makefile) :: $(MyPromptEfficiencyAlgConf_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgConf) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgConf_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgConf)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgConf.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConf_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgConf_makefile) MyPromptEfficiencyAlgConf

MyPromptEfficiencyAlgConf :: $(MyPromptEfficiencyAlgConf_dependencies) $(cmt_local_MyPromptEfficiencyAlgConf_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgConf${lock_suffix} and Starting MyPromptEfficiencyAlgConf"
	@{ ${lock_command} MyPromptEfficiencyAlgConf${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgConf${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConf; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgConf${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgConf done"

clean :: MyPromptEfficiencyAlgConfclean

MyPromptEfficiencyAlgConfclean :: $(MyPromptEfficiencyAlgConfclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgConf_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgConfclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConfclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile) $(bin)MyPromptEfficiencyAlgConf_dependencies.make

install :: MyPromptEfficiencyAlgConfinstall

MyPromptEfficiencyAlgConfinstall :: $(MyPromptEfficiencyAlgConf_dependencies) $(cmt_local_MyPromptEfficiencyAlgConf_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgConf"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgConf done"

uninstall :: MyPromptEfficiencyAlgConfuninstall

MyPromptEfficiencyAlgConfuninstall :: $(cmt_local_MyPromptEfficiencyAlgConf_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgConf"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConf_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgConf done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgConf"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgConf done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlg_python_init_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlg_python_init_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python_init.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg_python_init = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_python_initsetup.make
cmt_local_MyPromptEfficiencyAlg_python_init_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python_init$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python_init.make
cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python_init.make
cmt_final_setup_MyPromptEfficiencyAlg_python_init = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_python_initsetup.make
cmt_local_MyPromptEfficiencyAlg_python_init_makefile = $(bin)MyPromptEfficiencyAlg_python_init.make
endif

MyPromptEfficiencyAlg_python_init_extratags = -tag_add=target_MyPromptEfficiencyAlg_python_init

#$(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_init_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlg_python_init); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlg_python_init); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_init_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlg_python_init)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg_python_init = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_init_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python_init$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlg_python_init = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlg_python_init = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_init_makefile = $(bin)MyPromptEfficiencyAlg_python_init.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) :: $(MyPromptEfficiencyAlg_python_init_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlg_python_init)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlg_python_init.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_init_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) MyPromptEfficiencyAlg_python_init

MyPromptEfficiencyAlg_python_init :: $(MyPromptEfficiencyAlg_python_init_dependencies) $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlg_python_init${lock_suffix} and Starting MyPromptEfficiencyAlg_python_init"
	@{ ${lock_command} MyPromptEfficiencyAlg_python_init${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlg_python_init${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlg_python_init; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlg_python_init${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlg_python_init done"

clean :: MyPromptEfficiencyAlg_python_initclean

MyPromptEfficiencyAlg_python_initclean :: $(MyPromptEfficiencyAlg_python_initclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlg_python_init_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlg_python_initclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlg_python_initclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) $(bin)MyPromptEfficiencyAlg_python_init_dependencies.make

install :: MyPromptEfficiencyAlg_python_initinstall

MyPromptEfficiencyAlg_python_initinstall :: $(MyPromptEfficiencyAlg_python_init_dependencies) $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlg_python_init"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlg_python_init done"

uninstall :: MyPromptEfficiencyAlg_python_inituninstall

MyPromptEfficiencyAlg_python_inituninstall :: $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlg_python_init"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_init_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlg_python_init done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlg_python_init"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlg_python_init done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgConfDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConfDbMerge_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfDbMerge.make
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfDbMerge.make
endif

MyPromptEfficiencyAlgConfDbMerge_extratags = -tag_add=target_MyPromptEfficiencyAlgConfDbMerge

#$(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfDbMerge_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfDbMerge_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgConfDbMerge = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfDbMerge.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) :: $(MyPromptEfficiencyAlgConfDbMerge_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgConfDbMerge)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgConfDbMerge.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfDbMerge_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) MyPromptEfficiencyAlgConfDbMerge

MyPromptEfficiencyAlgConfDbMerge :: $(MyPromptEfficiencyAlgConfDbMerge_dependencies) $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgConfDbMerge${lock_suffix} and Starting MyPromptEfficiencyAlgConfDbMerge"
	@{ ${lock_command} MyPromptEfficiencyAlgConfDbMerge${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgConfDbMerge${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConfDbMerge; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgConfDbMerge${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgConfDbMerge done"

clean :: MyPromptEfficiencyAlgConfDbMergeclean

MyPromptEfficiencyAlgConfDbMergeclean :: $(MyPromptEfficiencyAlgConfDbMergeclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgConfDbMergeclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConfDbMergeclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) $(bin)MyPromptEfficiencyAlgConfDbMerge_dependencies.make

install :: MyPromptEfficiencyAlgConfDbMergeinstall

MyPromptEfficiencyAlgConfDbMergeinstall :: $(MyPromptEfficiencyAlgConfDbMerge_dependencies) $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgConfDbMerge"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgConfDbMerge done"

uninstall :: MyPromptEfficiencyAlgConfDbMergeuninstall

MyPromptEfficiencyAlgConfDbMergeuninstall :: $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgConfDbMerge"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgConfDbMerge done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgConfDbMerge"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgConfDbMerge done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_install_scripts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_install_scripts_has_target_tag

ifdef READONLY
cmt_local_tagfile_install_scripts = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_install_scripts.make$(cmt_lock_pid)
cmt_final_setup_install_scripts = /tmp/CMT_MyPromptEfficiencyAlg_install_scriptssetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
#cmt_local_tagfile_install_scripts = $(MyPromptEfficiencyAlg_tag)_install_scripts.make
cmt_local_tagfile_install_scripts = $(bin)$(MyPromptEfficiencyAlg_tag)_install_scripts.make
cmt_final_setup_install_scripts = $(bin)MyPromptEfficiencyAlg_install_scriptssetup.make
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
cmt_local_tagfile_install_scripts = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_install_scripts = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_install_scripts_makefile = /tmp/CMT_install_scripts$(cmt_lock_pid).make
else
#cmt_local_tagfile_install_scripts = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_install_scripts = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_install_scripts = $(bin)MyPromptEfficiencyAlgsetup.make
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

cmt_MyPromptEfficiencyAlg_python_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlg_python_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg_python = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_pythonsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make
cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlg_python.make
cmt_final_setup_MyPromptEfficiencyAlg_python = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlg_pythonsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = $(bin)MyPromptEfficiencyAlg_python.make
endif

MyPromptEfficiencyAlg_python_extratags = -tag_add=target_MyPromptEfficiencyAlg_python

#$(cmt_local_tagfile_MyPromptEfficiencyAlg_python) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlg_python) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlg_python) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlg_python)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlg_python); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlg_python); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlg_python); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlg_python); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlg_python); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlg_python)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlg_python = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlg_python = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = /tmp/CMT_MyPromptEfficiencyAlg_python$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlg_python = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlg_python = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlg_python_makefile = $(bin)MyPromptEfficiencyAlg_python.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlg_python_makefile) :: $(MyPromptEfficiencyAlg_python_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlg_python) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlg_python_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlg_python)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlg_python.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlg_python_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlg_python_makefile) MyPromptEfficiencyAlg_python

MyPromptEfficiencyAlg_python :: $(MyPromptEfficiencyAlg_python_dependencies) $(cmt_local_MyPromptEfficiencyAlg_python_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlg_python${lock_suffix} and Starting MyPromptEfficiencyAlg_python"
	@{ ${lock_command} MyPromptEfficiencyAlg_python${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlg_python${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlg_python; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlg_python${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlg_python done"

clean :: MyPromptEfficiencyAlg_pythonclean

MyPromptEfficiencyAlg_pythonclean :: $(MyPromptEfficiencyAlg_pythonclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlg_python_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlg_pythonclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlg_pythonclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile) $(bin)MyPromptEfficiencyAlg_python_dependencies.make

install :: MyPromptEfficiencyAlg_pythoninstall

MyPromptEfficiencyAlg_pythoninstall :: $(MyPromptEfficiencyAlg_python_dependencies) $(cmt_local_MyPromptEfficiencyAlg_python_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlg_python"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlg_python done"

uninstall :: MyPromptEfficiencyAlg_pythonuninstall

MyPromptEfficiencyAlg_pythonuninstall :: $(cmt_local_MyPromptEfficiencyAlg_python_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlg_python"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlg_python_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlg_python done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlg_python"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlg_python done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgGenConfUser_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgGenConfUser_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgGenConfUsersetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = /tmp/CMT_MyPromptEfficiencyAlgGenConfUser$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgGenConfUser.make
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgGenConfUsersetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = $(bin)MyPromptEfficiencyAlgGenConfUser.make
endif

MyPromptEfficiencyAlgGenConfUser_extratags = -tag_add=target_MyPromptEfficiencyAlgGenConfUser

#$(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgGenConfUser_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgGenConfUser); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgGenConfUser); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgGenConfUser_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgGenConfUser)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = /tmp/CMT_MyPromptEfficiencyAlgGenConfUser$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgGenConfUser = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile = $(bin)MyPromptEfficiencyAlgGenConfUser.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) :: $(MyPromptEfficiencyAlgGenConfUser_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgGenConfUser)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgGenConfUser.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgGenConfUser_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) MyPromptEfficiencyAlgGenConfUser

MyPromptEfficiencyAlgGenConfUser :: $(MyPromptEfficiencyAlgGenConfUser_dependencies) $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgGenConfUser${lock_suffix} and Starting MyPromptEfficiencyAlgGenConfUser"
	@{ ${lock_command} MyPromptEfficiencyAlgGenConfUser${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgGenConfUser${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgGenConfUser; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgGenConfUser${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgGenConfUser done"

clean :: MyPromptEfficiencyAlgGenConfUserclean

MyPromptEfficiencyAlgGenConfUserclean :: $(MyPromptEfficiencyAlgGenConfUserclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgGenConfUserclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgGenConfUserclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) $(bin)MyPromptEfficiencyAlgGenConfUser_dependencies.make

install :: MyPromptEfficiencyAlgGenConfUserinstall

MyPromptEfficiencyAlgGenConfUserinstall :: $(MyPromptEfficiencyAlgGenConfUser_dependencies) $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgGenConfUser"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgGenConfUser done"

uninstall :: MyPromptEfficiencyAlgGenConfUseruninstall

MyPromptEfficiencyAlgGenConfUseruninstall :: $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgGenConfUser"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgGenConfUser_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgGenConfUser done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgGenConfUser"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgGenConfUser done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_MyPromptEfficiencyAlgConfUserDbMerge_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgConfUserDbMerge_has_target_tag

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfUserDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfUserDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgConfUserDbMerge.make
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgConfUserDbMergesetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfUserDbMerge.make
endif

MyPromptEfficiencyAlgConfUserDbMerge_extratags = -tag_add=target_MyPromptEfficiencyAlgConfUserDbMerge

#$(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge) ::
else
$(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge)"
	@if test -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge); then /bin/rm -f $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge); fi ; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfUserDbMerge_extratags) build tag_makefile >>$(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge); \
	  if test -f $(cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge); then /bin/rm -f $(cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge); fi; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfUserDbMerge_extratags) show setup >>$(cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = /tmp/CMT_MyPromptEfficiencyAlgConfUserDbMerge$(cmt_lock_pid).make
else
#cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_MyPromptEfficiencyAlgConfUserDbMerge = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile = $(bin)MyPromptEfficiencyAlgConfUserDbMerge.make
endif

endif

ifndef QUICK
$(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) :: $(MyPromptEfficiencyAlgConfUserDbMerge_dependencies) $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge) build_library_links dirs
else
$(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) :: $(cmt_local_tagfile_MyPromptEfficiencyAlgConfUserDbMerge)
endif
	$(echo) "(constituents.make) Building MyPromptEfficiencyAlgConfUserDbMerge.make"; \
	  $(cmtexe) -quiet -tag=$(tags) $(MyPromptEfficiencyAlgConfUserDbMerge_extratags) build constituent_makefile -out=$(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) MyPromptEfficiencyAlgConfUserDbMerge

MyPromptEfficiencyAlgConfUserDbMerge :: $(MyPromptEfficiencyAlgConfUserDbMerge_dependencies) $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Creating MyPromptEfficiencyAlgConfUserDbMerge${lock_suffix} and Starting MyPromptEfficiencyAlgConfUserDbMerge"
	@{ ${lock_command} MyPromptEfficiencyAlgConfUserDbMerge${lock_suffix} || exit $$?; } ; \
	  retval=$$?; \
	  trap '${unlock_command} MyPromptEfficiencyAlgConfUserDbMerge${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConfUserDbMerge; \
	  retval=$$?; ${unlock_command} MyPromptEfficiencyAlgConfUserDbMerge${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) MyPromptEfficiencyAlgConfUserDbMerge done"

clean :: MyPromptEfficiencyAlgConfUserDbMergeclean

MyPromptEfficiencyAlgConfUserDbMergeclean :: $(MyPromptEfficiencyAlgConfUserDbMergeclean_dependencies) ##$(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting MyPromptEfficiencyAlgConfUserDbMergeclean"
	@-if test -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile); then \
	  $(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} MyPromptEfficiencyAlgConfUserDbMergeclean; \
	fi

##	  /bin/rm -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) $(bin)MyPromptEfficiencyAlgConfUserDbMerge_dependencies.make

install :: MyPromptEfficiencyAlgConfUserDbMergeinstall

MyPromptEfficiencyAlgConfUserDbMergeinstall :: $(MyPromptEfficiencyAlgConfUserDbMerge_dependencies) $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting install MyPromptEfficiencyAlgConfUserDbMerge"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install MyPromptEfficiencyAlgConfUserDbMerge done"

uninstall :: MyPromptEfficiencyAlgConfUserDbMergeuninstall

MyPromptEfficiencyAlgConfUserDbMergeuninstall :: $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile)
	$(echo) "(constituents.make) Starting uninstall MyPromptEfficiencyAlgConfUserDbMerge"
	@-$(MAKE) -f $(cmt_local_MyPromptEfficiencyAlgConfUserDbMerge_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall MyPromptEfficiencyAlgConfUserDbMerge done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ MyPromptEfficiencyAlgConfUserDbMerge"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ MyPromptEfficiencyAlgConfUserDbMerge done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_make_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_make_has_target_tag

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_make.make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_MyPromptEfficiencyAlg_makesetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(MyPromptEfficiencyAlg_tag)_make.make
cmt_local_tagfile_make = $(bin)$(MyPromptEfficiencyAlg_tag)_make.make
cmt_final_setup_make = $(bin)MyPromptEfficiencyAlg_makesetup.make
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
cmt_local_tagfile_make = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_make = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_make = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_doxygen = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_doxygen.make$(cmt_lock_pid)
cmt_final_setup_doxygen = /tmp/CMT_MyPromptEfficiencyAlg_doxygensetup.make
cmt_local_doxygen_makefile = /tmp/CMT_doxygen$(cmt_lock_pid).make
else
#cmt_local_tagfile_doxygen = $(MyPromptEfficiencyAlg_tag)_doxygen.make
cmt_local_tagfile_doxygen = $(bin)$(MyPromptEfficiencyAlg_tag)_doxygen.make
cmt_final_setup_doxygen = $(bin)MyPromptEfficiencyAlg_doxygensetup.make
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
cmt_local_tagfile_doxygen = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_doxygen = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_doxygen_makefile = /tmp/CMT_doxygen$(cmt_lock_pid).make
else
#cmt_local_tagfile_doxygen = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_doxygen = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_doxygen = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_CompilePython = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_CompilePython.make$(cmt_lock_pid)
cmt_final_setup_CompilePython = /tmp/CMT_MyPromptEfficiencyAlg_CompilePythonsetup.make
cmt_local_CompilePython_makefile = /tmp/CMT_CompilePython$(cmt_lock_pid).make
else
#cmt_local_tagfile_CompilePython = $(MyPromptEfficiencyAlg_tag)_CompilePython.make
cmt_local_tagfile_CompilePython = $(bin)$(MyPromptEfficiencyAlg_tag)_CompilePython.make
cmt_final_setup_CompilePython = $(bin)MyPromptEfficiencyAlg_CompilePythonsetup.make
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
cmt_local_tagfile_CompilePython = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_CompilePython = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_CompilePython_makefile = /tmp/CMT_CompilePython$(cmt_lock_pid).make
else
#cmt_local_tagfile_CompilePython = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_CompilePython = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_CompilePython = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_qmtest_run = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_qmtest_run.make$(cmt_lock_pid)
cmt_final_setup_qmtest_run = /tmp/CMT_MyPromptEfficiencyAlg_qmtest_runsetup.make
cmt_local_qmtest_run_makefile = /tmp/CMT_qmtest_run$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_run = $(MyPromptEfficiencyAlg_tag)_qmtest_run.make
cmt_local_tagfile_qmtest_run = $(bin)$(MyPromptEfficiencyAlg_tag)_qmtest_run.make
cmt_final_setup_qmtest_run = $(bin)MyPromptEfficiencyAlg_qmtest_runsetup.make
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
cmt_local_tagfile_qmtest_run = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_qmtest_run = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_qmtest_run_makefile = /tmp/CMT_qmtest_run$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_run = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_qmtest_run = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_qmtest_run = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_qmtest_summarize = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_qmtest_summarize.make$(cmt_lock_pid)
cmt_final_setup_qmtest_summarize = /tmp/CMT_MyPromptEfficiencyAlg_qmtest_summarizesetup.make
cmt_local_qmtest_summarize_makefile = /tmp/CMT_qmtest_summarize$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_summarize = $(MyPromptEfficiencyAlg_tag)_qmtest_summarize.make
cmt_local_tagfile_qmtest_summarize = $(bin)$(MyPromptEfficiencyAlg_tag)_qmtest_summarize.make
cmt_final_setup_qmtest_summarize = $(bin)MyPromptEfficiencyAlg_qmtest_summarizesetup.make
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
cmt_local_tagfile_qmtest_summarize = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_qmtest_summarize = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_qmtest_summarize_makefile = /tmp/CMT_qmtest_summarize$(cmt_lock_pid).make
else
#cmt_local_tagfile_qmtest_summarize = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_qmtest_summarize = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_qmtest_summarize = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_TestPackage = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_TestPackage.make$(cmt_lock_pid)
cmt_final_setup_TestPackage = /tmp/CMT_MyPromptEfficiencyAlg_TestPackagesetup.make
cmt_local_TestPackage_makefile = /tmp/CMT_TestPackage$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestPackage = $(MyPromptEfficiencyAlg_tag)_TestPackage.make
cmt_local_tagfile_TestPackage = $(bin)$(MyPromptEfficiencyAlg_tag)_TestPackage.make
cmt_final_setup_TestPackage = $(bin)MyPromptEfficiencyAlg_TestPackagesetup.make
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
cmt_local_tagfile_TestPackage = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_TestPackage = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_TestPackage_makefile = /tmp/CMT_TestPackage$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestPackage = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_TestPackage = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_TestPackage = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_TestProject = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_TestProject.make$(cmt_lock_pid)
cmt_final_setup_TestProject = /tmp/CMT_MyPromptEfficiencyAlg_TestProjectsetup.make
cmt_local_TestProject_makefile = /tmp/CMT_TestProject$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestProject = $(MyPromptEfficiencyAlg_tag)_TestProject.make
cmt_local_tagfile_TestProject = $(bin)$(MyPromptEfficiencyAlg_tag)_TestProject.make
cmt_final_setup_TestProject = $(bin)MyPromptEfficiencyAlg_TestProjectsetup.make
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
cmt_local_tagfile_TestProject = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_TestProject = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_TestProject_makefile = /tmp/CMT_TestProject$(cmt_lock_pid).make
else
#cmt_local_tagfile_TestProject = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_TestProject = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_TestProject = $(bin)MyPromptEfficiencyAlgsetup.make
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
cmt_local_tagfile_new_rootsys = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_new_rootsys.make$(cmt_lock_pid)
cmt_final_setup_new_rootsys = /tmp/CMT_MyPromptEfficiencyAlg_new_rootsyssetup.make
cmt_local_new_rootsys_makefile = /tmp/CMT_new_rootsys$(cmt_lock_pid).make
else
#cmt_local_tagfile_new_rootsys = $(MyPromptEfficiencyAlg_tag)_new_rootsys.make
cmt_local_tagfile_new_rootsys = $(bin)$(MyPromptEfficiencyAlg_tag)_new_rootsys.make
cmt_final_setup_new_rootsys = $(bin)MyPromptEfficiencyAlg_new_rootsyssetup.make
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
cmt_local_tagfile_new_rootsys = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
cmt_final_setup_new_rootsys = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_new_rootsys_makefile = /tmp/CMT_new_rootsys$(cmt_lock_pid).make
else
#cmt_local_tagfile_new_rootsys = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_new_rootsys = $(bin)$(MyPromptEfficiencyAlg_tag).make
cmt_final_setup_new_rootsys = $(bin)MyPromptEfficiencyAlgsetup.make
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
