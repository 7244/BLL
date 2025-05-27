#if BLL_set_PadNode == 0
  #pragma pack(push, 1)
#endif
#if defined(_BLL_HaveConstantNodeData)
  #if defined(BLL_set_NodeData)
    BLL_DeclareStruct(_P(NodeData_t));
    struct _P(NodeData_t){
      BLL_set_NodeData
    };
  #elif defined(BLL_set_NodeDataType)
    typedef BLL_set_NodeDataType _P(NodeData_t);
  #else
    #error not possible
  #endif
#else
  typedef void _P(NodeData_t);
#endif
typedef struct{
  #if BLL_set_Link == 1
    #if BLL_set_PreferNextFirst == 1
      _P(NodeReference_t) NextNodeReference;
      #if !BLL_set_OnlyNextLink
        _P(NodeReference_t) PrevNodeReference;
      #endif
    #else
      #if !BLL_set_OnlyNextLink
        _P(NodeReference_t) PrevNodeReference;
      #endif
      _P(NodeReference_t) NextNodeReference;
    #endif
  #endif
  #ifdef _BLL_HaveConstantNodeData
    #if BLL_set_CPP_Node_ConstructDestruct
      _P(NodeData_t) data;
      #if BLL_set_Link == 0
        uint8_t _PaddingForNextRecycled[
          sizeof(_P(NodeData_t)) < sizeof(_P(NodeReference_t)) ?
            sizeof(_P(NodeReference_t)) - sizeof(_P(NodeData_t)) :
            0
        ];
      #endif
    #else
      union{
        _P(NodeData_t) data;
        #if BLL_set_Link == 0
          /* used for empty next */
          _P(NodeReference_t) _NextRecycled;
        #endif
      };
    #endif
  #endif
}_P(Node_t);
#if BLL_set_PadNode == 0
  #pragma pack(pop)
#endif

BLL_DeclareStruct(_P(t));

#define BLL_CapacityUpdateInfo_define 0
#include "_CapacityUpdateInfo.h"

#define BLL_HandleAllocate_define 0
#include "_HandleAllocate.h"

#define bcontainer_set_Prefix _P(_NodeList)
#define bcontainer_set_NodeType BLL_set_type_node
#if defined(_BLL_HaveConstantNodeData)
  #define bcontainer_set_NodeData _P(Node_t)
#endif
#if BLL_set_CPP_CopyAtPointerChange
  #define bcontainer_set_HandleAllocate _P(_HandleAllocate)
#endif
#if defined(BLL_set_CapacityUpdateInfo)
  #define bcontainer_set_CapacityUpdateInfo \
    _P(_CapacityUpdateInfo)(This, old_capacity, new_capacity);
#endif
#define bcontainer_set_Clear BLL_set_Clear
#define bcontainer_set_Recycle BLL_set_Recycle
#if BLL_set_IsNodeRecycled
  #define bcontainer_set_IsElementRecycled 1
  #if BLL_set_Link && !BLL_set_OnlyNextLink
    #define bcontainer_set_IsElementRecycled \
      bcontainer_set_IsElementRecycled_Strategy_InvalidateDataAsID
  #else
    #define bcontainer_set_IsElementRecycled 1
  #endif
#endif
#define bcontainer_set_MultiThread BLL_set_MultiThread
#define bcontainer_set_CountLockFail BLL_set_CountLockFail
#if defined(BLL_set_CountLockFailGlobal)
  #define bcontainer_set_CountLockFailGlobal BLL_set_CountLockFailGlobal
#endif
#include <bcontainer/bcontainer.h>

#if BLL_set_MultiThread
  #define BME_set_Prefix _P(_FastLock)
  #define BME_set_LockValue 1
  #define BME_set_Sleep 0
  #define BME_set_CountLockFail BLL_set_CountLockFail
  #ifdef BLL_set_CountLockFailGlobal
    #define BME_set_CountLockFailGlobal BLL_set_CountLockFailGlobal
  #endif
  #include <BME/BME.h>
#endif

struct _P(t){
  _P(_NodeList_t) NodeList;

  #if BLL_set_LinkSentinel
    _P(NodeReference_t) src;
    _P(NodeReference_t) dst;
  #endif

