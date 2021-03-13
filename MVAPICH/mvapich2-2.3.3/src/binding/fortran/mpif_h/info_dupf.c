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
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_INFO_DUP = PMPI_INFO_DUP
#pragma weak mpi_info_dup__ = PMPI_INFO_DUP
#pragma weak mpi_info_dup_ = PMPI_INFO_DUP
#pragma weak mpi_info_dup = PMPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_INFO_DUP = pmpi_info_dup__
#pragma weak mpi_info_dup__ = pmpi_info_dup__
#pragma weak mpi_info_dup_ = pmpi_info_dup__
#pragma weak mpi_info_dup = pmpi_info_dup__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_INFO_DUP = pmpi_info_dup_
#pragma weak mpi_info_dup__ = pmpi_info_dup_
#pragma weak mpi_info_dup_ = pmpi_info_dup_
#pragma weak mpi_info_dup = pmpi_info_dup_
#else
#pragma weak MPI_INFO_DUP = pmpi_info_dup
#pragma weak mpi_info_dup__ = pmpi_info_dup
#pragma weak mpi_info_dup_ = pmpi_info_dup
#pragma weak mpi_info_dup = pmpi_info_dup
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_INFO_DUP = PMPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_info_dup__ = pmpi_info_dup__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_info_dup = pmpi_info_dup
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_info_dup_ = pmpi_info_dup_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_INFO_DUP  MPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_info_dup__  mpi_info_dup__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_info_dup  mpi_info_dup
#else
#pragma _HP_SECONDARY_DEF pmpi_info_dup_  mpi_info_dup_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_INFO_DUP as PMPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_info_dup__ as pmpi_info_dup__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_info_dup as pmpi_info_dup
#else
#pragma _CRI duplicate mpi_info_dup_ as pmpi_info_dup_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_info_dup__ = MPI_INFO_DUP
#pragma weak mpi_info_dup_ = MPI_INFO_DUP
#pragma weak mpi_info_dup = MPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_INFO_DUP = mpi_info_dup__
#pragma weak mpi_info_dup_ = mpi_info_dup__
#pragma weak mpi_info_dup = mpi_info_dup__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_INFO_DUP = mpi_info_dup_
#pragma weak mpi_info_dup__ = mpi_info_dup_
#pragma weak mpi_info_dup = mpi_info_dup_
#else
#pragma weak MPI_INFO_DUP = mpi_info_dup
#pragma weak mpi_info_dup__ = mpi_info_dup
#pragma weak mpi_info_dup_ = mpi_info_dup
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_INFO_DUP")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL mpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_info_dup__ = PMPI_INFO_DUP
#pragma weak pmpi_info_dup_ = PMPI_INFO_DUP
#pragma weak pmpi_info_dup = PMPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_INFO_DUP = pmpi_info_dup__
#pragma weak pmpi_info_dup_ = pmpi_info_dup__
#pragma weak pmpi_info_dup = pmpi_info_dup__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_INFO_DUP = pmpi_info_dup_
#pragma weak pmpi_info_dup__ = pmpi_info_dup_
#pragma weak pmpi_info_dup = pmpi_info_dup_
#else
#pragma weak PMPI_INFO_DUP = pmpi_info_dup
#pragma weak pmpi_info_dup__ = pmpi_info_dup
#pragma weak pmpi_info_dup_ = pmpi_info_dup
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_INFO_DUP")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_INFO_DUP( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_info_dup_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_info_dup")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_info_dup_ PMPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_info_dup_ pmpi_info_dup__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_info_dup_ pmpi_info_dup
#else
#define mpi_info_dup_ pmpi_info_dup_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Info_dup
#define MPI_Info_dup PMPI_Info_dup 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_info_dup_ MPI_INFO_DUP
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_info_dup_ mpi_info_dup__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_info_dup_ mpi_info_dup
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_info_dup_ ( MPI_Fint *v1, MPI_Fint *v2, MPI_Fint *ierr ){
    *ierr = MPI_Info_dup( (MPI_Info)(*v1), (MPI_Info *)(v2) );
}
