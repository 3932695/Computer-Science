#include <iostream>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

#include "semantics.h"
#include "parsetree.h"


Symtab * currentScope = NULL;
S_interface* currentInterface = NULL;
S_class* currentClass = NULL;
S_function* currentFunction = NULL;
int currentSeq = 0;

Symtab::Symtab(Symtab *p) : parent(p) {}

semantics * Symtab::lookup(string key) { 
  semantics *answer;
  return 
    (answer = local_lookup(key)) ? answer : 
    parent ? parent->lookup(key) : NULL;

}

semantics * Symtab::local_lookup(string key) { 
  return dict[key];
}

void Symtab::insert(string key, semantics * item) {
  assert (dict[key] == NULL);
  dict[key] = item;
}

void openscope()
{
  currentScope = new Symtab(currentScope);
}

Symtab *closescope()
{
  Symtab *v = currentScope;
  currentScope = currentScope->parent;
  return v;
}

