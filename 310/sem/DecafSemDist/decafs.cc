#include "parsetree.h"
#include "semantics.h"



extern int yyparse(void);
extern ParseTree * top;
extern S_interface* currentInterface;
extern S_class* currentClass;
extern S_function* currentFunction;

void pass1(ParseTree * tree)
{
  bool open = false;
  if (!tree) return;
  if (tree->type==TERMINAL) return;
  // must be nonterminal
  if (tree->description=="binop")
    cout << "binop" << endl;
  if (tree->description=="Block") {
    openscope();
    open = true;
  }
  for (size_t i = 0; i < tree->children.size();i++)
    pass1(tree->children[i]);
  if (open)
    tree->symtab = closescope();
}

int main()
{
  yyparse();
  traverseTree(top,0,0);
  pass1(top);
  return 0;
}
