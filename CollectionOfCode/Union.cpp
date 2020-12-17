/// Before
#include <stdio.h>

int var1 = 1234;
int var2 = 4321;

int Union_v1() {
    int *pntr = &var2;
    pntr--;
    (*pntr) = 99;
    printf("Var1=%d\n",var1);
    printf("Var2=%d\n",var2);
}

/// After

#include <stdio.h>

union   // ugly, but interesting; still, ugly
{
  struct
  {
    int var1 {5678};
    int var2 {8765};
  };
  int arr[2];   // what about this ? in which one should the initialization
    // be placed, and which one is the "default type selection" of a union (?!)
}u;

int Union_v2() {
    int *pntr = &u.arr[1];
    pntr--;
    (*pntr) = 99;
    printf("Var1=%d\n",u.var1);
    printf("Var2=%d\n",u.var2);
}
