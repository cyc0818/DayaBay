if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/.ihep.ac.cn/soft/dayabay/NuWa-slc6/NuWa-3.x.x-opt/external/CMT/v1r20p20080222
endif
source ${CMTROOT}/mgr/setup.csh
set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=MyPromptEfficiencyAlg -version=v0 -path=/dybfs2/users/yuchincheng/workdir/IBD/code $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

