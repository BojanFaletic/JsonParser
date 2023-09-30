#include <pybind11/pybind11.h>

import json.parser;

// add function
int add(int i, int j) {
  json::MyFunc();
  return i + j;
}

// make module
PYBIND11_MODULE(JsonParser, m) {
  m.doc() = "pybind11 example plugin";  // optional module docstring

  // add bindings
  m.def("add", &add, "A function which adds two numbers");
}
