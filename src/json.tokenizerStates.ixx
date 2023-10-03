module;
#include <list>
#include <vector>
#include <cstdint>
using namespace std;

export module json.tokenizerStates;

import json.tokenizer_v2;

namespace json {
//const list<vector<TokenType>> States;

// transtion table for blob
enum class StateMachineType {
  InBlock,
  IsDone,
};

enum class StateMachineSymbols {
  Key,
  Value,
  Seperator,
};

// chain 1
vector<StateMachineSymbols> chain1{StateMachineSymbols::Key,
                                   StateMachineSymbols::Value
};


uint32_t blob_depth = 0;


};