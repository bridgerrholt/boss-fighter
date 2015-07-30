#ifndef MAKE_UNIQUE_REC_H_
#define MAKE_UNIQUE_REC_H_

#include "main.h"

template<typename T, typename... Args>
std::unique_ptr<T> makeUniqueRec(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif
