#ifndef _MONGOOSE_CPP_COMMON_H
#define _MONGOOSE_CPP_COMMON_H

#ifdef _MSC_VER
# pragma once
# pragma warning(disable:4251)  // Disable VC warning about dll linkage required (for private members?)
# pragma warning(disable:4275)  // Disable warning about non dll-interface base class.
#endif

#if defined(_MSC_VER) && defined(MONGOOSE_CPP_USE_DLL)
  #ifdef MONGOOSE_CPP_BUILD_DLL
    #define MONGOOSE_CPP_EXPORT __declspec(dllexport)
  #else
    #define MONGOOSE_CPP_EXPORT __declspec(dllimport)
  #endif
#else
  #define MONGOOSE_CPP_EXPORT
#endif

#endif
