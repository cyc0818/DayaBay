if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/.ihep.ac.cn/soft/dayabay/NuWa-slc6/NuWa-3.x.x-opt/external/CMT/v1r20p20080222; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=ExamTruth -version=v1 -path=/dybfs2/users/yuchincheng/workdir/IBD/code $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

