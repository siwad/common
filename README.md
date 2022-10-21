# common
Common C++ classes and functions

Originally in 2005, at a short period of unemployment, I developped some classes and functions I found helpfully for further projects.
These classes and functions, in their primary form, became part of later projects.
In 2022, at the beginning of my partial retirement, I reworked these classes found in 2005.

The repository of common classes and functions contains:
* Java-like "synchronized { ... }"
* C++ array with variable size (like in Java)
* StringTokenizer (like in Java)
* Model-View-(Controller) pattern<br>Every setting in my projects is a so-called 'parameter'. Any change of a value of this parameter (by a controller) causes an update of all registered views. AssignRules and Voters could be attached.

The classes and functions have been compiled and tested with gcc 7.5.0 under Linux.

### License
GNU LGPL v3.0

