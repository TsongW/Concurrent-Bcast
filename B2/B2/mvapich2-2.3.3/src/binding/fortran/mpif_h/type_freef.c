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
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_TYPE_FREE = PMPI_TYPE_FREE
#pragma weak mpi_type_free__ = PMPI_TYPE_FREE
#pragma weak mpi_type_free_ = PMPI_TYPE_FREE
#pragma weak mpi_type_free = PMPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_TYPE_FREE = pmpi_type_free__
#pragma weak mpi_type_free__ = pmpi_type_free__
#pragma weak mpi_type_free_ = pmpi_type_free__
#pragma weak mpi_type_free = pmpi_type_free__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_TYPE_FREE = pmpi_type_free_
#pragma weak mpi_type_free__ = pmpi_type_free_
#pragma weak mpi_type_free_ = pmpi_type_free_
#pragma weak mpi_type_free = pmpi_type_free_
#else
#pragma weak MPI_TYPE_FREE = pmpi_type_free
#pragma weak mpi_type_free__ = pmpi_type_free
#pragma weak mpi_type_free_ = pmpi_type_free
#pragma weak mpi_type_free = pmpi_type_free
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * );

#pragma weak MPI_TYPE_FREE = PMPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * );

#pragma weak mpi_type_free__ = pmpi_type_free__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * );

#pragma weak mpi_type_free = pmpi_type_free
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * );

#pragma weak mpi_type_free_ = pmpi_type_free_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_TYPE_FREE  MPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_type_free__  mpi_type_free__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_type_free  mpi_type_free
#else
#pragma _HP_SECONDARY_DEF pmpi_type_free_  mpi_type_free_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_TYPE_FREE as PMPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_type_free__ as pmpi_type_free__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_type_free as pmpi_type_free
#else
#pragma _CRI duplicate mpi_type_free_ as pmpi_type_free_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_type_free__ = MPI_TYPE_FREE
#pragma weak mpi_type_free_ = MPI_TYPE_FREE
#pragma weak mpi_type_free = MPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_TYPE_FREE = mpi_type_free__
#pragma weak mpi_type_free_ = mpi_type_free__
#pragma weak mpi_type_free = mpi_type_free__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_TYPE_FREE = mpi_type_free_
#pragma weak mpi_type_free__ = mpi_type_free_
#pragma weak mpi_type_free = mpi_type_free_
#else
#pragma weak MPI_TYPE_FREE = mpi_type_free
#pragma weak mpi_type_free__ = mpi_type_free
#pragma weak mpi_type_free_ = mpi_type_free
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_TYPE_FREE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL mpi_type_free( MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_TYPE_FREE( MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free__( MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free_( MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free( MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_type_free__ = PMPI_TYPE_FREE
#pragma weak pmpi_type_free_ = PMPI_TYPE_FREE
#pragma weak pmpi_type_free = PMPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_TYPE_FREE = pmpi_type_free__
#pragma weak pmpi_type_free_ = pmpi_type_free__
#pragma weak pmpi_type_free = pmpi_type_free__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_TYPE_FREE = pmpi_type_free_
#pragma weak pmpi_type_free__ = pmpi_type_free_
#pragma weak pmpi_type_free = pmpi_type_free_
#else
#pragma weak PMPI_TYPE_FREE = pmpi_type_free
#pragma weak pmpi_type_free__ = pmpi_type_free
#pragma weak pmpi_type_free_ = pmpi_type_free
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_TYPE_FREE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_TYPE_FREE( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free__( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_type_free_( MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_type_free")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_type_free_ PMPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_type_free_ pmpi_type_free__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_type_free_ pmpi_type_free
#else
#define mpi_type_free_ pmpi_type_free_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Type_free
#define MPI_Type_free PMPI_Type_free 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_type_free_ MPI_TYPE_FREE
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_type_free_ mpi_type_free__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_type_free_ mpi_type_free
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_type_free_ ( MPI_Fint *v1, MPI_Fint *ierr ){
    *ierr = MPI_Type_free( (MPI_Datatype *)(v1) );
}