  #if BLL_set_SafeNext == 1
    _P(NodeReference_t) SafeNext;
  #elif BLL_set_SafeNext > 1
    uint8_t SafeNextCount;
    _P(NodeReference_t) SafeNext[BLL_set_SafeNext];
  #endif

#if BLL_set_Language == 0
  };
#else
  using nd_t = _P(NodeData_t);
  using nr_t = _P(NodeReference_t);

  nr_t gnric(){
    return _P(gnric)();
  }
  bool inric(
    nr_t nr
  ){
    return _P(inric)(nr);
  }
#endif

_BLL_fdec(BLL_set_NodeSizeType, GetNodeSize
){
  return _P(_NodeList_GetNodeSize)(&_BLL_this->NodeList);
}

/* is node reference invalid */
_BLL_fdec(bool, inri,
  _P(NodeReference_t) node_id
){
  return _P(_NodeList_IsElementInvalid)(
    &_BLL_this->NodeList,
    *_P(gnrint)(&node_id)
  );
}

_BLL_fdec(_P(Node_t) *, GetNodeUnsafe,
  _P(NodeReference_t) nr
){
  return (_P(Node_t) *)_P(_NodeList_GetNode)(&_BLL_this->NodeList, *_P(gnrint)(&nr));
}

#if !BLL_set_MultiThread
  /* backward compatibility */
  _BLL_fdec(__forceinline _P(Node_t) *, GetNodeByReference,
    _P(NodeReference_t) node_id
  ){
    return _BLL_fcall(GetNodeUnsafe, node_id);
  }
#endif

_BLL_fdec(_P(Node_t) *, AcquireNode,
  _P(NodeReference_t) nr
){
  return _BLL_fcall(GetNodeUnsafe, nr);
}

_BLL_fdec(void, ReleaseNode,
  _P(NodeReference_t) nr,
  _P(Node_t) *n
){
  /* ~mazurek~ */
}

_BLL_fdec(uintptr_t, _ndoffset
){
  #if defined(_BLL_HaveConstantNodeData)
    return offsetof(_P(Node_t), data);
  #else
    #if BLL_set_Link == 1
      return sizeof(_P(NodeReference_t)) * (1 + !BLL_set_OnlyNextLink);
    #else
      return 0;
    #endif
  #endif
}

#if !BLL_set_MultiThread
  _BLL_fdec(_P(NodeData_t) *, GetNodeDataPointer,
    _P(NodeReference_t) node_id
  ){
    _P(Node_t) *n = _BLL_fcall(GetNodeByReference, node_id);
    return (_P(NodeData_t) *)((uint8_t *)n + _BLL_fcall(_ndoffset));
  }
#endif

_BLL_fdec(void, SetNodeData,
  _P(NodeReference_t) node_id,
  const _P(NodeData_t) *data
){
  _P(Node_t) *node = _BLL_fcall(AcquireNode, node_id);

  _P(NodeData_t) *nd = (_P(NodeData_t) *)((uint8_t *)node + _BLL_fcall(_ndoffset));

  #if defined(_BLL_HaveConstantNodeData)
    *nd = *data;
  #else
    __builtin_memcpy(nd, data, _BLL_fcall(GetNodeSize) - _BLL_fcall(_ndoffset));
  #endif

  _BLL_fcall(ReleaseNode, node_id, node);
}

#if BLL_set_Usage
  _BLL_fdec(BLL_set_type_node, Usage
  ){
    return _P(_NodeList_Usage)(&_BLL_this->NodeList)
      #if BLL_set_LinkSentinel
        #if BLL_set_Allow_Usage_In_CapacityUpdateInfo
          - !_P(inric)(_BLL_this->src)
          - !_P(inric)(_BLL_this->dst)
        #else
          - 2
        #endif
      #endif
    ;
  }
#endif

_BLL_fdec(BLL_set_type_node, SizeNormalized
){
  return _P(_NodeList_SizeNormalized)(&_BLL_this->NodeList)
    #if BLL_set_LinkSentinel
      #if BLL_set_Allow_Usage_In_CapacityUpdateInfo
        - !_P(inric)(_BLL_this->src)
        - !_P(inric)(_BLL_this->dst)
      #else
        - 2
      #endif
    #endif
  ;
}

