#include "internal/CheckDeprecated.h"

/* can be used for debug internal code inside bll with checking preprocessor */
#ifndef BLL_set_Mark
  #define BLL_set_Mark 0
#endif

#ifndef BLL_set_AreWeInsideStruct
  #define BLL_set_AreWeInsideStruct 0
#endif

#ifndef BLL_set_Language
  #if BLL_set_AreWeInsideStruct
    #define BLL_set_Language 1
  #elif defined(__language_c) && !defined(__language_cpp)
    #define BLL_set_Language 0
  #else
    #error BLL_set_Language needs to be set. 0 is C and 1 is C++
  #endif
#endif

#ifndef BLL_set_prefix
  #error ifndef BLL_set_prefix
#endif
#ifndef BLL_set_declare_NodeReference
  #define BLL_set_declare_NodeReference 1
#endif
#ifndef BLL_set_declare_rest
  #define BLL_set_declare_rest 1
#endif
#ifndef BLL_set_IntegerNR
  #define BLL_set_IntegerNR 0
#endif
#ifndef BLL_set_PreferNextFirst
  #define BLL_set_PreferNextFirst 1
#endif
#ifndef BLL_set_Recycle
  #define BLL_set_Recycle 1
#endif
#ifndef BLL_set_PadNode
  #define BLL_set_PadNode 0
#endif
#ifndef BLL_set_SafeNext
  #define BLL_set_SafeNext 0
#endif
#ifndef BLL_set_ResizeListAfterClear
  #define BLL_set_ResizeListAfterClear 0
#endif
#ifndef BLL_set_Link
  #define BLL_set_Link 1
#endif
#ifndef BLL_set_OnlyNextLink
  #define BLL_set_OnlyNextLink 0
#endif
#ifndef BLL_set_LinkSentinel
  #if BLL_set_Link
    #define BLL_set_LinkSentinel 1
  #else
    #define BLL_set_LinkSentinel 0
  #endif
#endif
#ifndef BLL_set_MultiThread
  #define BLL_set_MultiThread 0
#endif
#ifndef BLL_set_CountLockFail
  #define BLL_set_CountLockFail 0
#endif
#ifndef BLL_set_type_node
  #define BLL_set_type_node uint32_t
#endif
#ifndef BLL_set_NodeSizeType
  #define BLL_set_NodeSizeType uint32_t
#endif
#ifndef BLL_set_IsNodeRecycled
  #define BLL_set_IsNodeRecycled 0
#endif
#ifndef BLL_set_Clear
  #define BLL_set_Clear 0
#endif
#ifndef BLL_set_Usage
  #define BLL_set_Usage 0
#endif
#ifndef BLL_set_Allow_Usage_In_CapacityUpdateInfo
  #if defined(BLL_set_CapacityUpdateInfo) && BLL_set_Usage
    #define BLL_set_Allow_Usage_In_CapacityUpdateInfo 1
  #else
    #define BLL_set_Allow_Usage_In_CapacityUpdateInfo 0
  #endif
#endif

#ifndef BLL_set_CPP_nrsic
  #define BLL_set_CPP_nrsic 0
#endif
#ifndef BLL_set_CPP_Node_ConstructDestruct
  #define BLL_set_CPP_Node_ConstructDestruct 0
#endif
#ifndef BLL_set_CPP_ConstructDestruct
  #define BLL_set_CPP_ConstructDestruct 0
#endif
#ifndef BLL_set_CPP_CopyAtPointerChange
  #define BLL_set_CPP_CopyAtPointerChange 0
#endif

#ifndef BLL_set_nrtra
  #if BLL_set_CPP_Node_ConstructDestruct
    #define BLL_set_nrtra 1
  #elif BLL_set_CPP_CopyAtPointerChange
    #define BLL_set_nrtra 1
  #else
    #define BLL_set_nrtra 0
  #endif
#endif

#include "internal/PrepareAndInclude.h"

#ifdef BLL_set_NodeReference_Overload_Declare
  #undef BLL_set_NodeReference_Overload_Declare
#endif
#ifdef BLL_set_Overload_Declare
  #undef BLL_set_Overload_Declare
#endif

#ifdef BLL_set_NodeData
  #undef BLL_set_NodeData
#endif
#ifdef BLL_set_NodeDataType
  #undef BLL_set_NodeDataType
#endif

#undef BLL_set_nrtra

#undef BLL_set_CPP_CopyAtPointerChange
#undef BLL_set_CPP_ConstructDestruct
#undef BLL_set_CPP_Node_ConstructDestruct
#undef BLL_set_CPP_nrsic

#ifdef BLL_set_CapacityUpdateInfo
  #undef BLL_set_CapacityUpdateInfo
#endif
#undef BLL_set_Allow_Usage_In_CapacityUpdateInfo
#undef BLL_set_Usage
#undef BLL_set_Clear
#undef BLL_set_IsNodeRecycled
#undef BLL_set_NodeSizeType
#undef BLL_set_type_node
#ifdef BLL_set_CountLockFailGlobal
  #undef BLL_set_CountLockFailGlobal
#endif
#undef BLL_set_CountLockFail
#undef BLL_set_MultiThread
#undef BLL_set_LinkSentinel
#undef BLL_set_OnlyNextLink
#undef BLL_set_Link
#undef BLL_set_ResizeListAfterClear
#undef BLL_set_SafeNext
#undef BLL_set_PadNode
#undef BLL_set_Recycle
#undef BLL_set_PreferNextFirst
#undef BLL_set_IntegerNR
#undef BLL_set_declare_rest
#undef BLL_set_declare_NodeReference
#undef BLL_set_Language
#undef BLL_set_AreWeInsideStruct
#undef BLL_set_prefix
#undef BLL_set_Mark
#undef BLL_set_NodeReference_iterator