#include "header.hpp"

UnlockableClass::UnlockableClass() {
    locked = true;
}
void UnlockableClass::unlock() {
    locked = false;
}