_BLL_fdec(void, _Node_Construct,
  _P(NodeReference_t) nr
){
  #if BLL_set_CPP_Node_ConstructDestruct
    #if BLL_set_MultiThread
      #error enjoy implementing
    #endif
    new (_BLL_fcall(GetNodeDataPointer, nr)) _P(NodeData_t);
  #endif
}
_BLL_fdec(void, _Node_Destruct,
  _P(NodeReference_t) nr
){
  #if BLL_set_CPP_Node_ConstructDestruct
    #if BLL_set_MultiThread
      #error enjoy implementing
    #endif
    _BLL_fcall(GetNodeDataPointer, nr)->~_P(NodeData_t)();
  #endif
}

_BLL_fdec(_P(Node_t) *, AcquireLinkNode,
  _P(NodeReference_t) node_id
){
  return _BLL_fcall(AcquireNode, node_id);
}
_BLL_fdec(void, ReleaseLinkNode,
  _P(NodeReference_t) node_id,
  _P(Node_t) *node
){
  _BLL_fcall(ReleaseNode, node_id, node);
}

_BLL_fdec(_P(NodeReference_t), _GetNodeAsID,
  _P(NodeReference_t) node_id,
  BLL_set_type_node index
){
  _P(Node_t) *node = _BLL_fcall(AcquireLinkNode, node_id);

  _P(NodeReference_t) ret = ((_P(NodeReference_t) *)node)[index];

  _BLL_fcall(ReleaseLinkNode, node_id, node);

  return ret;
}
_BLL_fdec(void, _SetNodeAsID,
  _P(NodeReference_t) node_id,
  BLL_set_type_node index,
  _P(NodeReference_t) id
){
  _P(Node_t) *node = _BLL_fcall(AcquireLinkNode, node_id);

  ((_P(NodeReference_t) *)node)[index] = id;

  _BLL_fcall(ReleaseLinkNode, node_id, node);
}

#if BLL_set_Recycle
  #if BLL_set_IsNodeRecycled
    _BLL_fdec(bool, IsNodeReferenceRecycled,
      _P(NodeReference_t) node_id
    ){
      return _P(_NodeList_IsElementRecycled)(
        &_BLL_this->NodeList,
        *_P(gnrint)(&node_id)
      );
    }
  #endif

  _BLL_fdec(void, Recycle_NoDestruct,
    _P(NodeReference_t) nr
  ){
    _P(_NodeList_Recycle)(&_BLL_this->NodeList, *_P(gnrint)(&nr));
  }

  _BLL_fdec(void, Recycle,
    _P(NodeReference_t) nr
  ){
    _BLL_fcall(_Node_Destruct, nr);
    _BLL_fcall(Recycle_NoDestruct, nr);
  }
#endif

_BLL_fdec(_P(NodeReference_t), _NewNode_NoConstruct
){
  BLL_set_type_node r = _P(_NodeList_NewNode)(&_BLL_this->NodeList);
  return *(_P(NodeReference_t) *)&r;
}
_BLL_fdec(_P(NodeReference_t), NewNode
){
  _P(NodeReference_t) nr = _BLL_fcall(_NewNode_NoConstruct);
  _BLL_fcall(_Node_Construct, nr);
  return nr;
}

