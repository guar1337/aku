// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Eloss
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "AELC.h"
#include "ELC.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_AELC(void *p);
   static void deleteArray_AELC(void *p);
   static void destruct_AELC(void *p);
   static void streamer_AELC(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AELC*)
   {
      ::AELC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AELC >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AELC", ::AELC::Class_Version(), "AELC.h", 5,
                  typeid(::AELC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AELC::Dictionary, isa_proxy, 16,
                  sizeof(::AELC) );
      instance.SetDelete(&delete_AELC);
      instance.SetDeleteArray(&deleteArray_AELC);
      instance.SetDestructor(&destruct_AELC);
      instance.SetStreamerFunc(&streamer_AELC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AELC*)
   {
      return GenerateInitInstanceLocal((::AELC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AELC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *ELC_Dictionary();
   static void ELC_TClassManip(TClass*);
   static void *new_ELC(void *p = 0);
   static void *newArray_ELC(Long_t size, void *p);
   static void delete_ELC(void *p);
   static void deleteArray_ELC(void *p);
   static void destruct_ELC(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ELC*)
   {
      ::ELC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ELC));
      static ::ROOT::TGenericClassInfo 
         instance("ELC", "ELC.h", 13,
                  typeid(::ELC), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ELC_Dictionary, isa_proxy, 0,
                  sizeof(::ELC) );
      instance.SetNew(&new_ELC);
      instance.SetNewArray(&newArray_ELC);
      instance.SetDelete(&delete_ELC);
      instance.SetDeleteArray(&deleteArray_ELC);
      instance.SetDestructor(&destruct_ELC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ELC*)
   {
      return GenerateInitInstanceLocal((::ELC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ELC*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ELC_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ELC*)0x0)->GetClass();
      ELC_TClassManip(theClass);
   return theClass;
   }

   static void ELC_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr AELC::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AELC::Class_Name()
{
   return "AELC";
}

//______________________________________________________________________________
const char *AELC::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AELC*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AELC::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AELC*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AELC::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AELC*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AELC::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AELC*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void AELC::Streamer(TBuffer &R__b)
{
   // Stream an object of class AELC.

   ::Error("AELC::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_AELC(void *p) {
      delete ((::AELC*)p);
   }
   static void deleteArray_AELC(void *p) {
      delete [] ((::AELC*)p);
   }
   static void destruct_AELC(void *p) {
      typedef ::AELC current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_AELC(TBuffer &buf, void *obj) {
      ((::AELC*)obj)->::AELC::Streamer(buf);
   }
} // end of namespace ROOT for class ::AELC

namespace ROOT {
   // Wrappers around operator new
   static void *new_ELC(void *p) {
      return  p ? new(p) ::ELC : new ::ELC;
   }
   static void *newArray_ELC(Long_t nElements, void *p) {
      return p ? new(p) ::ELC[nElements] : new ::ELC[nElements];
   }
   // Wrapper around operator delete
   static void delete_ELC(void *p) {
      delete ((::ELC*)p);
   }
   static void deleteArray_ELC(void *p) {
      delete [] ((::ELC*)p);
   }
   static void destruct_ELC(void *p) {
      typedef ::ELC current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ELC

namespace {
  void TriggerDictionaryInitialization_Eloss_Impl() {
    static const char* headers[] = {
"AELC.h",
"ELC.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/include",
"/usr/local/include",
"/home/zalewski/aku/wrk/ELC/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Eloss dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$AELC.h")))  AELC;
class __attribute__((annotate("$clingAutoload$ELC.h")))  ELC;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Eloss dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "AELC.h"
#include "ELC.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"AELC", payloadCode, "@",
"ELC", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Eloss",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Eloss_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Eloss_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Eloss() {
  TriggerDictionaryInitialization_Eloss_Impl();
}
