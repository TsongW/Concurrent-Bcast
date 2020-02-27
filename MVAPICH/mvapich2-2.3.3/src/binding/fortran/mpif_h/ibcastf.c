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
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_IBCAST = PMPI_IBCAST
#pragma weak mpi_ibcast__ = PMPI_IBCAST
#pragma weak mpi_ibcast_ = PMPI_IBCAST
#pragma weak mpi_ibcast = PMPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_IBCAST = pmpi_ibcast__
#pragma weak mpi_ibcast__ = pmpi_ibcast__
#pragma weak mpi_ibcast_ = pmpi_ibcast__
#pragma weak mpi_ibcast = pmpi_ibcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_IBCAST = pmpi_ibcast_
#pragma weak mpi_ibcast__ = pmpi_ibcast_
#pragma weak mpi_ibcast_ = pmpi_ibcast_
#pragma weak mpi_ibcast = pmpi_ibcast_
#else
#pragma weak MPI_IBCAST = pmpi_ibcast
#pragma weak mpi_ibcast__ = pmpi_ibcast
#pragma weak mpi_ibcast_ = pmpi_ibcast
#pragma weak mpi_ibcast = pmpi_ibcast
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_IBCAST = PMPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_ibcast__ = pmpi_ibcast__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_ibcast = pmpi_ibcast
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_ibcast_ = pmpi_ibcast_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_IBCAST  MPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_ibcast__  mpi_ibcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_ibcast  mpi_ibcast
#else
#pragma _HP_SECONDARY_DEF pmpi_ibcast_  mpi_ibcast_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_IBCAST as PMPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_ibcast__ as pmpi_ibcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_ibcast as pmpi_ibcast
#else
#pragma _CRI duplicate mpi_ibcast_ as pmpi_ibcast_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_ibcast__ = MPI_IBCAST
#pragma weak mpi_ibcast_ = MPI_IBCAST
#pragma weak mpi_ibcast = MPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_IBCAST = mpi_ibcast__
#pragma weak mpi_ibcast_ = mpi_ibcast__
#pragma weak mpi_ibcast = mpi_ibcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_IBCAST = mpi_ibcast_
#pragma weak mpi_ibcast__ = mpi_ibcast_
#pragma weak mpi_ibcast = mpi_ibcast_
#else
#pragma weak MPI_IBCAST = mpi_ibcast
#pragma weak mpi_ibcast__ = mpi_ibcast
#pragma weak mpi_ibcast_ = mpi_ibcast
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_IBCAST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL mpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_ibcast__ = PMPI_IBCAST
#pragma weak pmpi_ibcast_ = PMPI_IBCAST
#pragma weak pmpi_ibcast = PMPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_IBCAST = pmpi_ibcast__
#pragma weak pmpi_ibcast_ = pmpi_ibcast__
#pragma weak pmpi_ibcast = pmpi_ibcast__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_IBCAST = pmpi_ibcast_
#pragma weak pmpi_ibcast__ = pmpi_ibcast_
#pragma weak pmpi_ibcast = pmpi_ibcast_
#else
#pragma weak PMPI_IBCAST = pmpi_ibcast
#pragma weak pmpi_ibcast__ = pmpi_ibcast
#pragma weak pmpi_ibcast_ = pmpi_ibcast
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_IBCAST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_IBCAST( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_ibcast_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_ibcast")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_ibcast_ PMPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_ibcast_ pmpi_ibcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_ibcast_ pmpi_ibcast
#else
#define mpi_ibcast_ pmpi_ibcast_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Ibcast
#define MPI_Ibcast PMPI_Ibcast 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_ibcast_ MPI_IBCAST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_ibcast_ mpi_ibcast__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_ibcast_ mpi_ibcast
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_ibcast_ ( void*v1, MPI_Fint *v2, MPI_Fint *v3, MPI_Fint *v4, MPI_Fint *v5, MPI_Fint *v6, MPI_Fint *ierr ){
    if (v1 == MPIR_F_MPI_BOTTOM) v1 = MPI_BOTTOM;
    *ierr = MPI_Ibcast( v1, (int)*v2, (MPI_Datatype)(*v3), (int)*v4, (MPI_Comm)(*v5), (MPI_Request *)(v6) );
}