#if BLL_set_Link == 1

  _BLL_fdec(void, linkNext,
    _P(NodeReference_t) srcnr,
    _P(NodeReference_t) dstnr
  ){
    _P(Node_t) *srcNode = _BLL_fcall(AcquireLinkNode, srcnr);
    _P(NodeReference_t) next_id = srcNode->NextNodeReference;
    srcNode->NextNodeReference = dstnr;
    _BLL_fcall(ReleaseLinkNode, srcnr, srcNode);

    _P(Node_t) *dstNode = _BLL_fcall(AcquireLinkNode, dstnr);
    #if !BLL_set_OnlyNextLink
      dstNode->PrevNodeReference = srcnr;
    #endif
    dstNode->NextNodeReference = next_id;
    _BLL_fcall(ReleaseLinkNode, dstnr, dstNode);

    #if !BLL_set_OnlyNextLink
      _P(Node_t) *next_node = _BLL_fcall(AcquireLinkNode, next_id);
      next_node->PrevNodeReference = dstnr;
      _BLL_fcall(ReleaseLinkNode, next_id, next_node);
    #endif
  }
  _BLL_fdec(void, linkNextOfOrphan,
    _P(NodeReference_t) srcnr,
    _P(NodeReference_t) dstnr
  ){
    _P(Node_t) *srcNode = _BLL_fcall(AcquireLinkNode, srcnr);
    srcNode->NextNodeReference = dstnr;
    _BLL_fcall(ReleaseLinkNode, srcnr, srcNode);

    #if !BLL_set_OnlyNextLink
      _P(Node_t) *dstNode = _BLL_fcall(AcquireLinkNode, dstnr);
      dstNode->PrevNodeReference = srcnr;
      _BLL_fcall(ReleaseLinkNode, dstnr, dstNode);
    #endif
  }
  #if !BLL_set_OnlyNextLink
    _BLL_fdec(void, linkPrev,
      _P(NodeReference_t) srcnr,
      _P(NodeReference_t) dstnr
    ){
      _P(Node_t) *srcNode = _BLL_fcall(AcquireLinkNode, srcnr);
      _P(NodeReference_t) prev_id = srcNode->PrevNodeReference;
      srcNode->PrevNodeReference = dstnr;
      _BLL_fcall(ReleaseLinkNode, srcnr, srcNode);

      _P(Node_t) *prevNode = _BLL_fcall(AcquireLinkNode, prev_id);
      prevNode->NextNodeReference = dstnr;
      _BLL_fcall(ReleaseLinkNode, prev_id, prevNode);

      _P(Node_t) *dstNode = _BLL_fcall(AcquireLinkNode, dstnr);
      dstNode->PrevNodeReference = prev_id;
      dstNode->NextNodeReference = srcnr;
      _BLL_fcall(ReleaseLinkNode, dstnr, dstNode);
    }
  #endif
  _BLL_fdec(void, linkPrevOfOrphan,
    _P(NodeReference_t) srcnr,
    _P(NodeReference_t) dstnr
  ){
    _P(Node_t) *dstNode = _BLL_fcall(AcquireLinkNode, dstnr);
    dstNode->NextNodeReference = srcnr;
    _BLL_fcall(ReleaseLinkNode, dstnr, dstNode);

    #if !BLL_set_OnlyNextLink
      _P(Node_t) *srcNode = _BLL_fcall(AcquireLinkNode, srcnr);
      srcNode->PrevNodeReference = dstnr;
      _BLL_fcall(ReleaseLinkNode, srcnr, srcNode);
    #endif
  }

  #if !BLL_set_OnlyNextLink
    /* set invalid constant previous link */
    _BLL_fdec(void, sicpl,
      _P(NodeReference_t) node_id
    ){
      _P(Node_t) *node = _BLL_fcall(AcquireLinkNode, node_id);
      node->PrevNodeReference = _P(gnric)();
      _BLL_fcall(ReleaseLinkNode, node_id, node);
    }
  #endif
  /* set invalid constant next link */
  _BLL_fdec(void, sicnl,
    _P(NodeReference_t) node_id
  ){
    _P(Node_t) *node = _BLL_fcall(AcquireLinkNode, node_id);
    node->NextNodeReference = _P(gnric)();
    _BLL_fcall(ReleaseLinkNode, node_id, node);
  }

  #if !BLL_set_OnlyNextLink
    _BLL_fdec(void, Unlink,
      _P(NodeReference_t) node_id
    ){
      _P(Node_t) *node = _BLL_fcall(AcquireLinkNode, node_id);

      #if BLL_set_SafeNext == 1
        if(_BLL_this->SafeNext == node_id){
          _BLL_this->SafeNext = node->PrevNodeReference;
        }
      #elif BLL_set_SafeNext > 1
        for(uint8_t i = 0; i < _BLL_this->SafeNextCount; i++){
          if(_BLL_this->SafeNext[i] == node_id){
            _BLL_this->SafeNext[i] = node->PrevNodeReference;
          }
        }
      #endif

      _P(NodeReference_t) nnr = node->NextNodeReference;
      _P(NodeReference_t) pnr = node->PrevNodeReference;

      _BLL_fcall(ReleaseLinkNode, node_id, node);

      _P(Node_t) *next_node = _BLL_fcall(AcquireLinkNode, nnr);
      next_node->PrevNodeReference = pnr;
      _BLL_fcall(ReleaseLinkNode, nnr, next_node);

      _P(Node_t) *prev_node = _BLL_fcall(AcquireLinkNode, pnr);
      prev_node->NextNodeReference = nnr;
      _BLL_fcall(ReleaseLinkNode, pnr, prev_node);
    }
  #endif

  #if BLL_set_Recycle
    /* unlink recycle */
    _BLL_fdec(void, unlrec,
      _P(NodeReference_t) nr
    ){
      _BLL_fcall(Unlink, nr);
      _BLL_fcall(Recycle, nr);
    }
  #endif

  #if BLL_set_LinkSentinel
    _BLL_fdec(_P(NodeReference_t), GetNodeFirst
    ){
      #if BLL_set_MultiThread
        #error other thread can change sentinel. solve it
      #endif
      _P(Node_t) *sentinel_node = _BLL_fcall(AcquireLinkNode, _BLL_this->src);
      _P(NodeReference_t) ret = sentinel_node->NextNodeReference;
      _BLL_fcall(ReleaseLinkNode, _BLL_this->src, sentinel_node);
      return ret;
    }
    _BLL_fdec(_P(NodeReference_t), GetNodeLast
    ){
      #if BLL_set_MultiThread
        #error other thread can change sentinel. solve it
      #endif
      _P(Node_t) *sentinel_node = _BLL_fcall(AcquireLinkNode, _BLL_this->dst);
      _P(NodeReference_t) ret = sentinel_node->PrevNodeReference;
      _BLL_fcall(ReleaseLinkNode, _BLL_this->dst, sentinel_node);
      return ret;
    }

    _BLL_fdec(_P(NodeReference_t), NewNodeFirst
    ){
      _P(NodeReference_t) new_node_id = _BLL_fcall(_NewNode_NoConstruct);

      #if BLL_set_MultiThread
        #error other thread can change sentinel. solve it
      #endif

      _P(NodeReference_t) sentinel_node_id = _BLL_this->src;

      _P(Node_t) *new_node = _BLL_fcall(AcquireLinkNode, new_node_id);
      new_node->NextNodeReference = sentinel_node_id;
      _BLL_fcall(ReleaseLinkNode, new_node_id, new_node);

      _P(Node_t) *sentinel_node = _BLL_fcall(AcquireLinkNode, sentinel_node_id);
      sentinel_node->PrevNodeReference = new_node_id;
      _BLL_fcall(ReleaseLinkNode, sentinel_node_id, sentinel_node);

      _BLL_this->src = new_node_id;

      _BLL_fcall(_Node_Construct, sentinel_node_id);

      return sentinel_node_id;
    }
    _BLL_fdec(_P(NodeReference_t), NewNodeLast
    ){
      _P(NodeReference_t) new_node_id = _BLL_fcall(_NewNode_NoConstruct);

      #if BLL_set_MultiThread
        #error other thread can change sentinel. solve it
      #endif

      _P(NodeReference_t) sentinel_node_id = _BLL_this->dst;

      _P(Node_t) *new_node = _BLL_fcall(AcquireLinkNode, new_node_id);
      new_node->PrevNodeReference = sentinel_node_id;
      _BLL_fcall(ReleaseLinkNode, new_node_id, new_node);

      _P(Node_t) *sentinel_node = _BLL_fcall(AcquireLinkNode, sentinel_node_id);
      sentinel_node->NextNodeReference = new_node_id;
      _BLL_fcall(ReleaseLinkNode, sentinel_node_id, sentinel_node);

      _BLL_this->dst = new_node_id;

      _BLL_fcall(_Node_Construct, sentinel_node_id);

      return sentinel_node_id;
    }

    _BLL_fdec(bool, IsNRSentinel,
      _P(NodeReference_t) nr
    ){
      if(*_P(gnrint)(&nr) == *_P(gnrint)(&_BLL_this->src)){
        return 1;
      }
      if(*_P(gnrint)(&nr) == *_P(gnrint)(&_BLL_this->dst)){
        return 1;
      }
      return 0;
    }

    _BLL_fdec(void, LinkAsFirst,
      _P(NodeReference_t) nr
    ){
      _BLL_fcall(linkNext, _BLL_this->src, nr);
    }
    _BLL_fdec(void, LinkAsLast,
      _P(NodeReference_t) nr
    ){
      _BLL_fcall(linkPrev, _BLL_this->dst, nr);
    }

    _BLL_fdec(void, ReLinkAsFirst,
      _P(NodeReference_t) nr
    ){
      _BLL_fcall(Unlink, nr);
      _BLL_fcall(LinkAsFirst, nr);
    }
    _BLL_fdec(void, ReLinkAsLast,
      _P(NodeReference_t) nr
    ){
      _BLL_fcall(Unlink, nr);
      _BLL_fcall(LinkAsLast, nr);
    }
  #endif
