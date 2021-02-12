lox
===

lox is a **L**oader for **O**pen**X**R.  It isn't finished yet.

Differences from the standard loader so far
---

- The standard loader only requires the major and minor API versions to be compatible -- the patch
  number can be anything.  lox requires the patch version number to also be compatible.
- The standard loader supports creating instances from multiple threads.  lox doesn't.
- lox doesn't use secure_getenv, it just reads the environment variable.
