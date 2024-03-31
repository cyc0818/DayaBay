#-- start of make_header -----------------

#====================================
#  Document MyPromptEfficiencyAlgRootMap
#
#   Generated Wed Jul 20 16:50:18 2022  by yuchincheng
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_MyPromptEfficiencyAlgRootMap_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_MyPromptEfficiencyAlgRootMap_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_MyPromptEfficiencyAlgRootMap

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(bin)$(MyPromptEfficiencyAlg_tag)_MyPromptEfficiencyAlgRootMap.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

MyPromptEfficiencyAlg_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = /tmp/CMT_$(MyPromptEfficiencyAlg_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(MyPromptEfficiencyAlg_tag).make
cmt_local_tagfile_MyPromptEfficiencyAlgRootMap = $(bin)$(MyPromptEfficiencyAlg_tag).make
endif

endif

-include $(cmt_local_tagfile_MyPromptEfficiencyAlgRootMap)

ifdef cmt_MyPromptEfficiencyAlgRootMap_has_target_tag

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgRootMap = /tmp/CMT_MyPromptEfficiencyAlg_MyPromptEfficiencyAlgRootMapsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgRootMap$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgRootMap = $(bin)MyPromptEfficiencyAlg_MyPromptEfficiencyAlgRootMapsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = $(bin)MyPromptEfficiencyAlgRootMap.make
endif

else

ifdef READONLY
cmt_final_setup_MyPromptEfficiencyAlgRootMap = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = /tmp/CMT_MyPromptEfficiencyAlgRootMap$(cmt_lock_pid).make
else
cmt_final_setup_MyPromptEfficiencyAlgRootMap = $(bin)MyPromptEfficiencyAlgsetup.make
cmt_local_MyPromptEfficiencyAlgRootMap_makefile = $(bin)MyPromptEfficiencyAlgRootMap.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_MyPromptEfficiencyAlgsetup.make
else
cmt_final_setup = $(bin)MyPromptEfficiencyAlgsetup.make
endif

MyPromptEfficiencyAlgRootMap ::


ifdef READONLY
MyPromptEfficiencyAlgRootMap ::
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
	$(echo) 'MyPromptEfficiencyAlgRootMap'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = MyPromptEfficiencyAlgRootMap/
MyPromptEfficiencyAlgRootMap::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

##
rootmapfile = MyPromptEfficiencyAlg.rootmap
ROOTMAP_DIR = ../$(tag)
fulllibname = libMyPromptEfficiencyAlg.$(shlibsuffix)

MyPromptEfficiencyAlgRootMap :: ${ROOTMAP_DIR}/$(rootmapfile)
	@:

${ROOTMAP_DIR}/$(rootmapfile) :: $(bin)$(fulllibname)
	@echo 'Generating rootmap file for $(fulllibname)'
	cd ../$(tag);$(genmap_cmd) -i $(fulllibname) -o ${ROOTMAP_DIR}/$(rootmapfile) $(MyPromptEfficiencyAlgRootMap_genmapflags)

install :: MyPromptEfficiencyAlgRootMapinstall
MyPromptEfficiencyAlgRootMapinstall :: MyPromptEfficiencyAlgRootMap

uninstall :: MyPromptEfficiencyAlgRootMapuninstall
MyPromptEfficiencyAlgRootMapuninstall :: MyPromptEfficiencyAlgRootMapclean

MyPromptEfficiencyAlgRootMapclean ::
	@echo 'Deleting $(rootmapfile)'
	@rm -f ${ROOTMAP_DIR}/$(rootmapfile)

#-- start of cleanup_header --------------

clean :: MyPromptEfficiencyAlgRootMapclean
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

MyPromptEfficiencyAlgRootMapclean ::
#-- end of cleanup_header ---------------
