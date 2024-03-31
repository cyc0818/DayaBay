# echo "Setting ExamTruth v1 in /dybfs2/users/yuchincheng/workdir/IBD/code"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/.ihep.ac.cn/soft/dayabay/NuWa-slc6/NuWa-3.x.x-opt/external/CMT/v1r20p20080222; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=ExamTruth -version=v1 -path=/dybfs2/users/yuchincheng/workdir/IBD/code  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

