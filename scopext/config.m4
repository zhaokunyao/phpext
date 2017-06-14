dnl $Id$
dnl config.m4 for extension scopext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(scopext, for scopext support,
dnl Make sure that the comment is aligned:
dnl [  --with-scopext             Include scopext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(scopext, whether to enable scopext support,
[  --enable-scopext           Enable scopext support])

if test "$PHP_SCOPEXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-scopext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/scopext.h"  # you most likely want to change this
  dnl if test -r $PHP_SCOPEXT/$SEARCH_FOR; then # path given as parameter
  dnl   SCOPEXT_DIR=$PHP_SCOPEXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for scopext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SCOPEXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SCOPEXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the scopext distribution])
  dnl fi

  dnl # --with-scopext -> add include path
  dnl PHP_ADD_INCLUDE($SCOPEXT_DIR/include)

  dnl # --with-scopext -> check for lib and symbol presence
  dnl LIBNAME=scopext # you may want to change this
  dnl LIBSYMBOL=scopext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SCOPEXT_DIR/lib, SCOPEXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SCOPEXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong scopext lib version or lib not found])
  dnl ],[
  dnl   -L$SCOPEXT_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(SCOPEXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(scopext, scopext.c, $ext_shared)
fi
