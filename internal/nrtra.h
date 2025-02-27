#if BLL_set_Language == 0
  typedef struct{
#elif BLL_set_Language == 1
  struct nrtra_t{
#endif
  _P(NodeReference_t) nr;
  #if BLL_set_Recycle == 0
  #elif BLL_set_IsNodeRecycled == 0
    uint8_t *_RecycledArray;
  #endif

#if BLL_set_Language == 0
  }_P(nrtra_t);
#endif

  #define _BLL_nrtra_count _P(_NodeList_Usage)(&bll->NodeList)

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

  _BLL_nrtra_fdec(void, Open
  ){
    #if BLL_set_Recycle == 0
    #elif BLL_set_IsNodeRecycled == 0
      uintptr_t size = _BLL_nrtra_count * sizeof(uint8_t);
      _BLL_nrtra_this->_RecycledArray = (uint8_t *)__generic_malloc(size);
      __MemorySet(0, _BLL_nrtra_this->_RecycledArray, size);
      _P(NodeReference_t) cnr = bll->e.c;
      for(BLL_set_type_node i = bll->e.p; i != 0; --i){
        _BLL_nrtra_this->_RecycledArray[*_P(gnrint)(&cnr)] = 1;
        cnr = _BLL_nrtra_fcall(_GetNodeAsID, cnr, _BLL_nrtra_pcall(_RecycleIndex));
      }
    #endif
    *_P(gnrint)(&_BLL_nrtra_this->nr) = (BLL_set_type_node)-1;
  }
  _BLL_nrtra_fdec(void, Close
  ){
    #if BLL_set_Recycle == 0
    #elif BLL_set_IsNodeRecycled == 0
      __generic_free(_BLL_nrtra_this->_RecycledArray);
    #endif
  }

  _BLL_nrtra_fdec(bool, Loop
  ){
    while(++*_P(gnrint)(&_BLL_nrtra_this->nr) < _BLL_nrtra_count){

      #if BLL_set_Recycle == 0
      #elif BLL_set_IsNodeRecycled == 0
        if(_BLL_nrtra_this->_RecycledArray[*_P(gnrint)(&_BLL_nrtra_this->nr)] == 1){
          continue;
        }
      #elif BLL_set_IsNodeRecycled == 1
        if(_BLL_nrtra_fcall(IsNodeReferenceRecycled, _BLL_nrtra_this->nr) == true){
          continue;
        }
      #else
        #error ?
      #endif

      #if BLL_set_LinkSentinel
        if(_BLL_nrtra_fcall(IsNRSentinel, _BLL_nrtra_this->nr) == true){
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

  #undef _BLL_nrtra_count

#if BLL_set_Language == 1
  };
#endif
