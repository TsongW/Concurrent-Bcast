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
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_FILE_GET_INFO = PMPI_FILE_GET_INFO
#pragma weak mpi_file_get_info__ = PMPI_FILE_GET_INFO
#pragma weak mpi_file_get_info_ = PMPI_FILE_GET_INFO
#pragma weak mpi_file_get_info = PMPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_FILE_GET_INFO = pmpi_file_get_info__
#pragma weak mpi_file_get_info__ = pmpi_file_get_info__
#pragma weak mpi_file_get_info_ = pmpi_file_get_info__
#pragma weak mpi_file_get_info = pmpi_file_get_info__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_FILE_GET_INFO = pmpi_file_get_info_
#pragma weak mpi_file_get_info__ = pmpi_file_get_info_
#pragma weak mpi_file_get_info_ = pmpi_file_get_info_
#pragma weak mpi_file_get_info = pmpi_file_get_info_
#else
#pragma weak MPI_FILE_GET_INFO = pmpi_file_get_info
#pragma weak mpi_file_get_info__ = pmpi_file_get_info
#pragma weak mpi_file_get_info_ = pmpi_file_get_info
#pragma weak mpi_file_get_info = pmpi_file_get_info
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_FILE_GET_INFO = PMPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_file_get_info__ = pmpi_file_get_info__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_file_get_info = pmpi_file_get_info
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_file_get_info_ = pmpi_file_get_info_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_FILE_GET_INFO  MPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_file_get_info__  mpi_file_get_info__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_file_get_info  mpi_file_get_info
#else
#pragma _HP_SECONDARY_DEF pmpi_file_get_info_  mpi_file_get_info_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_FILE_GET_INFO as PMPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_file_get_info__ as pmpi_file_get_info__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_file_get_info as pmpi_file_get_info
#else
#pragma _CRI duplicate mpi_file_get_info_ as pmpi_file_get_info_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_file_get_info__ = MPI_FILE_GET_INFO
#pragma weak mpi_file_get_info_ = MPI_FILE_GET_INFO
#pragma weak mpi_file_get_info = MPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_FILE_GET_INFO = mpi_file_get_info__
#pragma weak mpi_file_get_info_ = mpi_file_get_info__
#pragma weak mpi_file_get_info = mpi_file_get_info__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_FILE_GET_INFO = mpi_file_get_info_
#pragma weak mpi_file_get_info__ = mpi_file_get_info_
#pragma weak mpi_file_get_info = mpi_file_get_info_
#else
#pragma weak MPI_FILE_GET_INFO = mpi_file_get_info
#pragma weak mpi_file_get_info__ = mpi_file_get_info
#pragma weak mpi_file_get_info_ = mpi_file_get_info
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_FILE_GET_INFO")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL mpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_file_get_info__ = PMPI_FILE_GET_INFO
#pragma weak pmpi_file_get_info_ = PMPI_FILE_GET_INFO
#pragma weak pmpi_file_get_info = PMPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_FILE_GET_INFO = pmpi_file_get_info__
#pragma weak pmpi_file_get_info_ = pmpi_file_get_info__
#pragma weak pmpi_file_get_info = pmpi_file_get_info__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_FILE_GET_INFO = pmpi_file_get_info_
#pragma weak pmpi_file_get_info__ = pmpi_file_get_info_
#pragma weak pmpi_file_get_info = pmpi_file_get_info_
#else
#pragma weak PMPI_FILE_GET_INFO = pmpi_file_get_info
#pragma weak pmpi_file_get_info__ = pmpi_file_get_info
#pragma weak pmpi_file_get_info_ = pmpi_file_get_info
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_FILE_GET_INFO")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_FILE_GET_INFO( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_file_get_info_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_file_get_info")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_file_get_info_ PMPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_file_get_info_ pmpi_file_get_info__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_file_get_info_ pmpi_file_get_info
#else
#define mpi_file_get_info_ pmpi_file_get_info_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_File_get_info
#define MPI_File_get_info PMPI_File_get_info 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_file_get_info_ MPI_FILE_GET_INFO
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_file_get_info_ mpi_file_get_info__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_file_get_info_ mpi_file_get_info
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_file_get_info_ ( MPI_Fint *v1, MPI_Fint *v2, MPI_Fint *ierr ){
#ifdef MPI_MODE_RDONLY
    *ierr = MPI_File_get_info( MPI_File_f2c(*v1), (MPI_Info *)(v2) );
#else
*ierr = MPI_ERR_INTERN;
#endif
}