#endif

#if BLL_set_Recycle
  #include "RecycleTraverse.h"
#endif
#if BLL_set_nrtra
  #include "nrtra.h"
#endif

_BLL_fdec(void, _DestructAllNodes
){
  #if BLL_set_CPP_Node_ConstructDestruct
    nrtra_t nrtra;
    _P(NodeReference_t) node_id;
    nrtra.Open(_BLL_this, &node_id);
    while(nrtra.Loop(_BLL_this, &node_id) == true){
      _BLL_fcall(_Node_Destruct, node_id);
    }
    nrtra.Close(_BLL_this);
  #endif
}

_BLL_fdec(void, _AfterInitNodes
){
  #if BLL_set_LinkSentinel
    #if BLL_set_Allow_Usage_In_CapacityUpdateInfo
      _BLL_this->src = _P(gnric)();
      _BLL_this->dst = _P(gnric)();
    #endif

    _BLL_this->src = _BLL_fcall(_NewNode_NoConstruct);
    _BLL_this->dst = _BLL_fcall(_NewNode_NoConstruct);

    _BLL_fcall(GetNodeUnsafe, _BLL_this->src)->NextNodeReference = _BLL_this->dst;
    _BLL_fcall(GetNodeUnsafe, _BLL_this->dst)->PrevNodeReference = _BLL_this->src;
  #endif
}

