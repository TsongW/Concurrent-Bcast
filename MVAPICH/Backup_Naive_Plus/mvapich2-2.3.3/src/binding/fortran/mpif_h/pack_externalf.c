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
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_PACK_EXTERNAL = PMPI_PACK_EXTERNAL
#pragma weak mpi_pack_external__ = PMPI_PACK_EXTERNAL
#pragma weak mpi_pack_external_ = PMPI_PACK_EXTERNAL
#pragma weak mpi_pack_external = PMPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_PACK_EXTERNAL = pmpi_pack_external__
#pragma weak mpi_pack_external__ = pmpi_pack_external__
#pragma weak mpi_pack_external_ = pmpi_pack_external__
#pragma weak mpi_pack_external = pmpi_pack_external__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_PACK_EXTERNAL = pmpi_pack_external_
#pragma weak mpi_pack_external__ = pmpi_pack_external_
#pragma weak mpi_pack_external_ = pmpi_pack_external_
#pragma weak mpi_pack_external = pmpi_pack_external_
#else
#pragma weak MPI_PACK_EXTERNAL = pmpi_pack_external
#pragma weak mpi_pack_external__ = pmpi_pack_external
#pragma weak mpi_pack_external_ = pmpi_pack_external
#pragma weak mpi_pack_external = pmpi_pack_external
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak MPI_PACK_EXTERNAL = PMPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_pack_external__ = pmpi_pack_external__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_pack_external = pmpi_pack_external
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#pragma weak mpi_pack_external_ = pmpi_pack_external_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_PACK_EXTERNAL  MPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_pack_external__  mpi_pack_external__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_pack_external  mpi_pack_external
#else
#pragma _HP_SECONDARY_DEF pmpi_pack_external_  mpi_pack_external_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_PACK_EXTERNAL as PMPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_pack_external__ as pmpi_pack_external__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_pack_external as pmpi_pack_external
#else
#pragma _CRI duplicate mpi_pack_external_ as pmpi_pack_external_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_pack_external__ = MPI_PACK_EXTERNAL
#pragma weak mpi_pack_external_ = MPI_PACK_EXTERNAL
#pragma weak mpi_pack_external = MPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_PACK_EXTERNAL = mpi_pack_external__
#pragma weak mpi_pack_external_ = mpi_pack_external__
#pragma weak mpi_pack_external = mpi_pack_external__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_PACK_EXTERNAL = mpi_pack_external_
#pragma weak mpi_pack_external__ = mpi_pack_external_
#pragma weak mpi_pack_external = mpi_pack_external_
#else
#pragma weak MPI_PACK_EXTERNAL = mpi_pack_external
#pragma weak mpi_pack_external__ = mpi_pack_external
#pragma weak mpi_pack_external_ = mpi_pack_external
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("MPI_PACK_EXTERNAL")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("mpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL mpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_pack_external__ = PMPI_PACK_EXTERNAL
#pragma weak pmpi_pack_external_ = PMPI_PACK_EXTERNAL
#pragma weak pmpi_pack_external = PMPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_PACK_EXTERNAL = pmpi_pack_external__
#pragma weak pmpi_pack_external_ = pmpi_pack_external__
#pragma weak pmpi_pack_external = pmpi_pack_external__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_PACK_EXTERNAL = pmpi_pack_external_
#pragma weak pmpi_pack_external__ = pmpi_pack_external_
#pragma weak pmpi_pack_external = pmpi_pack_external_
#else
#pragma weak PMPI_PACK_EXTERNAL = pmpi_pack_external
#pragma weak pmpi_pack_external__ = pmpi_pack_external
#pragma weak pmpi_pack_external_ = pmpi_pack_external
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("PMPI_PACK_EXTERNAL")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_PACK_EXTERNAL( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external__( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_pack_external_( char * FORT_MIXED_LEN_DECL, void*, MPI_Fint *, MPI_Fint *, void*, MPI_Aint *, MPI_Aint *, MPI_Fint * FORT_END_LEN_DECL ) __attribute__((weak,alias("pmpi_pack_external")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_pack_external_ PMPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_pack_external_ pmpi_pack_external__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_pack_external_ pmpi_pack_external
#else
#define mpi_pack_external_ pmpi_pack_external_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Pack_external
#define MPI_Pack_external PMPI_Pack_external 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_pack_external_ MPI_PACK_EXTERNAL
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_pack_external_ mpi_pack_external__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_pack_external_ mpi_pack_external
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_pack_external_ ( char *v1 FORT_MIXED_LEN(d1), void*v2, MPI_Fint *v3, MPI_Fint *v4, void*v5, MPI_Aint * v6, MPI_Aint * v7, MPI_Fint *ierr FORT_END_LEN(d1) ){
    char *p1;

    {char *p = v1 + d1 - 1;
     int  li;
        while (*p == ' ' && p > v1) p--;
        p++;
        p1 = (char *)MPIU_Malloc( p-v1 + 1 );
        for (li=0; li<(p-v1); li++) { p1[li] = v1[li]; }
        p1[li] = 0; 
    }
    if (v2 == MPIR_F_MPI_BOTTOM) v2 = MPI_BOTTOM;
    if (v5 == MPIR_F_MPI_BOTTOM) v5 = MPI_BOTTOM;
    *ierr = MPI_Pack_external( p1, v2, (int)*v3, (MPI_Datatype)(*v4), v5, *v6, v7 );
    MPIU_Free( p1 );
}