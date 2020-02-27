/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface 
 * DO NOT EDIT
 */
#include "mpi_fortimpl.h"


/* Begin MPI profiling block */
#if defined(USE_WEAK_SYMBOLS) && !defined(USE_ONLY_MPI_NAMES) 
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_WIN_GET_ATTR = PMPI_WIN_GET_ATTR
#pragma weak mpi_win_get_attr__ = PMPI_WIN_GET_ATTR
#pragma weak mpi_win_get_attr_ = PMPI_WIN_GET_ATTR
#pragma weak mpi_win_get_attr = PMPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_GET_ATTR = pmpi_win_get_attr__
#pragma weak mpi_win_get_attr__ = pmpi_win_get_attr__
#pragma weak mpi_win_get_attr_ = pmpi_win_get_attr__
#pragma weak mpi_win_get_attr = pmpi_win_get_attr__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_GET_ATTR = pmpi_win_get_attr_
#pragma weak mpi_win_get_attr__ = pmpi_win_get_attr_
#pragma weak mpi_win_get_attr_ = pmpi_win_get_attr_
#pragma weak mpi_win_get_attr = pmpi_win_get_attr_
#else
#pragma weak MPI_WIN_GET_ATTR = pmpi_win_get_attr
#pragma weak mpi_win_get_attr__ = pmpi_win_get_attr
#pragma weak mpi_win_get_attr_ = pmpi_win_get_attr
#pragma weak mpi_win_get_attr = pmpi_win_get_attr
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_WIN_GET_ATTR = PMPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_get_attr__ = pmpi_win_get_attr__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_get_attr = pmpi_win_get_attr
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_get_attr_ = pmpi_win_get_attr_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_WIN_GET_ATTR  MPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_get_attr__  mpi_win_get_attr__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_get_attr  mpi_win_get_attr
#else
#pragma _HP_SECONDARY_DEF pmpi_win_get_attr_  mpi_win_get_attr_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_WIN_GET_ATTR as PMPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_win_get_attr__ as pmpi_win_get_attr__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_win_get_attr as pmpi_win_get_attr
#else
#pragma _CRI duplicate mpi_win_get_attr_ as pmpi_win_get_attr_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_win_get_attr__ = MPI_WIN_GET_ATTR
#pragma weak mpi_win_get_attr_ = MPI_WIN_GET_ATTR
#pragma weak mpi_win_get_attr = MPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_GET_ATTR = mpi_win_get_attr__
#pragma weak mpi_win_get_attr_ = mpi_win_get_attr__
#pragma weak mpi_win_get_attr = mpi_win_get_attr__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_GET_ATTR = mpi_win_get_attr_
#pragma weak mpi_win_get_attr__ = mpi_win_get_attr_
#pragma weak mpi_win_get_attr = mpi_win_get_attr_
#else
#pragma weak MPI_WIN_GET_ATTR = mpi_win_get_attr
#pragma weak mpi_win_get_attr__ = mpi_win_get_attr
#pragma weak mpi_win_get_attr_ = mpi_win_get_attr
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_GET_ATTR")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_win_get_attr__ = PMPI_WIN_GET_ATTR
#pragma weak pmpi_win_get_attr_ = PMPI_WIN_GET_ATTR
#pragma weak pmpi_win_get_attr = PMPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_WIN_GET_ATTR = pmpi_win_get_attr__
#pragma weak pmpi_win_get_attr_ = pmpi_win_get_attr__
#pragma weak pmpi_win_get_attr = pmpi_win_get_attr__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_WIN_GET_ATTR = pmpi_win_get_attr_
#pragma weak pmpi_win_get_attr__ = pmpi_win_get_attr_
#pragma weak pmpi_win_get_attr = pmpi_win_get_attr_
#else
#pragma weak PMPI_WIN_GET_ATTR = pmpi_win_get_attr
#pragma weak pmpi_win_get_attr__ = pmpi_win_get_attr
#pragma weak pmpi_win_get_attr_ = pmpi_win_get_attr
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_GET_ATTR")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_GET_ATTR( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr__( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_get_attr_( MPI_Fint *, MPI_Fint *, void*, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_get_attr")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_win_get_attr_ PMPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_get_attr_ pmpi_win_get_attr__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_get_attr_ pmpi_win_get_attr
#else
#define mpi_win_get_attr_ pmpi_win_get_attr_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Win_get_attr
#define MPI_Win_get_attr PMPI_Win_get_attr 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_win_get_attr_ MPI_WIN_GET_ATTR
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_get_attr_ mpi_win_get_attr__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_get_attr_ mpi_win_get_attr
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_win_get_attr_ ( MPI_Fint *v1, MPI_Fint *v2, void*v3, MPI_Fint *v4, MPI_Fint *ierr ){
    void *attrv3;
    int l4;
    if (v3 == MPIR_F_MPI_BOTTOM) v3 = MPI_BOTTOM;
   *ierr = MPIR_WinGetAttr( (MPI_Win)*v1, (int)*v2, &attrv3, &l4, MPIR_ATTR_AINT );

    if ((int)*ierr || !l4) {
        *(MPI_Aint*)v3 = 0;
    }
    else {
        *(MPI_Aint*)v3 = (MPI_Aint)attrv3;
    }
    if (*ierr == MPI_SUCCESS) *v4 = MPIR_TO_FLOG(l4);
}