#if BLL_set_CPP_ConstructDestruct
  private:
#endif
_BLL_fdecnds(void, Open
){
  BLL_set_NodeSizeType NodeSize = 0;

  #if BLL_set_Link
    #if BLL_set_OnlyNextLink
      NodeSize += sizeof(_P(NodeReference_t)) * 1;
    #else
      NodeSize += sizeof(_P(NodeReference_t)) * 2;
    #endif
  #endif

  #if !defined(_BLL_HaveConstantNodeData)
    NodeSize += NodeDataSize;
  #else
    NodeSize += sizeof(_P(NodeData_t));
  #endif

  #if defined(_BLL_HaveConstantNodeData)
    _P(_NodeList_Open)(&_BLL_this->NodeList);
  #else
    _P(_NodeList_Open)(&_BLL_this->NodeList, NodeSize);
  #endif

  #if BLL_set_SafeNext == 1
    _P(snric)(&_BLL_this->SafeNext); /* TOOD but why we set it initially? */
  #elif BLL_set_SafeNext > 1
    _BLL_this->SafeNextCount = 0;
  #endif

  _BLL_fcall(_AfterInitNodes);
}
_BLL_fdec(void, Close
){
  _BLL_fcall(_DestructAllNodes);
  _P(_NodeList_Close)(&_BLL_this->NodeList);
}
#if BLL_set_CPP_ConstructDestruct
  public:
#endif

#if BLL_set_Clear
  _BLL_fdec(void, Clear
  ){
    _BLL_fcall(_DestructAllNodes);
    _P(_NodeList_Clear)(&_BLL_this->NodeList);
    _BLL_fcall(_AfterInitNodes);
  }
#endif

