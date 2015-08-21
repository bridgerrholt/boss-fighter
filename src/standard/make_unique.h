#ifndef STANDARD_MAKE_UNIQUE_H_
#define STANDARD_MAKE_UNIQUE_H_

#include "../main.h"

namespace Standard
{

	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

}

#endif
