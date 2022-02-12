#  keepcoding C library
## Data Structures

### Introduction

The keepcoding library contains a collection of data structures intended for general purpose usage. These structures are designed to be dynamic and allow the user to focus on their data rather than the structure. This comes with a slight performance cost; however, these data structures should be suitable for most applications.

### Compiling

To compile a stand-alone static library for the Data Structures sub-module, use the makefile:

```
make data_structures
```

This will generate a static library in the following folder:

```
keepcoding/data_structures/DataStructures.a
```

### Including

You can include the Data Structures sub-module by specifying its path:

```
#include <keepcoding/DataStructures.h>