/* TODO make implement of this with !BLL_set_LinkSentinel */
#if BLL_set_LinkSentinel
  _BLL_fdec(bool, IsNodeReferenceFronter,
    _P(NodeReference_t) srcnr,
    _P(NodeReference_t) dstnr
  ){
    _P(NodeReference_t) node_id = srcnr;
    do{
      _P(Node_t) *node = _BLL_fcall(AcquireNode, node_id);
      _P(NodeReference_t) tmp_id = node->NextNodeReference;
      _BLL_fcall(ReleaseNode, node_id, node);
      node_id = tmp_id;

      if(_P(inre)(srcnr, dstnr)){
        return 0;
      }
    }while(!_P(inre)(srcnr, _BLL_this->dst));
    return 1;
  }
#endif

#if BLL_set_SafeNext != 0
  _BLL_fdec(void, StartSafeNext,
    _P(NodeReference_t) nr
  ){
    #if BLL_set_SafeNext == 1
      _BLL_this->SafeNext = nr;
    #else
      _BLL_this->SafeNext[_BLL_this->SafeNextCount++] = nr;
    #endif
  }
  _BLL_fdec(_P(NodeReference_t), EndSafeNext
  ){
    _P(NodeReference_t) nr;
    #if BLL_set_SafeNext == 1
      nr = _BLL_this->SafeNext;
      _P(snric)(&_BLL_this->SafeNext); /* TODO but why we set? */
    #else
      nr = _BLL_this->SafeNext[--_BLL_this->SafeNextCount];
    #endif
    _P(Node_t) *Node = _BLL_fcall(GetNodeByReference, nr);
    return Node->NextNodeReference;
  }
  _BLL_fdec(_P(NodeReference_t), CheckSafeNext,
    uint8_t Depth
  ){
    ++Depth;
    #if BLL_set_SafeNext == 1
      return _BLL_this->SafeNext;
    #else
      return _BLL_this->SafeNext[_BLL_this->SafeNextCount - Depth];
    #endif
  }
#endif

#if BLL_set_Language == 1
  #if !BLL_set_MultiThread
    #if defined(_BLL_HaveConstantNodeData)
      _P(NodeData_t) &operator[](_P(NodeReference_t) NR){
        return *GetNodeDataPointer(NR);
      }
    #else
      _P(NodeData_t) *operator[](_P(NodeReference_t) NR){
        return GetNodeDataPointer(NR);
      }
    #endif
  #endif

  #if BLL_set_CPP_ConstructDestruct
    _P(t)(
      #if !defined(_BLL_HaveConstantNodeData)
        BLL_set_NodeSizeType NodeDataSize
      #endif
    ){
      Open(
        #if !defined(_BLL_HaveConstantNodeData)
          NodeDataSize
        #endif
      );
    }
    ~_P(t)(
    ){
      Close();
    }
  #endif

  #ifdef BLL_set_Overload_Declare
    BLL_set_Overload_Declare
  #endif
#endif

#if !BLL_set_Recycle && BLL_set_IntegerNR && !BLL_set_LinkSentinel
  #if BLL_set_Usage
    #if BLL_set_Language == 1
      _P(NodeData_t) *begin() { return &operator[](0); }
      _P(NodeData_t) *end() { return &operator[](Usage()); }
    #endif
  #endif

  _BLL_fdec(void, inc
  ){
    _BLL_fcall(NewNode);
  }
  _BLL_fdec(void, dec
  ){
    _BLL_fcall(_Node_Destruct, --_BLL_this->NodeList.Current);
  }
#endif

#if BLL_set_Language == 1
  };

  #if BLL_set_Link == 1
    static _P(NodeReference_t) _P(_NodeReference_Next)(_P(NodeReference_t) *node_id, _P(t) *list){
      _P(Node_t) *node = list->AcquireLinkNode(*node_id);
      auto ret = node->NextNodeReference;
      list->ReleaseLinkNode(*node_id, node);
      return ret;
    }
    #if !BLL_set_OnlyNextLink
      static _P(NodeReference_t) _P(_NodeReference_Prev)(_P(NodeReference_t) *node_id, _P(t) *list){
        _P(Node_t) *node = list->AcquireLinkNode(*node_id);
        auto ret = node->PrevNodeReference;
        list->ReleaseLinkNode(*node_id, node);
        return ret;
      }
    #endif
  #endif
#endif

#define BLL_CapacityUpdateInfo_define 1
#include "_CapacityUpdateInfo.h"

#define BLL_HandleAllocate_define 1
#include "_HandleAllocate.h"
