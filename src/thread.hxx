/*
 * thread.hxx
 *
 *  Created on: Aug 28, 2015
 *      Author: Kristofer
 */

#ifndef SRC_THREAD_HXX_
#define SRC_THREAD_HXX_

#if HAVE_MEGANZ_MINGW_STD_THREADS
#define NDEBUG 1
// https://github.com/meganz/mingw-std-threads/pull/1
#ifndef EOWNERDEAD
#define EOWNERDEAD -1
#endif
#ifndef EPROTO
#define EPROTO -1
#endif
#include <mingw.thread.h>
#endif /* HAVE_MEGANZ_MINGW_STD_THREADS */
#include <mutex>
#ifdef HAVE_MEGANZ_MINGW_STD_THREADS
#include <mingw.mutex.h>
#include <mingw.condition_variable.h>
#endif /* HAVE_MEGANZ_MINGW_STD_THREADS */
#include <atomic>

#endif /* SRC_THREAD_HXX_ */
