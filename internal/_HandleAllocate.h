#if BLL_set_CPP_CopyAtPointerChange
  #if BLL_HandleAllocate_define + BLL_set_AreWeInsideStruct <= 1
    static
    #if BLL_set_AreWeInsideStruct
      __forceinline
    #endif
    void *_P(_HandleAllocate)(
      void *_NodeList,
      BLL_set_type_node old_capacity
  #endif
  #if BLL_HandleAllocate_define + BLL_set_AreWeInsideStruct == 1
    ){
      _P(t) *bll = OFFSETLESS(_NodeList, _P(t), NodeList);

      BLL_set_type_node Capacity = _P(_NodeList_GetCapacity)(&bll->NodeList);

      uint8_t *old_ptr = (uint8_t *)_P(_NodeList_GetSinglePointer)(
        &bll->NodeList
      );
      uint8_t *new_ptr = (uint8_t *)_P(_NodeList__mmap)(
        (uintptr_t)Capacity * _P(_NodeList_GetNodeSize)(&bll->NodeList)
      );
      __builtin_memcpy(
        new_ptr,
        old_ptr,
        old_capacity * _P(_NodeList_GetNodeSize)(&bll->NodeList)
      );

    #if BLL_set_Language == 1
      typename
    #endif
      _P(t)::nrtra_t nrtra;
      _P(NodeReference_t) node_id;
      nrtra.Open(bll, &node_id);
      while(nrtra.Loop(bll, &node_id) == true){
        new
          (&((_P(Node_t) *)new_ptr)[*_P(gnrint)(&node_id)].data)
          _P(NodeData_t)(((_P(Node_t) *)old_ptr)[*_P(gnrint)(&node_id)].data);
      }
      nrtra.Close(bll);

      bll->_DestructAllNodes();

      _P(_NodeList__mfree)(
        old_ptr,
        old_capacity * _P(_NodeList_GetNodeSize)(&bll->NodeList)
      );

      return new_ptr;
    }
  #elif !BLL_set_AreWeInsideStruct
    );
  #endif
#endif

#undef BLL_HandleAllocate_define
