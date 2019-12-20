// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Mr_Blue_Sky
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
#include "TOOL.h"
#include "dE_E_angle.h"
#include "muchobojca.h"
#include "calibrate_tree.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TOOL(void *p = 0);
   static void *newArray_TOOL(Long_t size, void *p);
   static void delete_TOOL(void *p);
   static void deleteArray_TOOL(void *p);
   static void destruct_TOOL(void *p);
   static void streamer_TOOL(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TOOL*)
   {
      ::TOOL *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TOOL >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TOOL", ::TOOL::Class_Version(), "TOOL.h", 16,
                  typeid(::TOOL), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TOOL::Dictionary, isa_proxy, 16,
                  sizeof(::TOOL) );
      instance.SetNew(&new_TOOL);
      instance.SetNewArray(&newArray_TOOL);
      instance.SetDelete(&delete_TOOL);
      instance.SetDeleteArray(&deleteArray_TOOL);
      instance.SetDestructor(&destruct_TOOL);
      instance.SetStreamerFunc(&streamer_TOOL);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TOOL*)
   {
      return GenerateInitInstanceLocal((::TOOL*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TOOL*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_dE_E_angle(void *p = 0);
   static void *newArray_dE_E_angle(Long_t size, void *p);
   static void delete_dE_E_angle(void *p);
   static void deleteArray_dE_E_angle(void *p);
   static void destruct_dE_E_angle(void *p);
   static void streamer_dE_E_angle(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::dE_E_angle*)
   {
      ::dE_E_angle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::dE_E_angle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("dE_E_angle", ::dE_E_angle::Class_Version(), "dE_E_angle.h", 18,
                  typeid(::dE_E_angle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::dE_E_angle::Dictionary, isa_proxy, 16,
                  sizeof(::dE_E_angle) );
      instance.SetNew(&new_dE_E_angle);
      instance.SetNewArray(&newArray_dE_E_angle);
      instance.SetDelete(&delete_dE_E_angle);
      instance.SetDeleteArray(&deleteArray_dE_E_angle);
      instance.SetDestructor(&destruct_dE_E_angle);
      instance.SetStreamerFunc(&streamer_dE_E_angle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::dE_E_angle*)
   {
      return GenerateInitInstanceLocal((::dE_E_angle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::dE_E_angle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_muchobojca(void *p = 0);
   static void *newArray_muchobojca(Long_t size, void *p);
   static void delete_muchobojca(void *p);
   static void deleteArray_muchobojca(void *p);
   static void destruct_muchobojca(void *p);
   static void streamer_muchobojca(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::muchobojca*)
   {
      ::muchobojca *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::muchobojca >(0);
      static ::ROOT::TGenericClassInfo 
         instance("muchobojca", ::muchobojca::Class_Version(), "muchobojca.h", 20,
                  typeid(::muchobojca), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::muchobojca::Dictionary, isa_proxy, 16,
                  sizeof(::muchobojca) );
      instance.SetNew(&new_muchobojca);
      instance.SetNewArray(&newArray_muchobojca);
      instance.SetDelete(&delete_muchobojca);
      instance.SetDeleteArray(&deleteArray_muchobojca);
      instance.SetDestructor(&destruct_muchobojca);
      instance.SetStreamerFunc(&streamer_muchobojca);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::muchobojca*)
   {
      return GenerateInitInstanceLocal((::muchobojca*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::muchobojca*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_calibrate_tree(void *p = 0);
   static void *newArray_calibrate_tree(Long_t size, void *p);
   static void delete_calibrate_tree(void *p);
   static void deleteArray_calibrate_tree(void *p);
   static void destruct_calibrate_tree(void *p);
   static void streamer_calibrate_tree(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::calibrate_tree*)
   {
      ::calibrate_tree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::calibrate_tree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("calibrate_tree", ::calibrate_tree::Class_Version(), "calibrate_tree.h", 19,
                  typeid(::calibrate_tree), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::calibrate_tree::Dictionary, isa_proxy, 16,
                  sizeof(::calibrate_tree) );
      instance.SetNew(&new_calibrate_tree);
      instance.SetNewArray(&newArray_calibrate_tree);
      instance.SetDelete(&delete_calibrate_tree);
      instance.SetDeleteArray(&deleteArray_calibrate_tree);
      instance.SetDestructor(&destruct_calibrate_tree);
      instance.SetStreamerFunc(&streamer_calibrate_tree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::calibrate_tree*)
   {
      return GenerateInitInstanceLocal((::calibrate_tree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::calibrate_tree*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TOOL::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TOOL::Class_Name()
{
   return "TOOL";
}

//______________________________________________________________________________
const char *TOOL::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOOL*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TOOL::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TOOL*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TOOL::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOOL*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TOOL::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TOOL*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr dE_E_angle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *dE_E_angle::Class_Name()
{
   return "dE_E_angle";
}

//______________________________________________________________________________
const char *dE_E_angle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::dE_E_angle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int dE_E_angle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::dE_E_angle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *dE_E_angle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::dE_E_angle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *dE_E_angle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::dE_E_angle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr muchobojca::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *muchobojca::Class_Name()
{
   return "muchobojca";
}

//______________________________________________________________________________
const char *muchobojca::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::muchobojca*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int muchobojca::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::muchobojca*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *muchobojca::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::muchobojca*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *muchobojca::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::muchobojca*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr calibrate_tree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *calibrate_tree::Class_Name()
{
   return "calibrate_tree";
}

//______________________________________________________________________________
const char *calibrate_tree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::calibrate_tree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int calibrate_tree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::calibrate_tree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *calibrate_tree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::calibrate_tree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *calibrate_tree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::calibrate_tree*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TOOL::Streamer(TBuffer &R__b)
{
   // Stream an object of class TOOL.

   ::Error("TOOL::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TOOL(void *p) {
      return  p ? new(p) ::TOOL : new ::TOOL;
   }
   static void *newArray_TOOL(Long_t nElements, void *p) {
      return p ? new(p) ::TOOL[nElements] : new ::TOOL[nElements];
   }
   // Wrapper around operator delete
   static void delete_TOOL(void *p) {
      delete ((::TOOL*)p);
   }
   static void deleteArray_TOOL(void *p) {
      delete [] ((::TOOL*)p);
   }
   static void destruct_TOOL(void *p) {
      typedef ::TOOL current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TOOL(TBuffer &buf, void *obj) {
      ((::TOOL*)obj)->::TOOL::Streamer(buf);
   }
} // end of namespace ROOT for class ::TOOL

//______________________________________________________________________________
void dE_E_angle::Streamer(TBuffer &R__b)
{
   // Stream an object of class dE_E_angle.

   ::Error("dE_E_angle::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_dE_E_angle(void *p) {
      return  p ? new(p) ::dE_E_angle : new ::dE_E_angle;
   }
   static void *newArray_dE_E_angle(Long_t nElements, void *p) {
      return p ? new(p) ::dE_E_angle[nElements] : new ::dE_E_angle[nElements];
   }
   // Wrapper around operator delete
   static void delete_dE_E_angle(void *p) {
      delete ((::dE_E_angle*)p);
   }
   static void deleteArray_dE_E_angle(void *p) {
      delete [] ((::dE_E_angle*)p);
   }
   static void destruct_dE_E_angle(void *p) {
      typedef ::dE_E_angle current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_dE_E_angle(TBuffer &buf, void *obj) {
      ((::dE_E_angle*)obj)->::dE_E_angle::Streamer(buf);
   }
} // end of namespace ROOT for class ::dE_E_angle

//______________________________________________________________________________
void muchobojca::Streamer(TBuffer &R__b)
{
   // Stream an object of class muchobojca.

   ::Error("muchobojca::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_muchobojca(void *p) {
      return  p ? new(p) ::muchobojca : new ::muchobojca;
   }
   static void *newArray_muchobojca(Long_t nElements, void *p) {
      return p ? new(p) ::muchobojca[nElements] : new ::muchobojca[nElements];
   }
   // Wrapper around operator delete
   static void delete_muchobojca(void *p) {
      delete ((::muchobojca*)p);
   }
   static void deleteArray_muchobojca(void *p) {
      delete [] ((::muchobojca*)p);
   }
   static void destruct_muchobojca(void *p) {
      typedef ::muchobojca current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_muchobojca(TBuffer &buf, void *obj) {
      ((::muchobojca*)obj)->::muchobojca::Streamer(buf);
   }
} // end of namespace ROOT for class ::muchobojca

//______________________________________________________________________________
void calibrate_tree::Streamer(TBuffer &R__b)
{
   // Stream an object of class calibrate_tree.

   ::Error("calibrate_tree::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_calibrate_tree(void *p) {
      return  p ? new(p) ::calibrate_tree : new ::calibrate_tree;
   }
   static void *newArray_calibrate_tree(Long_t nElements, void *p) {
      return p ? new(p) ::calibrate_tree[nElements] : new ::calibrate_tree[nElements];
   }
   // Wrapper around operator delete
   static void delete_calibrate_tree(void *p) {
      delete ((::calibrate_tree*)p);
   }
   static void deleteArray_calibrate_tree(void *p) {
      delete [] ((::calibrate_tree*)p);
   }
   static void destruct_calibrate_tree(void *p) {
      typedef ::calibrate_tree current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_calibrate_tree(TBuffer &buf, void *obj) {
      ((::calibrate_tree*)obj)->::calibrate_tree::Streamer(buf);
   }
} // end of namespace ROOT for class ::calibrate_tree

namespace {
  void TriggerDictionaryInitialization_Mr_Blue_Sky_Impl() {
    static const char* headers[] = {
"TOOL.h",
"dE_E_angle.h",
"muchobojca.h",
"calibrate_tree.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/include",
"/usr/local/include",
"/home/zalewski/aku/wrk/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Mr_Blue_Sky dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TOOL.h")))  TOOL;
class __attribute__((annotate("$clingAutoload$dE_E_angle.h")))  dE_E_angle;
class __attribute__((annotate("$clingAutoload$muchobojca.h")))  muchobojca;
class __attribute__((annotate("$clingAutoload$calibrate_tree.h")))  calibrate_tree;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Mr_Blue_Sky dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TOOL.h"
#include "dE_E_angle.h"
#include "muchobojca.h"
#include "calibrate_tree.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TOOL", payloadCode, "@",
"calibrate_tree", payloadCode, "@",
"dE_E_angle", payloadCode, "@",
"muchobojca", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Mr_Blue_Sky",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Mr_Blue_Sky_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Mr_Blue_Sky_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Mr_Blue_Sky() {
  TriggerDictionaryInitialization_Mr_Blue_Sky_Impl();
}
