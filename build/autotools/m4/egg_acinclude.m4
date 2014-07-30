dnl aclocal.m4
dnl   macros autoconf uses when building configure from configure.in
dnl
dnl $Id: acinclude.m4 2911 2006-07-11 00:32:12Z bryan $
dnl

dnl EGG_CHECK_CCPIPE()
dnl
dnl This function checks whether or not the compiler supports the `-pipe' flag,
dnl which speeds up the compilation.
dnl
AC_DEFUN([EGG_CHECK_CCPIPE],
[
  if test -n "$GXX" && test -z "$no_pipe"; then
    AC_CACHE_CHECK([whether the compiler understands -pipe], egg_cv_var_ccpipe, [
        ac_old_CXX="$CXX"
        CXX="$CXX -pipe"
        AC_COMPILE_IFELSE([AC_LANG_SOURCE([
          int main ()
          {
            return(0);
          }
        ])], [
          egg_cv_var_ccpipe="yes"
        ], [
          egg_cv_var_ccpipe="no"
        ])
        CXX="$ac_old_CXX"
    ])

    if test "$egg_cv_var_ccpipe" = "yes"; then
      CXX="$CXX -pipe"
    fi
  fi
])

dnl @synopsis CXX_FLAGS_CHECK [var] [compiler flags] [cache name] [required]
dnl @summary check whether compiler supports given C++ flags or not
AC_DEFUN([CXX_FLAG_CHECK],
[
  AC_CACHE_CHECK([whether the compiler understands $2], egg_cv_prog_cc_$3, [
    AC_LANG_PUSH([C++])
    ac_saved_flags="$CXXFLAGS"
    CXXFLAGS="-Werror $2"
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
      [egg_cv_prog_cc_$3="yes"],
      [egg_cv_prog_cc_$3="no"],
    )
    CXXFLAGS="$ac_saved_flags"
    AC_LANG_POP([C++])
  ])

  if [[ "$egg_cv_prog_cc_$3" = "yes" ]]; then
    $1="$$1 $2"
  elif [[ -n "$4" ]]; then
      cat << 'EOF' >&2
configure: error:

  Your OS or C++ compiler does not support $2.
  This compile flag is required.

EOF
    exit 1
  fi
])

dnl  EGG_CHECK_CCSTATIC()
dnl
dnl  Checks whether the compiler supports the `-static' flag.
AC_DEFUN([EGG_CHECK_CCSTATIC],
[
if test -z "$no_static"
then
  if test -n "$GXX"
  then
    AC_CACHE_CHECK(whether the compiler understands -static, egg_cv_var_ccstatic, [dnl
      ac_old_CXX="$CXX"
      CXX="$CXX -static"
      AC_TRY_COMPILE(,, egg_cv_var_ccstatic="yes", egg_cv_var_ccstatic="no")
      CXX="$ac_old_CXX"
      
    ])
    if test "$egg_cv_var_ccstatic" = "yes"
    then
      CXXDEBUG="$CXX"
#      CXX="$CXX -static"
    else
      cat << 'EOF' >&2
configure: error:

  Your C compiler does not support -static.
  This compile flag is required.

EOF
  exit 1
    fi
  fi
fi
])