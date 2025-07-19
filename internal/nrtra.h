#if BLL_set_Language == 0
  typedef struct{
#elif BLL_set_Language == 1
  struct nrtra_t{
#endif

  BLL_set_type_node normalized;

  #if BLL_set_Recycle == 0
  #elif BLL_set_IsNodeRecycled == 0
    uint8_t *_RecycledArray;
  #endif

#if BLL_set_Language == 0
  }_P(nrtra_t);
#endif

  #define _BLL_nrtra_count _P(_NodeList_SizeNormalized)(&bll->NodeList)
  #define _BLL_nrtra_size (_BLL_nrtra_count / 8 + !!(_BLL_nrtra_count % 8))

  #if BLL_set_Language == 0
    #define _BLL_nrtra_this This
    #define _BLL_nrtra_fdec(rtype, name, ...) static rtype CONCAT2(_P(nrtra_),name)(_P(nrtra_t) *This, _P(t) *bll, ##__VA_ARGS__)
    #define _BLL_nrtra_fcall(name, ...) _P(name)(bll, ##__VA_ARGS__)
    #define _BLL_nrtra_pcall(name, ...) _P(name)(bll, ##__VA_ARGS__)
  #elif BLL_set_Language == 1
    #define _BLL_nrtra_this this
    #define _BLL_nrtra_fdec(rtype, name, ...) rtype name(_P(t) *bll, ##__VA_ARGS__)
    #define _BLL_nrtra_fcall(name, ...) bll->name(__VA_ARGS__)
    #define _BLL_nrtra_pcall(name, ...) bll->name(__VA_ARGS__)
  #else
    #error ?
  #endif

  _BLL_nrtra_fdec(void, Open,
    _P(NodeReference_t) *node_id
  ){
    #if BLL_set_Recycle == 0
    #elif BLL_set_IsNodeRecycled == 0
      _BLL_nrtra_this->_RecycledArray = (uint8_t *)_P(_NodeList__mmalloc)(
        _BLL_nrtra_size
      );
      __builtin_memset(
        _BLL_nrtra_this->_RecycledArray,
        0,
        _BLL_nrtra_size
      );
      BLL_set_type_node cnr = bll->NodeList.e.c;
      for(BLL_set_type_node i = bll->NodeList.e.p; i != 0; --i){
        BLL_set_type_node norm = _P(_NodeList_Normalize)(&bll->NodeList, cnr);
        BLL_set_type_node div = norm / 8;
        uint8_t mod = norm % 8;
        _BLL_nrtra_this->_RecycledArray[div] |= (uint8_t)1 << mod;
        cnr = _P(_NodeList__GetNextRecycledFromID)(&bll->NodeList, cnr);
      }
    #endif

    _BLL_nrtra_this->normalized = (BLL_set_type_node)-1;
  }
  _BLL_nrtra_fdec(void, Close
  ){
    #if BLL_set_Recycle == 0
    #elif BLL_set_IsNodeRecycled == 0
      _P(_NodeList__munmap)(_BLL_nrtra_this->_RecycledArray, _BLL_nrtra_size);
    #endif
  }

  _BLL_nrtra_fdec(bool, Loop,
    _P(NodeReference_t) *node_id
  ){
    while(++_BLL_nrtra_this->normalized < _BLL_nrtra_count){

      *_P(gnrint)(node_id) = _P(_NodeList_Unnormalize)(
        &bll->NodeList,
        _BLL_nrtra_this->normalized
      );

      #if BLL_set_Recycle == 0
      #elif BLL_set_IsNodeRecycled == 0
        BLL_set_type_node div = _BLL_nrtra_this->normalized / 8;
        uint8_t mod = _BLL_nrtra_this->normalized % 8;
        if(_BLL_nrtra_this->_RecycledArray[div] & (uint8_t)1 << mod){
          continue;
        }
      #elif BLL_set_IsNodeRecycled == 1
        #error TODO unnormalize
        if(_BLL_nrtra_fcall(IsNodeReferenceRecycled, *node_id)){
          continue;
        }
      #else
        #error ?
      #endif

      #if BLL_set_LinkSentinel
        if(_BLL_nrtra_fcall(IsNRSentinel, *node_id)){
          continue;
        }
      #endif

      return 1;
    }
    return 0;
  }

  #undef _BLL_nrtra_this
  #undef _BLL_nrtra_fdec
  #undef _BLL_nrtra_fcall
  #undef _BLL_nrtra_pcall

  #undef _BLL_nrtra_size
  #undef _BLL_nrtra_count

#if BLL_set_Language == 1
  };
#endif
